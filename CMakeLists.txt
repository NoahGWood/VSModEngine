cmake_minimum_required(VERSION 3.10)
project(VSModEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default")


set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
add_subdirectory(vendor/SDL2)

#ImGui
file(GLOB IMGUI_SOURCES
    vendor/imgui/*.cpp
    vendor/imgui/backends/imgui_impl_sdl2.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
    vendor/imgui
    vendor/imgui/backends
    vendor/SDL2/include
)

# spdlog
add_library(spdlog::spdlog_header_only INTERFACE IMPORTED GLOBAL)
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE vendor/spdlog/include)
add_library(spdlog::spdlog ALIAS spdlog)

#Editor Lib
add_library(vsmod_lib STATIC
    src/Core/Logger.cpp
    src/Plugin/PluginManager.cpp
    src/Utils/fs.cpp
)
target_include_directories(vsmod_lib PUBLIC
    include
    vendor/imgui
    vendor/imgui/backends
    vendor/SDL2
    vendor/spdlog/include
)
target_link_libraries(vsmod_lib PUBLIC SDL2 imgui OpenGL::GL spdlog::spdlog)

# Core Plugin
add_subdirectory(plugins/CorePlugin)

#Editor App
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(vsmod ${SOURCES})
target_include_directories(vsmod PRIVATE
    include
    vendor/imgui
    vendor/imgui/backends
    vendor/SDL2
    vendor/spdlog/include
    plugins
)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
target_link_libraries(vsmod PRIVATE vsmod_lib CorePlugin)