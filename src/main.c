#include "app.h"
#include "main_window.h"
#include "linked_list.h"

int main(int argc, char** argv) {
	DISCARD(argc);
	DISCARD(argv);

	if (!app_init())
		return -1;

	MainWindow* window = main_window_new(800, 600, APP_NAME);
	if (!window) {
		app_destroy();
		return -1;
	}

	main_window_run_main_loop(window);

	main_window_delete(window);
	app_destroy();
	return 0;
}

#ifdef _WIN32
#include <windows.h>
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	DISCARD(hInstance);
	DISCARD(hPrevInstance);
	DISCARD(lpCmdLine);
	DISCARD(nShowCmd);

	return main(__argc, __argv);
}
#endif
