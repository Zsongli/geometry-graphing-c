#include "window_with_imgui.h"
#include <stdlib.h>
#include "utils.h"
#include <cimgui_impl.h>

void window_with_imgui_on_draw(void* _this) {
	WindowWithImGui* this = _this;

	igSetCurrentContext(this->imgui_context);
	ImPlot_SetCurrentContext(this->implot_context);
	glfwMakeContextCurrent(this->base.glfw_window);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	igNewFrame();

	((WindowWithImGuiVTable*)this->base.vtable)->on_imgui_draw(this);

	igRender();
	
	glViewport(0, 0, (int)this->imgui_context->IO.DisplaySize.x, (int)this->imgui_context->IO.DisplaySize.y);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());

	if (this->imgui_context->IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		igUpdatePlatformWindows();
		igRenderPlatformWindowsDefault(NULL, NULL);
		glfwMakeContextCurrent(this->base.glfw_window);
	}
}

void window_with_imgui_on_imgui_draw(void* _this) {
	DISCARD(_this);
}

WindowWithImGuiVTable window_with_imgui_default_vtable = {
	.base = {
		.on_draw = window_with_imgui_on_draw,
	},
	.on_imgui_draw = window_with_imgui_on_imgui_draw,
};

bool window_with_imgui_new(WindowWithImGui* this, int width, int height, const char* title) {

	if(!window_new(&this->base, width, height, title)) goto fail_window;
	this->base.vtable = (WindowVTable*)&window_with_imgui_default_vtable;

	this->imgui_context = igCreateContext(NULL);
	if (!this->imgui_context) goto fail_imgui;

	this->implot_context = ImPlot_CreateContext();
	if (!this->implot_context) goto fail_implot;

	glfwSetWindowSizeLimits(this->base.glfw_window, 200, 100, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwMakeContextCurrent(this->base.glfw_window);
	glfwSwapInterval(1);

	igSetCurrentContext(this->imgui_context);

	if (!ImGui_ImplGlfw_InitForOpenGL(this->base.glfw_window, true)) goto fail_glfw;

	if (!ImGui_ImplOpenGL3_Init(NULL)) goto fail_opengl;

	return true;

fail_opengl:
	ImGui_ImplGlfw_Shutdown();
fail_glfw:
	ImPlot_DestroyContext(this->implot_context);
fail_implot:
	igDestroyContext(this->imgui_context);
fail_imgui:
	window_delete(&this->base);
fail_window:
	return false;
}

void window_with_imgui_delete(WindowWithImGui* this) {
	igSetCurrentContext(this->imgui_context);
	ImPlot_SetCurrentContext(this->implot_context);
	glfwMakeContextCurrent(this->base.glfw_window);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImPlot_DestroyContext(this->implot_context);
	igDestroyContext(this->imgui_context);
	window_delete(&this->base);
}
