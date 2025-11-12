#pragma once
#include "window_with_imgui.h"

typedef struct {
	WindowWithImGui base;
} MainWindow;

bool main_window_new(MainWindow* this, int width, int height, const char* title);
void main_window_delete(MainWindow* this);
