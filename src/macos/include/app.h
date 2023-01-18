#ifndef _mac_app_h_
#define _mac_app_h_

@interface CustomApp : NSApplication
- (void)run;
@end

@protocol WindowProtocol <NSWindowDelegate>
- (BOOL)windowShouldClose:(id)sender;
@end

@interface WindowDelegate:NSObject<WindowProtocol>
@end

BOOL isCloseRequested();

#endif
