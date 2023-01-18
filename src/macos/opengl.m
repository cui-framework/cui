#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include <glad/glad.h>
#include "include/opengl.h"

NSOpenGLContext *ctx;

// Creates a new Cocoa OpenGL context
void cui_macos_opengl_context(NSWindow *wnd) {
  NSOpenGLPixelFormatAttribute glAttribs[] = {
    NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
    NSOpenGLPFAColorSize, 24,
    NSOpenGLPFADepthSize, 8,
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFAAccelerated,
    0
  };

  NSOpenGLPixelFormat *pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:glAttribs];
  ctx = [[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil];

  [ctx setView:[wnd contentView]];
  [ctx makeCurrentContext];

  gladLoadGL();
}

// Swaps both buffers
void cui_macos_opengl_render() {
  [ctx makeCurrentContext];
  [ctx flushBuffer];
}
