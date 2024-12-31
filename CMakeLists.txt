cmake_minimum_required(VERSION 3.31)

# Set project name and uppercase version
set(PROJECT_NAME "art")
set(PROJECT_NAME_UPPER "")

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER) # Convert project name to uppercase

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

message(STATUS "Start generation of project with name: ${PROJECT_NAME_UPPER}")

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

# Enable folder structure in the IDE
set_property(GLOBAL PROPERTY USE_FOLDERS YES)

# Option to build shared or static libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Compile definitions

# Windows only
if(WIN32)
    add_definitions(-D${PROJECT_NAME_UPPER}_PLATFORM_WINDOWS)
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
    DEBUG_POSTFIX "_Debug"
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
