target_dir = rootdir .. "bin/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}/%{prj.name}"
obj_dir = rootdir .. "bin_obj/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}/%{prj.name}"
parent = "art"

include "core"
include "extern"

project "art"
    kind "StaticLib"
    language "C++"
    targetdir (target_dir)
    objdir (obj_dir)
    location (rootdir .. "/build/%{prj.name}")
    cppdialect "C++23"
    exceptionhandling "Off"

    files
    {
        "art.ixx",
    }

    includedirs
    {
        "core/src",
        "extern/entt/src/entt",
        "extern/taskflow/taskflow",
    }

    links
    {
        "art_core",
        "art_extern",
    }

    filter { "files:src/**.cppm", "files:src/**.ixx" }
        compileas "Module"

    filter "system:windows"
        systemversion "latest"
        buildoptions { "/experimental:module" }

        defines
        {
            "ART_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "ART_DEBUG"
        symbols "On"
    
    filter "configurations:Optimised"
        defines "ART_OPTIMISED"
        symbols "On"
        optimize "On"
    
    filter "configurations:Release"
        defines "ART_RELEASE"
        optimize "On"
    
    -- filter { "system:windows", "configurations:Release" }
    --     buildoptions "/MT"