#include "main_window.h"
#include "resources/index.h"
#include "utils.h"
#include <imgui_macros.h>
#include <string.h>

void _initialize_imgui_io_config(ImGuiContext* imgui_context) {
	ImGuiIO* const io = igGetIO_ContextPtr(imgui_context);
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io->ConfigDpiScaleFonts = true;
	io->ConfigDpiScaleViewports = true;
	io->LogFilename = NULL;
	io->IniFilename = NULL;

	// this is so stupid
	char* droid_sans_ttf_data_copy = malloc(IM_ARRAYSIZE(RESOURCE_DATA(DROID_SANS_TTF)));
	if (droid_sans_ttf_data_copy == NULL) return;
	memcpy(droid_sans_ttf_data_copy, RESOURCE_DATA(DROID_SANS_TTF), IM_ARRAYSIZE(RESOURCE_DATA(DROID_SANS_TTF)));
	
	ImFontAtlas_AddFontFromMemoryTTF(io->Fonts, droid_sans_ttf_data_copy, IM_ARRAYSIZE(RESOURCE_DATA(DROID_SANS_TTF)), 20.f, NULL, NULL);
}

void _initialize_imgui_style(ImGuiContext* imgui_context) {

	igStyleColorsLight(&imgui_context->Style);
	imgui_context->Style.FrameRounding = 4.f;
	imgui_context->Style.FrameBorderSize = 1.f;
}

void _initialize_imgui(ImGuiContext* imgui_context, ImPlotContext* implot_context) {
	DISCARD(implot_context);
	_initialize_imgui_io_config(imgui_context);
	_initialize_imgui_style(imgui_context);
}

void _draw(ImGuiContext* imgui_context, ImPlotContext* implot_context) {
	DISCARD(implot_context);
	DISCARD(imgui_context);
	/*DO_ONCE({
		igDockBuilderRemoveNode(0);
		igDockBuilderAddNode(0, ImGuiDockNodeFlags_DockSpace);
		igDockBuilderSetNodeSize(0, imgui_context->IO.DisplaySize);
		igDockBuilderFinish(0);
		});*/


	igBegin("Graph", NULL, ImGuiWindowFlags_None);
	ImPlot_SetNextAxesLimits(-100.0, 100.0, -100.0, 100.0, ImPlotCond_Once);
	if (ImPlot_BeginPlot("Graph", (ImVec2) { -1, -1 }, ImPlotFlags_NoTitle | ImPlotFlags_NoFrame)) {
		ImVec2 rmin;
		ImPlot_PlotToPixels_PlotPoInt(&rmin, (ImPlotPoint) { -10, -10 }, -1, -1);
		ImVec2 rmax;
		ImPlot_PlotToPixels_PlotPoInt(&rmax, (ImPlotPoint) { 10, 10 }, -1, -1);

		ImDrawList_AddRect(ImPlot_GetPlotDrawList(), rmin, rmax, IM_COL32(0, 0, 0, 255), 0.f, ImDrawFlags_None, 1.f);
		ImPlot_EndPlot();
	}

	igEnd();
}

MainWindow* main_window_new(int width, int height, const char* title) {
	MainWindow* this = malloc(sizeof(MainWindow));
	if (!this) return NULL;

	this->glfw_imgui_window = glfw_imgui_window_new(width, height, title, _initialize_imgui, _draw);
	if (!this->glfw_imgui_window) {
		free(this);
		return NULL;
	}

	return this;
}

void main_window_delete(MainWindow* this) {
	//ImFontAtlas_RemoveFont(this->glfw_imgui_window->imgui_context->IO.Fonts, this->font);
	glfw_imgui_window_delete(this->glfw_imgui_window);
	free(this);
}

void main_window_run_main_loop(MainWindow* this) {
	glfw_imgui_window_run_main_loop(this->glfw_imgui_window);
}
