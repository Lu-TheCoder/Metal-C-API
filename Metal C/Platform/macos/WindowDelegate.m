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
    return YES;
}

- (void)windowDidChangeScreen:(NSNotification *)notification {
    CGSize viewSize = state->view.bounds.size;
    NSSize newDrawableSize = [state->view convertSizeToBacking:viewSize];
    state->handle.layer.drawableSize = newDrawableSize;
    state->handle.layer.contentsScale = state->view.window.backingScaleFactor;
    state->device_pixel_ratio = state->handle.layer.contentsScale;
}

- (void)windowDidResize:(NSNotification *)notification {
    CGSize viewSize = state->view.bounds.size;
    NSSize newDrawableSize = [state->view convertSizeToBacking:viewSize];
    state->handle.layer.drawableSize = newDrawableSize;
    state->handle.layer.contentsScale = state->view.window.backingScaleFactor;
    state->device_pixel_ratio = state->handle.layer.contentsScale;
}

- (void)windowDidMiniaturize:(NSNotification *)notification {

}

- (void)windowDidDeminiaturize:(NSNotification *)notification {
    CGSize viewSize = state->view.bounds.size;
    NSSize newDrawableSize = [state->view convertSizeToBacking:viewSize];
    state->handle.layer.drawableSize = newDrawableSize;
    state->handle.layer.contentsScale = state->view.window.backingScaleFactor;
    state->device_pixel_ratio = state->handle.layer.contentsScale;
}

@end
