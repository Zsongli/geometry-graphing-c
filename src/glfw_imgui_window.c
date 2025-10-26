#include "glfw_imgui_window.h"

GLFWImGuiWindow* glfw_imgui_window_create(int width, int height, const char* title, ImGuiWindowCallback initialize_imgui_callback, ImGuiWindowCallback draw_callback) {
	GLFWImGuiWindow* this = malloc(sizeof(GLFWImGuiWindow));
	if (!this) return NULL;

	this->initialize_imgui_callack = initialize_imgui_callback;
	this->draw_callback = draw_callback;

	this->imgui_context = igCreateContext(NULL);
	if (!this->imgui_context) {
		free(this);
		return NULL;
	}
	INVOKE_CALLBACK(this->initialize_imgui_callack, this->imgui_context);

	this->glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!this->glfw_window) {
		igDestroyContext(this->imgui_context);
		free(this);
		return NULL;
	}

	glfwSetWindowSizeLimits(this->glfw_window, 200, 100, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwMakeContextCurrent(this->glfw_window);
	glfwSwapInterval(1);

	if (!ImGui_ImplGlfw_InitForOpenGL(this->glfw_window, true)) {
		glfwDestroyWindow(this->glfw_window);
		igDestroyContext(this->imgui_context);
		free(this);
		return NULL;
	}

	if (!ImGui_ImplOpenGL3_Init(NULL)) {
		ImGui_ImplGlfw_Shutdown();
		glfwDestroyWindow(this->glfw_window);
		igDestroyContext(this->imgui_context);
		free(this);
		return NULL;
	}

	return this;
}

void _init_new_frame(GLFWImGuiWindow* this) {
	igSetCurrentContext(this->imgui_context);
	glfwMakeContextCurrent(this->glfw_window);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	igNewFrame();
}

void _populate_draw_data(GLFWImGuiWindow* this) {
	if (this->imgui_context->IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		int window_x, window_y;
		glfwGetWindowPos(this->glfw_window, &window_x, &window_y);
		igSetNextWindowPos((ImVec2) { (float)window_x, (float)window_y }, ImGuiCond_Always, (ImVec2) { 0, 0 });
	}
	else {
		igSetNextWindowPos((ImVec2) { 0, 0 }, ImGuiCond_Always, (ImVec2) { 0, 0 });
	}
	igSetNextWindowSize((ImVec2) { this->imgui_context->IO.DisplaySize.x, this->imgui_context->IO.DisplaySize.y }, ImGuiCond_Always);

	igBegin("Main", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking);
	INVOKE_CALLBACK(this->draw_callback, this->imgui_context);
	igEnd();

	igRender();
}

void _render_draw_data(GLFWImGuiWindow* this) {
	glViewport(0, 0, (int)this->imgui_context->IO.DisplaySize.x, (int)this->imgui_context->IO.DisplaySize.y);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());

	// update and render viewports outside the main window
	if (this->imgui_context->IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		igUpdatePlatformWindows();
		igRenderPlatformWindowsDefault(NULL, NULL);
		glfwMakeContextCurrent(this->glfw_window);
	}
}

void glfw_imgui_window_run_main_loop(GLFWImGuiWindow* this) {
	while (!glfwWindowShouldClose(this->glfw_window)) {
		glfwPollEvents();

		_init_new_frame(this);
		_populate_draw_data(this);
		_render_draw_data(this);

		glfwSwapBuffers(this->glfw_window); // present
	}
}

void glfw_imgui_window_destroy(GLFWImGuiWindow* this) {
	igSetCurrentContext(this->imgui_context);
	glfwMakeContextCurrent(this->glfw_window);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	glfwDestroyWindow(this->glfw_window);
	igDestroyContext(this->imgui_context);
	free(this);
}
