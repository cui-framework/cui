cmake_minimum_required(VERSION 3.0)
project(CUI VERSION 0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

if(MINGW OR MSVC)
  set(PLATFORM_SRCS src/windows/opengl.c src/windows/window.c)
endif(MINGW OR MSVC)

if(APPLE)
  set(CMAKE_C_LINK_FLAGS "${CMAKE_OBJC_LINK_FLAGS} -framework Foundation -framework Cocoa")
  set(PLATFORM_SRCS src/macos/app.m src/macos/window.m src/macos/opengl.m)
endif(APPLE)

if(UNIX AND NOT APPLE)
  set(PLATFORM_SRCS src/linux/window.c)
endif(UNIX AND NOT APPLE)

set(WIDGETS_SRCS src/widgets/window.c)
set(SRCS external/glad/glad.c src/main.c)

add_subdirectory(external/cglm)
include_directories(external)
include_directories(external/cglm/include)

add_executable(CUI ${PLATFORM_SRCS} ${WIDGETS_SRCS} ${SRCS})

if(MINGW OR MSVC)
  target_link_libraries(CUI user32 gdi32 opengl32)
endif(MINGW OR MSVC)

if(UNIX AND NOT APPLE)
  target_link_libraries(CUI GL dl pthread X11)
endif(UNIX AND NOT APPLE)
