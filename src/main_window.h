#pragma once
#include "window_with_imgui.h"
#include "texture.h"

typedef struct {
	WindowWithImGui base;
	Texture bg_tex;
	Texture about_tex;
	ImFont* default_font;
} MainWindow;

bool main_window_new(MainWindow* this, int width, int height, const char* title);
void main_window_delete(MainWindow* this);
