//
//  ApplicationDelegate.m
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/02.
//

#import <Foundation/Foundation.h>
#import "ApplicationDelegate.h"

@implementation ApplicationDelegate

-(instancetype)init
{
    self = [super init];
    return self;
}

-(void)applicationWillFinishLaunching:(NSNotification *)notification
{
    
}

-(void)applicationDidFinishLaunching:(NSNotification *)notification
{
    // Posting an empty event at start
    @autoreleasepool {

    NSEvent* event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                        location:NSMakePoint(0, 0)
                                   modifierFlags:0
                                       timestamp:0
                                    windowNumber:0
                                         context:nil
                                         subtype:0
                                           data1:0
                                           data2:0];
    [NSApp postEvent:event atStart:YES];

    } // autoreleasepool

    [NSApp stop:nil];
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    
}


@end
