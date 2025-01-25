cmake_minimum_required(VERSION 3.16)

# CMake variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project Variables
set(EXE_NAME sdl3game)

# SDL Variables
set(SDL_TEST_LIBRARY OFF)

project(sdlgame C)

set(GAME_SOURCE_FILES
	src/main.c
	src/context.c
	src/vulkan.c)

# Find Packages
find_package(Vulkan REQUIRED)

# subdirs
add_subdirectory(subprojects/)
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

add_executable(${EXE_NAME})
target_sources(${EXE_NAME}
PRIVATE
	${GAME_SOURCE_FILES}
)
target_include_directories(${EXE_NAME}
PRIVATE
	Vulkan::Headers
	include/
)
target_link_libraries(${EXE_NAME}
PRIVATE
	SDL3::SDL3
	Vulkan::Vulkan
)
