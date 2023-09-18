cmake_minimum_required(VERSION 3.12.0)
project(SDL_helloworld)

find_package(SDL3 CONFIG REQUIRED)

add_executable(sdl-helloworld
    main.c
)

target_link_libraries(sdl-helloworld PRIVATE SDL3::SDL3)

# This is safe to set on all platforms. Otherwise your SDL app will
#  have a terminal window pop up with it on Windows.
set_property(TARGET sdl-helloworld PROPERTY WIN32_EXECUTABLE TRUE)

