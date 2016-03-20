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

int main(int argc, const char **argv) {
    int pid;
    pid = fork();
    printf("pid = %i",pid);
    if (pid == -1){
        printf("fork was not created");
    }
    else if (pid == 0){
        printf("fork was created\n");
        agentinit();
    }
    else{
        daemoninit();
    }
    return 0;
}
