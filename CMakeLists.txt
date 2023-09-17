cmake_minimum_required(VERSION 3.12.0)
project(SDL_helloworld)

find_package(SDL3 CONFIG REQUIRED)

add_executable(sdl-helloworld
    main.c
)

target_link_libraries(sdl-helloworld PRIVATE SDL3::SDL3-shared)
target_link_libraries(sdl-helloworld PUBLIC SDL3::Headers)

if (WINDOWS)
    set_property(TARGET sdl-helloworld PROPERTY WIN32_EXECUTABLE TRUE)
endif()

