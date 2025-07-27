cmake_minimum_required(VERSION 3.31)

# Set project name and uppercase version
set(PROJECT_NAME "art_extern")
set(PROJECT_NAME_UPPER "")

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER) # Convert project name to uppercase

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Optimised" CACHE STRING "" FORCE)

# MSVC ONLY COMPILE OPTIONS
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_OPTIMISED "/O2 /Zi /DEBUG" CACHE STRING "Flags for Optimised configuration" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_OPTIMISED "/DEBUG /OPT:REF /OPT:ICF" CACHE STRING "Linker flags for Optimised configuration" FORCE)
endif()

# APPLE NOT ON DARWIN CONFIG
if ((APPLE AND NOT CMAKE_SYSTEM_NAME MATCHES "Darwin") OR EMSCRIPTEN)
    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")    # Disable shared builds on platforms where it does not make sense to use them
    set(SDL_SHARED OFF)
else()
    set(SDL_SHARED ON)
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

# Compile definitions

# Windows only
if(WIN32)
    add_definitions(-D${PROJECT_NAME_UPPER}_WINDOWS)
endif()

set(TF_BUILD_TESTS OFF CACHE BOOL "Build Taskflow tests" FORCE) 
set(TF_BUILD_EXAMPLES OFF CACHE BOOL "Build Taskflow examples" FORCE)

# external libs
add_subdirectory(taskflow)
add_subdirectory(flecs)
add_subdirectory(sdl EXCLUDE_FROM_ALL)

# TARGET & PROPERTIES
add_library(${PROJECT_NAME})
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    target_link_options(${PROJECT_NAME} PUBLIC -sASSERTIONS=1 -sPROXY_TO_PTHREAD -sTOTAL_MEMORY=1536MB -sEXIT_RUNTIME=1 -sUSE_PTHREADS=1)
    target_compile_options(${PROJECT_NAME} PUBLIC -matomics)
endif()

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

if(WIN32)
    add_custom_command(
        TARGET art_extern POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:art_extern>
        VERBATIM
    )
endif()

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

# Link against the subsystem libraries
target_link_libraries(${PROJECT_NAME} PUBLIC Taskflow PUBLIC ${ATOMIC_LIBRARY} PUBLIC flecs::flecs_static PUBLIC SDL3::SDL3)