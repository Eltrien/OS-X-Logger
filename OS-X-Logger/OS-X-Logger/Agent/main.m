//
//  main.m
//  IWU_agent
//
//  Created by Admin on 03.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import "logging.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        
        NSString *s = @"asdasd";
        NSError *error = nil;
        BOOL flag = [s writeToFile:@"/Users/admin/Desktop/IWU_agent/test.txt"
            atomically:YES
              encoding:NSUTF8StringEncoding
                 error:&error];
        if (!flag) NSLog(@"%@", error.localizedDescription);
        NSData *eye = [NSData dataWithContentsOfFile:@"/Users/admin/Desktop/IWU_agent/eye.jpg"];
        [eye writeToFile:@"/Users/admin/Desktop/IWU_agent/new_eye.jpg"
              atomically:YES];
        NSLog(@"yes, my Lord!\n");
        
        
        //keylogger
        
        
    }
    return NSApplicationMain(argc, (const char **)argv);;
}
