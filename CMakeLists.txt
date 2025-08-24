cmake_minimum_required(VERSION 3.31)

# Set project name and uppercase version
set(PROJECT_NAME "art")
set(PROJECT_NAME_UPPER "")
set(parent_prj "${parent_prj}/${PROJECT_NAME}")

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER) # Convert project name to uppercase

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Optimised" CACHE STRING "" FORCE)

# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# MSVC ONLY COMPILE OPTIONS
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_OPTIMISED "/O2 /Zi /DEBUG" CACHE STRING "Flags for Optimised configuration" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_OPTIMISED "/DEBUG /OPT:REF /OPT:ICF" CACHE STRING "Linker flags for Optimised configuration" FORCE)
endif()

if(CMAKE_GENERATOR STREQUAL "Ninja")
    # TODO: This is obtrusive. Use string(FIND <string> <substring> <output_variable>)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules -fbuiltin-module-map")

    set(CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE true)
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP true)
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API true)
endif()

# Option to build shared or static libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# BUILD DIR
set(build_dir "${root_dir}/build/${platform}/${PROJECT_NAME}")
set(CMAKE_BUILD_PATH ${build_dir})

# TODO: Include based on main project needs and setup!
# TODO: Separate into separate repos?

# COMPILE DEFINITIONS

# Windows only
if(WIN32)
    add_definitions(-D${PROJECT_NAME_UPPER}_WINDOWS)
endif()

# NEEDED FOR LINKING!! UPDATE WHENEVER A NEW PROJECT IS ADDED!!! ORDER MATTERS - DEPENDENCY TREE (or line xd)!!!! 
set(projects_list 
    "art"
    "art_paint"
    "art_canvas"
    "art_core"
    "art_extern"
    CACHE STRING "List of all projects" FORCE
)

# ADD ART DEPENDECIES AND SET DEPENDECIES TO OTHER PROJECTS (each project links against all others)
set(copied_list ${projects_list})
foreach(prj ${projects_list})
    list(REMOVE_ITEM copied_list ${prj})
    set(${prj}_DEPENDENCIES ${copied_list})

    if(NOT ${prj} STREQUAL ${PROJECT_NAME})
        add_subdirectory(${prj})
    endif()
endforeach() 

# TARGET & PROPERTIES
add_library(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME ${PROJECT_NAME}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${out_dir}/debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${out_dir}/release"
    ARCHIVE_OUTPUT_DIRECTORY_OPTIMISED "${out_dir}/optimised"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${out_dir}/debug"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${out_dir}/release"
    LIBRARY_OUTPUT_DIRECTORY_OPTIMISED "${out_dir}/optimised"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${out_dir}/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${out_dir}/release"
    RUNTIME_OUTPUT_DIRECTORY_OPTIMISED "${out_dir}/optimised"
    FOLDER "${parent_prj}"
)

file(GLOB_RECURSE mod_impls CONFIGURE_DEPENDS "src/*.cppm")
file(GLOB_RECURSE mod_headers CONFIGURE_DEPENDS "src/*.ixx")

file(GLOB_RECURSE impls CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "src/*.h")

# SOURCES
target_sources(${PROJECT_NAME}
    PRIVATE
    FILE_SET module_impls TYPE CXX_MODULES
    FILES
        ${mod_impls}
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${impls}
)

target_sources(${PROJECT_NAME}
    PUBLIC
    FILE_SET module_headers TYPE CXX_MODULES
    FILES
        ${mod_headers}
)

# INCLUDES
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${headers}
)

foreach(prj ${projects_list})
    message("Deps for project ${prj}: ${${prj}_DEPENDENCIES} ")
    target_link_libraries(${prj} PUBLIC ${${prj}_DEPENDENCIES})
endforeach()