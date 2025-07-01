add_library(CorePlugin STATIC
    src/CorePlugin.cpp
)

target_include_directories(CorePlugin PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/vendor/imgui
    ${CMAKE_SOURCE_DIR}/vendor/imgui/backends
    ${CMAKE_SOURCE_DIR}/vendor/SDL2
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
)

target_link_libraries(CorePlugin PUBLIC spdlog)
