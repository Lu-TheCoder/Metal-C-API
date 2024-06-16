//
//  WindowDelegate.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/02.
//

#pragma once
#import <Cocoa/Cocoa.h>
#import "NSDefines.h"
#import <QuartzCore/CAMetalLayer.h>
#import "../platform.h"

@class ApplicationDelegate;
@class WindowDelegate;
@class ContentView;

typedef struct macos_handle_info {
    CAMetalLayer* layer;
}macos_handle_info;

/**
 Platform Internal State
 */
typedef struct platform_state{
    ApplicationDelegate* app_delegate;
    WindowDelegate* wnd_delegate;
    NSWindow* window;
    ContentView* view;
    macos_handle_info handle;
    bool quit_flagged;
    float device_pixel_ratio;
    platform_window_resized_callback window_resized_callback;
}platform_state;


@interface WindowDelegate : NSWindow <NSWindowDelegate>
{
    platform_state* state;
}
-(instancetype)initWithState:(platform_state*)init_state;

@end //interface WindowDelegate
