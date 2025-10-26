-- Premake script generated to match the CMakeLists behavior for cimplot
-- This project builds a static library only (no shared/DLL option)

lib_root = "src"
project "cimplot"
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"

    location "build"
    objdir "build/obj/%{cfg.platform}/%{cfg.buildcfg}"
    targetdir "build/bin/%{cfg.platform}/%{cfg.buildcfg}"

    -- remove the default 'lib' prefix on Unix-like systems so the target name matches the
    -- CMake output (CMake set_target_properties(PREFIX ""))
    targetprefix ""

    -- include directories
    includedirs {
        lib_root,
        lib_root .. "/implot",
        -- cimgui/imgui and cimgui root (relative to this premake file)
        "../cimgui/src/imgui",
        "../cimgui/src",
    }

    -- explicit source list to match CMakeLists.txt
    files {
        -- cimplot sources
        lib_root .. "/cimplot.cpp",
        lib_root .. "/cimplot.h",
        lib_root .. "/implot/implot.cpp",
        lib_root .. "/implot/implot_demo.cpp",
        lib_root .. "/implot/implot_items.cpp",

        -- cimgui / imgui sources used by cimplot
        "../cimgui/src/cimgui.cpp",
        "../cimgui/src/imgui/imgui.cpp",
        "../cimgui/src/imgui/imgui_draw.cpp",
        "../cimgui/src/imgui/imgui_demo.cpp",
        "../cimgui/src/imgui/imgui_widgets.cpp",
        "../cimgui/src/imgui/imgui_tables.cpp",
    }

    -- preprocessor definitions from the CMakeLists
    -- IMGUI_USER_CONFIG must include the path to the user config header
    defines {
        'IMGUI_USER_CONFIG=\"..\\cimconfig.h\"',
        'IMGUI_DISABLE_OBSOLETE_FUNCTIONS=1',
    }

    -- Use static runtime to mirror a static library build
    staticruntime "On"

    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        links { "GL" }

    filter {}
