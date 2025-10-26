#include "main_window.h"
#include "resources/droid_sans_ttf.h"
#include "utils.h"

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

void _set_imgui_style(ImGuiStyle* imgui_style, ImPlotStyle* implot_style) {
	igStyleColorsLight(imgui_style);
	imgui_style->FrameRounding = 4.f;
	imgui_style->FrameBorderSize = 1.f;
}

void _initialize_imgui(ImGuiContext* imgui_context, ImPlotContext* implot_context) {
	_set_imgui_io_config(&imgui_context->IO);
	_set_imgui_style(&imgui_context->Style, &implot_context->Style);
}

void _draw(ImGuiContext* imgui_context, ImPlotContext* implot_context) {
	//DO_ONCE_BEGIN()
	//{
	//	igDockBuilderRemoveNode(0); // Clear out existing layout
	//	igDockBuilderAddNode(0, ImGuiDockNodeFlags_DockSpace);
	//	igDockBuilderSetNodeSize(0, ctx->IO.DisplaySize);
	//	igDockBuilderFinish(0);
	//}
	//DO_ONCE_END()

	if (igBegin("Graph", NULL, ImGuiWindowFlags_None)) {
		ImPlot_SetNextAxesLimits(-100.0, 100.0, -100.0, 100.0, ImPlotCond_Once);
		if (ImPlot_BeginPlot("Graph", (ImVec2) { -1, -1 }, ImPlotFlags_NoTitle | ImPlotFlags_NoFrame)) {
			ImVec2 rmin;
			ImPlot_PlotToPixels_PlotPoInt(&rmin, (ImPlotPoint) { -10, -10 }, -1, -1);
			ImVec2 rmax;
			ImPlot_PlotToPixels_PlotPoInt(&rmax, (ImPlotPoint) { 10, 10 }, -1, -1);
			
			ImDrawList_AddRect(ImPlot_GetPlotDrawList(), rmin, rmax, IM_COL32(0,0,0,255), 0.f, ImDrawFlags_None, 1.f);
			ImPlot_EndPlot();
		}
		igEnd();
	}
}

MainWindow* main_window_create(int width, int height, const char* title) {
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
