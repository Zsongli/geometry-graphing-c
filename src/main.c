#include <GLFW/glfw3.h>
#include "utils.h"
#include "main_window.h"

#define INITIAL_WINDOW_WIDTH 800
#define INITIAL_WINDOW_HEIGHT 600

int main(int argc, char** argv) {
	DISCARD(argc); DISCARD(argv);

	if (!glfwInit())
		return -1;

	MainWindow window;
	if (!main_window_new(&window, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, APP_NAME)) {
		glfwTerminate();
		return -1;
	}

	window_run_main_loop((Window*)&window);

	main_window_delete(&window);
	glfwTerminate();
	return 0;
}

#ifdef _WIN32
#include <windows.h>
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	DISCARD(hInstance); DISCARD(hPrevInstance); DISCARD(lpCmdLine); DISCARD(nShowCmd);
	return main(__argc, __argv);
}
#endif
