#include "app.h"
#include <assert.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

bool initialized = false;
bool app_init() {
	assert(!initialized && "app_init called after successful initialization");

	if (!glfwInit()) return false;
	// other initialization code can go here

	initialized = true;
	return true;
}

void app_destroy() {
	glfwTerminate();
}
