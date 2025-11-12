#include "main_window.h"
#include "resources/index.h"
#include "utils.h"
#include <imgui_macros.h>
#include <string.h>
#include <stdlib.h>

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
	char* droid_sans_ttf_data_copy = malloc(RESOURCE_SIZE(DROID_SANS_TTF));
	if (droid_sans_ttf_data_copy == NULL) return;
	memcpy(droid_sans_ttf_data_copy, RESOURCE_DATA(DROID_SANS_TTF), RESOURCE_SIZE(DROID_SANS_TTF));
	
	ImFontAtlas_AddFontFromMemoryTTF(io->Fonts, droid_sans_ttf_data_copy, RESOURCE_SIZE(DROID_SANS_TTF), 20.f, NULL, NULL);
}

void _initialize_imgui_style(ImGuiContext* imgui_context) {

	igStyleColorsLight(&imgui_context->Style);
	imgui_context->Style.FrameRounding = 4.f;
	imgui_context->Style.FrameBorderSize = 1.f;
}

void main_window_on_imgui_draw(void* _this) {
	MainWindow* this = _this;
	/*DO_ONCE({
		igDockBuilderRemoveNode(0);
		igDockBuilderAddNode(0, ImGuiDockNodeFlags_DockSpace);
		igDockBuilderSetNodeSize(0, imgui_context->IO.DisplaySize);
		igDockBuilderFinish(0);
		});*/

	ImGuiViewport* main_viewport = igGetMainViewport();
	igPushStyleColor_Vec4(ImGuiCol_DockingEmptyBg, (ImVec4) { 1.f, 1.f, 1.f, 1.f });
	igDockSpaceOverViewport(0, main_viewport, ImGuiDockNodeFlags_None, NULL);
	igPopStyleColor(1);

	/*char dockspace_window_label[32];
	sprintf_s(dockspace_window_label, IM_ARRAYSIZE(dockspace_window_label), "WindowOverViewport_%08X", main_viewport->ID);

	ImGuiWindow* dockspace_window = igFindWindowByName(dockspace_window_label);
	ImDrawList_AddImage(dockspace_window->DrawList,)*/

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

WindowWithImGuiVTable main_window_vtable = {
	.base = {
		.on_draw = window_with_imgui_on_draw,
	},
	.on_imgui_draw = main_window_on_imgui_draw,
};

bool main_window_new(MainWindow* this, int width, int height, const char* title) {

	if (!window_with_imgui_new(&this->base, width, height, title)) return false;
	this->base.base.vtable = (WindowVTable*)& main_window_vtable;

	_initialize_imgui_io_config(this->base.imgui_context);
	_initialize_imgui_style(this->base.imgui_context);

	return true;
}

void main_window_delete(MainWindow* this) {
	window_with_imgui_delete(&this->base);
}
