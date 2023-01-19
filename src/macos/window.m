#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include "include/app.h"
#include "include/window.h"
#include "include/opengl.h"

#include <glad/glad.h>

// Creates a new macOS Cocoa framework window
void cui_macos_window_new(unsigned int width, unsigned int height, const char *title) {
  @autoreleasepool {
    // Create the app
    [CustomApp sharedApplication];

    // Window configuration
    NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable | 
      NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;

    NSRect size = NSMakeRect(300, 300, width, height);
    NSString *newTitle = [NSString stringWithUTF8String:title];

    // Create the window
    NSWindow *wnd = [[NSWindow alloc] initWithContentRect:size styleMask:style
      backing:NSBackingStoreBuffered defer:NO];

    // Show the window
    [wnd setDelegate:[WindowDelegate alloc]];
    [wnd setTitle:newTitle];
    [wnd orderFrontRegardless];

    cui_macos_opengl_context(wnd);
  }
}

// Updates the window
void cui_macos_window_update() {
  [NSApp run];
  cui_macos_opengl_render();
}

// Returns a boolean value determining if the window is active
int cui_macos_window_active() {
  return isCloseRequested() == NO;
}

// Closes the window
void cui_macos_window_close() {
  [NSApp terminate:nil];
}
