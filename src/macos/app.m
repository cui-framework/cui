#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include "include/app.h"

BOOL closeRequested = NO;

@implementation CustomApp
- (void)run {
  @autoreleasepool {
    // Event handling
    NSEvent *event = [self nextEventMatchingMask:NSEventMaskAny
      untilDate:[NSDate distantFuture]
      inMode:NSDefaultRunLoopMode
      dequeue:YES];
    
    [self sendEvent:event];
    [self updateWindows];
  }
}
@end

// Redirect the window closing system to not close automatically
@implementation WindowDelegate
- (BOOL)windowShouldClose:(id)sender {
  closeRequested = YES;
  return NO;
}
@end

// Returns a boolean value determining if the window should close
BOOL isCloseRequested() {
  return closeRequested;
}
