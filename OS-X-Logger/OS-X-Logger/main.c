//
//  main.c
//  OS-X-Logger
//
//  Created by Eltrien on 3/8/16.
//  Copyright (c) 2016 Eltrien. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "Daemon/daemon.c"
#include "Agent/agent.c"
#include "Server/main.c"

int main(int argc, const char **argv) {
    pid_t pid = fork(); /*Kostil v2*/
    //printf("pid = %i\n",pid);
    if (pid == -1){
        printf("Error]\tAgent was not initialized\n");
    }
    else if (pid == 0){
        printf("[Init]\tAgent was initialized\n");
        agentinit();
    }
    else{
        pid_t pids = fork();
        if (pid == -1){
            printf("[Error]\tServer was not initialized\n");
        }
        else if (pids == 0){
            printf("[Init]\tDaemon was initialized\n");
            daemoninit();

        }
        else{
            printf("[Init]\tServer was initialized\n");
            servermain();
        }
    }
    /*int forkNum = 3, arr[forkNum];
    /*int i1 = fork();
    int i2 = fork();
    printf("i1 = %i\ni2 = %i\n", i1, i2 );*/
    /*Kostyl' v1*/
    //int rep = 1, reps = 1;
    /*        for (int i = 0; i < forkNum; i++){
            printf("i = %i\n", i);
            switch (i) {
                case 0:
                    //arr[i] = fork();
                    if (arr[i] = fork() < 0) {
                        printf("Daemon was not initialized\n");
                    }
                    else {
                        printf("Daemon was initialized\n");
                        daemoninit();
                        exit(i);
                    }
                    //break;
                case 1:
                    //arr[i] = fork();
                    if (arr[i] < 0) {
                        printf("Agent was not initialized\n");
                    }
                    else {
                        printf("Agent was initialized\n");
                        daemoninit();
                        exit(i);
                    }
                case 2:
                    arr[i] = 1;
                    printf("Server was initialized\n");
                    servermain();
                    exit(i);
                default:
                    
                    break;
            }
        //}
    }
    
    /*
    servermain();
    pid_t pidserv = fork(), pid = fork();
    printf("pid = %i\n",pid);
    if (pid == -1){
        printf("fork was not created\n");
    }
    else if (pid == 0){
        printf("fork was created\n");
        agentinit();
    }
    else{
        printf("demon\n");
        daemoninit();
    }
    
    
    
    switch (pid) {
        case -1:
            printf("fork was not created");
            break;
        case 0:
            printf("fork was created\n");
            agentinit();
            break;
        case pidserv:
            printf("server started\n");
            servermain();
            break;
        default:
            printf("demon\n\n");
            daemoninit();
            
    }*/
    return 0;
}
