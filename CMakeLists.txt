cmake_minimum_required(VERSION 3.31)

# Set project name and uppercase version
set(PROJECT_NAME "art")
set(PROJECT_NAME_UPPER "")
set(parent_prj "${parent_prj}/${PROJECT_NAME}")

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER) # Convert project name to uppercase

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Optimised" CACHE STRING "" FORCE)

# MSVC ONLY COMPILE OPTIONS
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_OPTIMISED "/O2 /Zi /DEBUG" CACHE STRING "Flags for Optimised configuration" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_OPTIMISED "/DEBUG /OPT:REF /OPT:ICF" CACHE STRING "Linker flags for Optimised configuration" FORCE)
endif()

# Check if the platform is 64-bit or 32-bit and set appropriate definitions
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    ADD_DEFINITIONS(-D${PROJECT_NAME_UPPER}_X64)
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
    ADD_DEFINITIONS(-D${PROJECT_NAME_UPPER}_X86)
ELSE()
	MESSAGE( FATAL_ERROR "Unknown CPU architecture, CMAKE will exit." )
ENDIF()

# Option to build shared or static libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# BUILD DIR
set(build_dir "${root_dir}/build/${platform}/${PROJECT_NAME}")
set(CMAKE_BUILD_PATH ${build_dir})

# TODO: Include based on main project needs and setup!
# TODO: Separate into separate repos?

# SET EXTERNAL INCLUDES TO BE AVAILABLE FOR CHILDREN
set(extern_include 
        "${CMAKE_CURRENT_SOURCE_DIR}/art_extern/taskflow/taskflow"
        "${CMAKE_CURRENT_SOURCE_DIR}/art_extern/entt/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/art_core/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/art_paint/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/art_canvas/src"
)

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

# EXTERNAL INCUDE DIRS
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${extern_include}
)

foreach(prj ${projects_list})
    message("Deps for project ${prj}: ${${prj}_DEPENDENCIES} ")
    target_link_libraries(${prj} PUBLIC ${${prj}_DEPENDENCIES})
endforeach()

# target_link_libraries(${PROJECT_NAME} PUBLIC art_core art_extern)
# target_link_libraries(art_core PUBLIC art_extern)