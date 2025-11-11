lib_root = "src"
project "cimplot"
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"

    location "build"
    objdir "build/obj/%{cfg.platform}/%{cfg.buildcfg}"
    targetdir "build/bin/%{cfg.platform}/%{cfg.buildcfg}"

    targetprefix ""

    includedirs {
        lib_root,
        lib_root .. "/implot",
        "../cimgui/src/imgui",
        "../cimgui/src"
    }

    files {
        lib_root .. "/cimplot.cpp",
        lib_root .. "/cimplot.h",
        lib_root .. "/implot/implot.cpp",
        lib_root .. "/implot/implot_demo.cpp",
        lib_root .. "/implot/implot_items.cpp",

        "../cimgui/src/cimgui.cpp",
        "../cimgui/src/imgui/imgui.cpp",
        "../cimgui/src/imgui/imgui_draw.cpp",
        "../cimgui/src/imgui/imgui_demo.cpp",
        "../cimgui/src/imgui/imgui_widgets.cpp",
        "../cimgui/src/imgui/imgui_tables.cpp",
    }

    defines {
        'IMGUI_USER_CONFIG=\"..\\cimconfig.h\"',
        'IMGUI_DISABLE_OBSOLETE_FUNCTIONS=1',
    }

    filter "system:windows"
        staticruntime "On"

    filter "system:linux"
        links { "GL" }

    filter {}
