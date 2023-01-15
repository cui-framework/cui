cmake_minimum_required(VERSION 3.0)
project(CUI VERSION 0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(SRCS src/main.c)

add_executable(CUI ${SRCS})

if(MINGW OR MSVC)
  target_link_libraries(CUI user32 gdi32 opengl32)
endif(MINGW OR MSVC)
