//
//  platform_macos.m
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/02.
//

#import <Foundation/Foundation.h>
#import "../platform.h"
#import "ApplicationDelegate.h"
#import "WindowDelegate.h"
#import "ContentView.h"
#import <Metal/Metal.h>
#import <QuartzCore/CoreAnimation.h>
#import "../../Engine/core/event.h"

static platform_state* state_ptr;

bool platform_system_startup(platform_system_config* config){
    
    state_ptr = malloc(sizeof(platform_state));
    
    state_ptr->device_pixel_ratio = 1.0f;
    
    @autoreleasepool {
        
        [NSApplication sharedApplication];
        
        state_ptr->app_delegate = [[ApplicationDelegate alloc] init];
        if(!state_ptr->app_delegate){
            NSLog(@"Failed to create Application delegate.");
            return false;
        }
        
        [NSApp setDelegate:state_ptr->app_delegate];
        
        state_ptr->wnd_delegate = [[WindowDelegate alloc] initWithState:state_ptr];
        if (!state_ptr->wnd_delegate){
            NSLog(@"Failed to create Window delegate.");
            return false;
        }
        
        state_ptr->window = [[NSWindow alloc]
                             initWithContentRect:NSMakeRect(config->x, config->y, config->width, config->height)
                             styleMask:NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable
                             backing:NSBackingStoreBuffered
                             defer:NO];
        if (!state_ptr->window){
            NSLog(@"Failed to create Window window");
            return false;
        }
        
        state_ptr->view = [[ContentView alloc] initWithWindow:state_ptr->window];
        [state_ptr->view setWantsLayer:YES];
        
        // Layer creation
        state_ptr->handle.layer = [CAMetalLayer layer];
        state_ptr->handle.layer.frame = state_ptr->window.contentView.frame;
        state_ptr->handle.layer.device = MTLCreateSystemDefaultDevice();
        state_ptr->handle.layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        
        if (!state_ptr->handle.layer) {
            NSLog(@"Failed to create layer for view");
        }
        
        //Window properties
        [state_ptr->window setLevel:NSNormalWindowLevel];
        [state_ptr->window setContentView:state_ptr->view];
        [state_ptr->window.contentView.layer addSublayer:state_ptr->handle.layer];
        [state_ptr->window makeFirstResponder:state_ptr->view];
        [state_ptr->window setTitle:@(config->application_name)];
        [state_ptr->window setDelegate:state_ptr->wnd_delegate];
        [state_ptr->window setAcceptsMouseMovedEvents:YES];
        [state_ptr->window setRestorable:NO];
        
        // Handle content scaling for various fidelity displays (i.e. Retina)
        state_ptr->handle.layer.bounds = state_ptr->view.bounds;
        // It's important to set the drawableSize to the actual backing pixels. When rendering
        // full-screen, we can skip the macOS compositor if the size matches the display size.
        state_ptr->handle.layer.drawableSize = [state_ptr->view convertSizeToBacking:state_ptr->view.bounds.size];

        // In its implementation of vkGetPhysicalDeviceSurfaceCapabilitiesKHR, MoltenVK takes into
        // consideration both the size (in points) of the bounds, and the contentsScale of the
        // CAMetalLayer from which the Vulkan surface was created.
        // See also https://github.com/KhronosGroup/MoltenVK/issues/428
        state_ptr->handle.layer.contentsScale = state_ptr->view.window.backingScaleFactor;
        NSLog(@"contentScale: %f", state_ptr->handle.layer.contentsScale);
        // Save off the device pixel ratio.
        state_ptr->device_pixel_ratio = state_ptr->handle.layer.contentsScale;

        state_ptr->handle.layer.opaque = YES;
        
        [state_ptr->view setLayer:state_ptr->handle.layer];

        if (![[NSRunningApplication currentApplication] isFinishedLaunching])
                [NSApp run];
        
        // Making the app a proper UI app since we're unbundled
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        
        // Putting window in front on launch
        [NSApp activateIgnoringOtherApps:YES];
        [state_ptr->window makeKeyAndOrderFront:nil];
        
//        // Handle content scaling for various fidelity displays (i.e. Retina)
//        state_ptr->handle.layer.bounds = state_ptr->view.bounds;
//        // It's important to set the drawableSize to the actual backing pixels. When rendering
//        // full-screen, we can skip the macOS compositor if the size matches the display size.
//        state_ptr->handle.layer.drawableSize = [state_ptr->view convertSizeToBacking:state_ptr->view.bounds.size];
//
//        // In its implementation of vkGetPhysicalDeviceSurfaceCapabilitiesKHR, MoltenVK takes into
//        // consideration both the size (in points) of the bounds, and the contentsScale of the
//        // CAMetalLayer from which the Vulkan surface was created.
//        // See also https://github.com/KhronosGroup/MoltenVK/issues/428
//        state_ptr->handle.layer.contentsScale = state_ptr->view.window.backingScaleFactor;
//        NSLog(@"contentScale: %f", state_ptr->handle.layer.contentsScale);
//        // Save off the device pixel ratio.
//        state_ptr->device_pixel_ratio = state_ptr->handle.layer.contentsScale;
//
//       [state_ptr->view setLayer:state_ptr->handle.layer];
        
        
        
//        NSOperatingSystemVersion ver = [NSProcessInfo processInfo].operatingSystemVersion;
//        NSLog(@"%@", [NSProcessInfo processInfo].operatingSystemVersionString);
//        NSLog(@"%d.%d.%d", (int64_t)ver.majorVersion, (int64_t)ver.minorVersion, (int64_t)ver.patchVersion);
//        
        [NSApp finishLaunching];
        
        // Fire off a resize event to make sure the framebuffer is the right size.
        // Again, this should be the actual backing framebuffer size (taking into account pixel density).
        event_context context;
        context.data.u16[0] = (uint16_t)state_ptr->handle.layer.drawableSize.width;
        context.data.u16[1] = (uint16_t)state_ptr->handle.layer.drawableSize.height;
        event_fire(EVENT_CODE_RESIZED, 0, context);
        
        return true;
    }
    
}

void platform_system_shutdown(void){
    if (state_ptr){
        @autoreleasepool {
            [state_ptr->wnd_delegate release];
            [state_ptr->view release];
            [state_ptr->app_delegate release];
        }
    }
    free(state_ptr);
    state_ptr = 0;
}

bool platform_pump_messages(void){
    if (state_ptr) {
        @autoreleasepool {
            
            NSEvent* event;
            
            for (;;) {
                event = [NSApp
                         nextEventMatchingMask:NSEventMaskAny
                         untilDate:[NSDate distantPast]
                         inMode:NSDefaultRunLoopMode
                         dequeue:YES];
                
                if (!event)
                    break;
                
                [NSApp sendEvent:event];
            }
            
        } // autoreleasepool
        
        return !state_ptr->quit_flagged;
    }
    return true;
}

void* platform_get_next_drawable(void) {
    return (void*)[state_ptr->handle.layer nextDrawable];
}

unsigned long platform_get_drawable_width(void) {
    return state_ptr->handle.layer.drawableSize.width;
}

unsigned long platform_get_drawable_height(void) {
    return state_ptr->handle.layer.drawableSize.height;
}

unsigned long platform_get_drawable_pixelFormat(void) {
    return state_ptr->handle.layer.pixelFormat;
}

void* platform_get_next_drawable_texture(void* drawable) {
    return [((id<CAMetalDrawable>)drawable) texture];
}

