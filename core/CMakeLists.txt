cmake_minimum_required(VERSION 3.31)

# Set project name and uppercase version
set(PROJECT_NAME "art_core")
set(PROJECT_NAME_UPPER "")

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER) # Convert project name to uppercase

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

# Debug postfix
set(CMAKE_DEBUG_POSTFIX _Debug)
# Enable folder structure in the IDE
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

# Check if the platform is 64-bit or 32-bit and set appropriate definitions
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    ADD_DEFINITIONS(-D${PROJECT_NAME_UPPER}_PLATFORM_X64)
    MESSAGE(STATUS "64 bit platform - adding definition: ${PROJECT_NAME_UPPER}_PLATFORM_X64")
ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
    ADD_DEFINITIONS(-D${PROJECT_NAME_UPPER}_PLATFORM_X86)
    MESSAGE(STATUS "32 bit platform - adding definition: ${PROJECT_NAME_UPPER}_PLATFORM_X86")
ELSE()
	MESSAGE( FATAL_ERROR "Unknown CPU architecture, CMAKE will exit." )
ENDIF()

# Compile definitions

# Windows only
if(WIN32)
    add_definitions(-D${PROJECT_NAME_UPPER}_PLATFORM_WINDOWS)
endif()

# Add the core library
add_library(${PROJECT_NAME} STATIC)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME ${PROJECT_NAME}
    DEBUG_POSTFIX "_Debug"
)

# Add our module implementations included in this lib
target_sources(${PROJECT_NAME}
    PRIVATE
    FILE_SET module_impls TYPE CXX_MODULES
    FILES
        core.cppm

    PUBLIC
    FILE_SET module_headers TYPE CXX_MODULES
    FILES
        core.ixx
)

