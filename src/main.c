#include "app.h"
#include "main_window.h"
#include "utils.h"

int main(int argc, char** argv) {
	if (!app_init())
		return -1;

	MainWindow* window = main_window_create(800, 600, APP_NAME);
	if (!window) {
		app_destroy();
		return -1;
	}

	main_window_run_main_loop(window);

	main_window_destroy(window);
	app_destroy();
	return 0;
}

#ifdef _WIN32
	#include <windows.h>
	DEFINE_WINDOWS_ENTRY_POINT(main)
#endif
