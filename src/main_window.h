#pragma once
#include "glfw_imgui_window.h"

typedef struct {
	GLFWImGuiWindow* glfw_imgui_window;
	ImFont* font;
} MainWindow;

MainWindow* main_window_new(int width, int height, const char* title);
void main_window_delete(MainWindow* this);
void main_window_run_main_loop(MainWindow* this);
