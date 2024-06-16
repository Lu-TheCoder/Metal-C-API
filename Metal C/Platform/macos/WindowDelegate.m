//
//  WindowDelegate.m
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/02.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import <QuartzCore/CAMetalLayer.h>
#import "WindowDelegate.h"
#import "ContentView.h"
#import "../../Engine/core/input.h"
#import "../../Engine/core/event.h"

@implementation WindowDelegate

- (instancetype)initWithState:(platform_state *)init_state {
    self = [super init];
    
    if (self != nil) {
        state = init_state;
        state->quit_flagged = false;
    }
    
    return self;
}

- (BOOL)windowShouldClose:(NSWindow *)sender {
    state->quit_flagged = true;
    
    event_context context = {0};
    event_fire(EVENT_CODE_APPLICATION_QUIT, 0, context);
    
    return YES;
}

- (void)windowDidChangeScreen:(NSNotification *)notification {
    event_context context = {0};
    CGSize viewSize = state->view.bounds.size;
    NSSize newDrawableSize = [state->view convertSizeToBacking:viewSize];
    state->handle.layer.drawableSize = newDrawableSize;
    state->handle.layer.contentsScale = state->view.window.backingScaleFactor;
    state->device_pixel_ratio = state->handle.layer.contentsScale;
    
    context.data.u16[0] = (uint16_t)newDrawableSize.width;
    context.data.u16[1] = (uint16_t)newDrawableSize.height;
    event_fire(EVENT_CODE_RESIZED, 0, context);
}

- (void)windowDidResize:(NSNotification *)notification {
    event_context context = {0};
    CGSize viewSize = state->view.bounds.size;
    NSSize newDrawableSize = [state->view convertSizeToBacking:viewSize];
    state->handle.layer.drawableSize = newDrawableSize;
    state->handle.layer.contentsScale = state->view.window.backingScaleFactor;
    state->device_pixel_ratio = state->handle.layer.contentsScale;
    
    context.data.u16[0] = (uint16_t)newDrawableSize.width;
    context.data.u16[1] = (uint16_t)newDrawableSize.height;
    event_fire(EVENT_CODE_RESIZED, 0, context);
}

- (void)windowDidMiniaturize:(NSNotification *)notification {
    // Send a size of 0, which tells the application it was minimized.
    event_context context;
    context.data.u16[0] = 0;
    context.data.u16[1] = 0;
    event_fire(EVENT_CODE_RESIZED, 0, context);
    
    printf("Mini W: %d\n", context.data.u16[0]);
    printf("Mini H: %d\n", context.data.u16[1]);

    [state->window miniaturize:nil];
}

- (void)windowDidDeminiaturize:(NSNotification *)notification {
    event_context context;
    CGSize viewSize = state->view.bounds.size;
    NSSize newDrawableSize = [state->view convertSizeToBacking:viewSize];
    state->handle.layer.drawableSize = newDrawableSize;
    state->handle.layer.contentsScale = state->view.window.backingScaleFactor;
    state->device_pixel_ratio = state->handle.layer.contentsScale;
    
    context.data.u16[0] = (uint16_t)newDrawableSize.width;
    context.data.u16[1] = (uint16_t)newDrawableSize.height;
    event_fire(EVENT_CODE_RESIZED, 0, context);
    
//    state->window_resized_callback((uint16_t)newDrawableSize.width, (uint16_t)newDrawableSize.height);
    
    [state->window deminiaturize:nil];
}

@end
