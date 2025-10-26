#pragma once
#include <GLFW/glfw3.h>
#include <cimgui.h>
#include <cimgui_impl.h>
#include <stdlib.h>
#include "utils.h"

typedef void (*ImGuiWindowCallback)(ImGuiContext* ctx);

typedef struct {
	GLFWwindow* glfw_window;
	ImGuiContext* imgui_context;
	ImGuiWindowCallback initialize_imgui_callack;
	ImGuiWindowCallback draw_callback;
} GLFWImGuiWindow;

GLFWImGuiWindow* glfw_imgui_window_create(int width, int height, const char* title, ImGuiWindowCallback initialize_imgui_callback, ImGuiWindowCallback draw_callback);
void glfw_imgui_window_run_main_loop(GLFWImGuiWindow* this);
void glfw_imgui_window_destroy(GLFWImGuiWindow* this);
