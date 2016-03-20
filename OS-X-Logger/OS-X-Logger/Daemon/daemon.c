#include <stdio.h>

int daemoninit() {
    for (int i = 0; i < 10; i++) {
        printf("im daemon ");
        sleep(1);
    }
    return 0;
}