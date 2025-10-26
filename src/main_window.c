#include "main_window.h"
#include "resources/droid_sans_ttf.h"

void _set_imgui_io_config(ImGuiIO* io) {
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io->ConfigDpiScaleFonts = true;
	io->ConfigDpiScaleViewports = true;
	io->LogFilename = NULL;
	io->IniFilename = NULL;
	ImFontAtlas_AddFontFromMemoryCompressedBase85TTF(io->Fonts, droid_sans_compressed_data_base85, 20.f, NULL, NULL);
}

void _set_imgui_style(ImGuiStyle* style) {
	igStyleColorsLight(style);
	style->FrameRounding = 4.f;
	style->FrameBorderSize = 1.f;
}

void _initialize_imgui(ImGuiContext* ctx) {
	_set_imgui_io_config(&ctx->IO);
	_set_imgui_style(&ctx->Style);
}

void _draw(ImGuiContext* ctx) {
	igButton("Hello, world!", (ImVec2) { 0, 0 });
}

MainWindow* main_window_create(int width, int height, const char* title){
	MainWindow* this = malloc(sizeof(MainWindow));
	if (!this) return NULL;

	this->glfw_imgui_window = glfw_imgui_window_create(width, height, title, _initialize_imgui, _draw);
	if (!this->glfw_imgui_window) {
		free(this);
		return NULL;
	}

	return this;
}

void main_window_destroy(MainWindow* this) {
	glfw_imgui_window_destroy(this->glfw_imgui_window);
	free(this);
}

void main_window_run_main_loop(MainWindow* this) {
	glfw_imgui_window_run_main_loop(this->glfw_imgui_window);
}
