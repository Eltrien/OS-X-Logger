// thread example
//#include <iostream>       // std::cout
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#include "daemon.c"

int main(int argc, const char **argv){
    daemoninit();
    printf("qwerty");
}