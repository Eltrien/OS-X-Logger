//
//  main.c
//  SysCalls_testing
//
//  Created by Admin on 23.03.16.
//  Copyright © 2016 Admin. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char * argv[]) {
    int testFile = open("/Users/admin/Desktop/SysCalls_testing/test.txt", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IROTH);
    if(testFile < 0)
        printf("failed to open file!\n");;
    if(write(testFile,"This will be output to testfile.txt\n", 36) != 36)
    {
        write(2, "writing error\n", 40);
        return 1;
    }
    printf("Hello, World!\n");
    return 0;
}
