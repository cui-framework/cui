cmake_minimum_required(VERSION 3.0)
project(CUI VERSION 0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

if(MINGW OR MSVC)
  set(PLATFORM_SRCS src/windows/window.c)
endif(MINGW OR MSVC)

set(SRCS src/main.c)

add_executable(CUI ${PLATFORM_SRCS} ${SRCS})

if(MINGW OR MSVC)
  target_link_libraries(CUI user32 gdi32 opengl32)
endif(MINGW OR MSVC)
