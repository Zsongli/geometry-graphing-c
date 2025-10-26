#define CONCAT_IMPL(x, y) x##y
#define CONCAT( x, y ) CONCAT_IMPL(x,y)

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

#define DO_ONCE_BEGIN() _DO_ONCE_BEGIN(CONCAT(do_once_, __COUNTER__))
#define _DO_ONCE_BEGIN(varname) static bool varname = true; if(varname) { varname = false;
#define DO_ONCE_END() }

#define IM_COL32(R,G,B,A)    (((ImU32)(A)<<24) | ((ImU32)(B)<<16) | ((ImU32)(G)<<8) | ((ImU32)(R)<<0))
