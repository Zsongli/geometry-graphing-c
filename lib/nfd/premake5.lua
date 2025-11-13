lib_dir = "src"
project "nfd"
    kind "StaticLib"
    language "C"

    location "build"
    objdir "build/obj/%{cfg.platform}/%{cfg.buildcfg}"
    targetdir "build/bin/%{cfg.platform}/%{cfg.buildcfg}"

    includedirs {
        lib_dir .. "/src/include"
    }

    files {
        lib_dir .. "/src/*.h",
        lib_dir .. "/src/include/*.h",
        lib_dir .. "/src/nfd_common.c"
    }

    filter "system:windows"
        language "C++"
        staticruntime "On"
        files {
            lib_dir .. "/src/nfd_win.cpp"
        }
    
    filter "system:linux"
        files {
            lib_dir .. "/src/nfd_gtk.c"
        }
    
    filter "action:vs*"
        defines { "_CRT_SECURE_NO_WARNINGS" }


