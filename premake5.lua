
workspace "Geometry Graphing"
   filename "GeometryGraphing"
   configurations { "Debug", "Release" }
   platforms { "x64" }
   defaultplatform "x64"

   filter "configurations:Debug"
      symbols "On"
      defines { "_DEBUG" }

   filter "configurations:Release"
      optimize "On"
   
   filter "platforms:x64"
      architecture "x86_64"

include "lib/glfw"
include "lib/cimgui"

project "GeometryGraphing"
   kind "WindowedApp"

   language "C"
   cdialect "C17"
   location "build"
   staticruntime "On"
   objdir "build/obj/%{cfg.platform}/%{cfg.buildcfg}"
   targetdir "build/bin/%{cfg.platform}/%{cfg.buildcfg}"

   files { "src/**.h", "src/**.c" }

   includedirs {
      "lib/glfw/src/include",
      "lib/cimgui/src",
      "lib/cimgui/imgui",
      "lib/cimgui/imgui/backends"
   }

   links { "cimgui", "glfw" }

   defines { "CIMGUI_USE_GLFW", "CIMGUI_USE_OPENGL3", "CIMGUI_DEFINE_ENUMS_AND_STRUCTS", "APP_NAME=\"%{wks.name}\"" }

   filter "system:windows"
      links { "opengl32" }

   filter "system:linux"
      links { "GL", "X11", "pthread", "dl" }
