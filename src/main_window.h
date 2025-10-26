#pragma once
#include "glfw_imgui_window.h"

typedef struct {
	GLFWImGuiWindow* glfw_imgui_window;
} MainWindow;

MainWindow* main_window_create(int width, int height, const char* title);
void main_window_destroy(MainWindow* this);
void main_window_run_main_loop(MainWindow* this);
