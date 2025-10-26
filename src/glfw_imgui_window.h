#pragma once
#include <GLFW/glfw3.h>
#include <cimgui.h>
#include <cimgui_impl.h>
#include <cimplot.h>
#include <stdlib.h>
#include "utils.h"

typedef void (*GLFWImGuiWindowCallback)(ImGuiContext* imgui_context, ImPlotContext* implot_context);

typedef struct {
	GLFWwindow* glfw_window;
	ImGuiContext* imgui_context;
	GLFWImGuiWindowCallback initialize_imgui_callack;
	GLFWImGuiWindowCallback draw_callback;
	ImPlotContext* implot_context;
} GLFWImGuiWindow;

GLFWImGuiWindow* glfw_imgui_window_create(int width, int height, const char* title, GLFWImGuiWindowCallback initialize_imgui_callback, GLFWImGuiWindowCallback draw_callback);
void glfw_imgui_window_run_main_loop(GLFWImGuiWindow* this);
void glfw_imgui_window_destroy(GLFWImGuiWindow* this);
