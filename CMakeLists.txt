cmake_minimum_required(VERSION 3.31)

# Set project name and uppercase version
set(PROJECT_NAME "art")
set(PROJECT_NAME_UPPER "")

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER) # Convert project name to uppercase

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Optimised" CACHE STRING "" FORCE)

# MSVC ONLY!!!
set(CMAKE_CXX_FLAGS_OPTIMISED "/O2 /Zi /DEBUG" CACHE STRING "Flags for Optimised configuration" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_OPTIMISED "/DEBUG /OPT:REF /OPT:ICF" CACHE STRING "Linker flags for Optimised configuration" FORCE)

# Check if the platform is 64-bit or 32-bit and set appropriate definitions
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    ADD_DEFINITIONS(-D${PROJECT_NAME_UPPER}_X64)
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
    ADD_DEFINITIONS(-D${PROJECT_NAME_UPPER}_X86)
ELSE()
	MESSAGE( FATAL_ERROR "Unknown CPU architecture, CMAKE will exit." )
ENDIF()

# Enable folder structure in the IDE
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

# Option to build shared or static libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(build_dir "${root_dir}/build/${platform}/${PROJECT_NAME}")
set(parent_build_dir ${build_dir})
message("Build Directory for ${PROJECT_NAME} set to ${build_dir}")
set(CMAKE_BUILD_PATH ${build_dir})

# Compile definitions

# Windows only
if(WIN32)
    add_definitions(-D${PROJECT_NAME_UPPER}_WINDOWS)
endif()

# Add subdirectories for each subsystem
add_subdirectory(core)
# add_subdirectory(audio)
# add_subdirectory(graphics)
# add_subdirectory(window)

# Add the audio library
add_library(${PROJECT_NAME} art.ixx)

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
)

# Add our modules included in this lib
target_sources(${PROJECT_NAME}
    PUBLIC
    FILE_SET module_headers TYPE CXX_MODULES
    FILES
        art.ixx
)

# Link against the subsystem libraries
target_link_libraries(${PROJECT_NAME} PUBLIC art_core)
