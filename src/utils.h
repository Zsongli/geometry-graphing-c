#define INVOKE_CALLBACK(callback, ...) \
	do { \
		if (callback) { \
			callback(__VA_ARGS__); \
		} \
	} while (0)

#define DEFINE_WINDOWS_ENTRY_POINT(main_function) \
	int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) { \
		int argc = __argc; \
		char** argv = __argv; \
		return main_function(argc, argv); \
	}