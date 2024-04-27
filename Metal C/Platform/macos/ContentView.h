//
//  ContentView.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/02.
//

#pragma once
#import <Cocoa/Cocoa.h>

@interface ContentView : NSView <NSTextInputClient> {
    NSWindow* window;
    NSTrackingArea* tracking_area;
    NSMutableAttributedString* marked_text;
}

- (instancetype)initWithWindow:(NSWindow*)init_window;

@end
