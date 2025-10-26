lib_root = "src"
project "glfw"
    kind "StaticLib"
    language "C"
    cdialect "C99"

    location "build"
    objdir "build/obj/%{cfg.platform}/%{cfg.buildcfg}"
    targetdir "build/bin/%{cfg.platform}/%{cfg.buildcfg}"

    files {
        lib_root .. "/include/GLFW/glfw3.h",
        lib_root .. "/include/GLFW/glfw3native.h",
        lib_root .. "/src/internal.h",
        lib_root .. "/src/platform.h",
        lib_root .. "/src/mappings.h",
        lib_root .. "/src/context.c",
        lib_root .. "/src/init.c",
        lib_root .. "/src/input.c",
        lib_root .. "/src/monitor.c",
        lib_root .. "/src/platform.c",
        lib_root .. "/src/vulkan.c",
        lib_root .. "/src/window.c",
        lib_root .. "/src/egl_context.c",
        lib_root .. "/src/osmesa_context.c",
        lib_root .. "/src/null_*.h",
        lib_root .. "/src/null_*.c"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        defines { "_GLFW_WIN32", "_CRT_SECURE_NO_WARNINGS" }
        files {
            lib_root .. "/src/win32_*.c",
            lib_root .. "/src/win32_*.h",
            lib_root .. "/src/wgl_context.c",
            lib_root .. "/src/egl_context.c",
            lib_root .. "/src/osmesa_context.c"
        }
    
    filter "system:linux"
        pic "On"
        defines { "_GLFW_X11" }
        files {
            lib_root .. "/src/x11_*.c",
            lib_root .. "/src/xkb_unicode.c",
            lib_root .. "/src/posix_time.c",
            lib_root .. "/src/posix_thread.c",
            lib_root .. "/src/glx_context.c",
            lib_root .. "/src/egl_context.c",
            lib_root .. "/src/osmesa_context.c",
            lib_root .. "/src/linux_joystick.c"
        }
