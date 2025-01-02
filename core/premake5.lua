target_dir = rootdir .. "/bin/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}/%{prj.name}"
obj_dir = rootdir .. "/bin_obj/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}/%{prj.name}"

project "art_core"
    kind "StaticLib"
    language "C++"
    targetdir (target_dir)
    objdir (obj_dir)
    location (rootdir .. "/build/" .. parent .. "/%{prj.name}")
    cppdialect "C++23"
    exceptionhandling "Off"

    files
    {
        "src/**.cpp",
        "src/**.h",
        "src/**.ixx",
        "src/**.cppm",
    }

    includedirs
    {
        rootdir .. "/art/core/src",
        rootdir .. "/art/extern/entt/src/entt",
        rootdir .. "/art/extern/taskflow/taskflow",
    }

    filter { "files:src/**.cppm", "files:src/**.ixx" }
        compileas "Module"

    filter "system:windows"
        systemversion "latest"
        buildoptions { "/experimental:module" }

        defines
        {
            "ART_CORE_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "ART_CORE_DEBUG"
        symbols "On"
    
    filter "configurations:Optimised"
        defines "ART_CORE_OPTIMISED"
        symbols "On"
        optimize "On"
    
    filter "configurations:Release"
        defines "ART_CORE_RELEASE"
        optimize "On"
    
    -- filter { "system:windows", "configurations:Release" }
    --     buildoptions "/experimental:module"