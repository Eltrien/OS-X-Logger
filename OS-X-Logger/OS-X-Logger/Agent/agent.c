#include <stdio.h>

int agentinit() {
    for (int i = 0; i < 10; i++){
        printf("im agent ");
        sleep(1);
    }
    return 0;
}