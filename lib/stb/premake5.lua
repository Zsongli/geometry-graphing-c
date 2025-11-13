lib_root = "src"
project "stb"
    kind "StaticLib"
    
    language "C"
    cdialect "C17"
    location "build"
    staticruntime "On"
    objdir "build/obj/%{cfg.platform}/%{cfg.buildcfg}"
    targetdir "build/bin/%{cfg.platform}/%{cfg.buildcfg}"
    
    includedirs { lib_root }
    files { lib_root .. "/*.h", "src_local/*.c" }
