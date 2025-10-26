lib_root = "src"
project "cimgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"

    location "build"
    objdir "build/obj/%{cfg.platform}/%{cfg.buildcfg}"
    targetdir "build/bin/%{cfg.platform}/%{cfg.buildcfg}"

    includedirs {
        lib_root,
        lib_root .. "/imgui",
        lib_root .. "/imgui/backends",
        "%{wks.location}/lib/glfw/src/include"
    }

    files {
        lib_root .. "/cimgui.cpp",
        lib_root .. "/imgui/*.cpp",
        lib_root .. "/imgui/backends/imgui_impl_glfw.cpp",
        lib_root .. "/imgui/backends/imgui_impl_opengl3.cpp"
    }

    defines {
        "IMGUI_DISABLE_OBSOLETE_FUNCTIONS=1",
        "IMGUI_IMPL_OPENGL_LOADER_GL3W",
        "IMGUI_USER_CONFIG=\"../cimconfig.h\""
    }

    links { "glfw" }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"
        defines { "IMGUI_IMPL_API=extern \"C\" __declspec(dllexport)" }
    
    filter "system:linux"
        links { "GL" }
        defines { "IMGUI_IMPL_API=extern \"C\"" }
