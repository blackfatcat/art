target_dir = rootdir .. "/bin/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}/%{prj.name}"
obj_dir = rootdir .. "/bin_obj/%{cfg.system}_%{cfg.architecture}/%{cfg.buildcfg}/%{prj.name}"

project "art_extern"
    kind "StaticLib"
    language "C++"
    targetdir (target_dir)
    objdir (obj_dir)
    location (rootdir .. "/build/" .. parent .. "/%{prj.name}")
    cppdialect "C++23"
    exceptionhandling "Off"

    files
    {
        "entt/src/**.cpp",
        "entt/src/**.h",
        "entt/src/**.ixx",
        "entt/src/**.cppm",
        "entt/src/**.hpp",
        "entt/src/**.c",
        "taskflow/taskflow/**.cpp",
        "taskflow/taskflow/**.h",
        "taskflow/taskflow/**.ixx",
        "taskflow/taskflow/**.cppm",
        "taskflow/taskflow/**.hpp",
        "taskflow/taskflow/**.c",
    }

    local pthread = os.findlib("Threads")

    links
    {
        "Threads",
    }

    filter { "files:src/**.cppm", "files:src/**.ixx" }
        compileas "Module"

    filter "system:windows"
        systemversion "latest"
        buildoptions { "/experimental:module" }
        
        defines
        {
            "ART_EXTERN_PLATFORM_WINDOWS"
        }
    
    filter "configurations:Debug"
        defines "ART_EXTERN_DEBUG"
        symbols "On"
    
    filter "configurations:Optimised"
        defines "ART_EXTERN_OPTIMISED"
        symbols "On"
        optimize "On"
    
    filter "configurations:Release"
        defines "ART_EXTERN_RELEASE"
        optimize "On"
    
    -- filter { "system:windows", "configurations:Release" }
    --     buildoptions "/experimental:module"
