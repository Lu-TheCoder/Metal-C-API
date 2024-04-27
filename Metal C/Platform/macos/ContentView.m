//
//  ContentView.m
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/02.
//

#import <Foundation/Foundation.h>
#import "ContentView.h"
#import <QuartzCore/CAMetalLayer.h>

@implementation ContentView

- (instancetype)initWithWindow:(NSWindow *)init_window {
    self = [super init];
    
    if (self != nil){
        window = init_window;
    }
    
    return self;
}

-(BOOL)wantsUpdateLayer {
    return YES;
}

- (BOOL)isOpaque {
    return YES;
}

//MARK: Focus

- (BOOL)canBecomeKeyView {
    return YES;
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

//MARK: Mouse

//MARK: Keyboard

//MARK: Scroll and Pan

//MARK: IME

- (nullable NSAttributedString *)attributedSubstringForProposedRange:(NSRange)range actualRange:(nullable NSRangePointer)actualRange { 
    return nil;
}

- (NSUInteger)characterIndexForPoint:(NSPoint)point { 
    return 0;
}

- (NSRect)firstRectForCharacterRange:(NSRange)range actualRange:(nullable NSRangePointer)actualRange { 
    return NSMakeRect(0, 0, 0, 0);
}

- (BOOL)hasMarkedText { 
    return marked_text.length > 0;
}

- (void)insertText:(nonnull id)string replacementRange:(NSRange)replacementRange { 

}

- (NSRange)markedRange { 
    return NSMakeRange(0, marked_text.length);
}

- (NSRange)selectedRange { 
    static const NSRange kEmptyRange = { NSNotFound, 0 };
    return kEmptyRange;
}

- (void)setMarkedText:(nonnull id)string selectedRange:(NSRange)selectedRange replacementRange:(NSRange)replacementRange { 
    
}

- (void)unmarkText { 
    
}

- (nonnull NSArray<NSAttributedStringKey> *)validAttributesForMarkedText { 
    return [NSArray array];
}

@end
