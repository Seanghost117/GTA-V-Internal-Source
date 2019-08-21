workspace "UC-Internal"
  architecture "x64"
  startproject "UC-Internal"

  configurations
  {
    "Debug",
    "Release"
  }

  IncludeDir = {}
  IncludeDir["MinHook"] = "vendor/MinHook/include"
  IncludeDir["json"] = "vendor/json/single_include"

  staticruntime "Off"
  systemversion "10.0"
  toolset "v142"
  cppdialect "C++17"

  defines
  {
    "_CRT_SECURE_NO_WARNINGS",
    "NOMINMAX",
    "WIN32_LEAN_AND_MEAN",
    "_WIN32_WINNT=0x601" -- Windows 7
  }

  filter "configurations:Debug"
    defines { "_DEBUG" }
    symbols "On"
  filter "not configurations:Debug"
    defines { "NDEBUG" }

  filter "configurations:Dist"
    flags { "LinkTimeOptimization" }
    optimize "speed"

  flags { "MultiProcessorCompile" }

  project "MinHook"
    kind "StaticLib"
    language "C"

    targetdir ("bin/lib/%{cfg.buildcfg}")
    objdir ("bin/lib/int/%{cfg.buildcfg}/MinHook")

    files
    {
      "vendor/MinHook/include/**.h",
      "vendor/MinHook/src/**.h",
      "vendor/MinHook/src/**.c"
    }

  project "UC-Internal"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("bin/int/%{cfg.buildcfg}/%{prj.name}")

    PrecompiledHeaderInclude = "stdafx.h"
    PrecompiledHeaderSource = "src/stdafx.cpp"
 
    files
    {
      "src/**.h",
      "src/**.hpp",
      "src/**.cpp",
      "src/**.asm"
    }

    includedirs
    {
      "%{IncludeDir.MinHook}",
      "%{IncludeDir.json}",
      "src/"
    }

    libdirs
    {
      "bin/lib"
    }

    links
    {
      "MinHook"
    }

    pchheader "%{PrecompiledHeaderInclude}"
    pchsource "%{PrecompiledHeaderSource}"

    forceincludes
    {
      "%{PrecompiledHeaderInclude}"
    }

    flags { "NoImportLib", "Maps" }

