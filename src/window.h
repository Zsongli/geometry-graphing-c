#pragma once
#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct {
	void (*on_draw)(void* this);
} WindowVTable;

WindowVTable window_default_vtable;

typedef struct {
	WindowVTable* vtable;
	GLFWwindow* glfw_window;
} Window;

bool window_new(Window* this, int width, int height, const char* title);
void window_run_main_loop(Window* this);
void window_delete(Window* this);

void window_on_draw(void* this);
