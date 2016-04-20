#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

/*void *PosixThreadMainRoutine(void *thrd_id)
{
    int i = 0;
    printf("I'm alive\n");
    fflush(stdout);
    while (i++ < 5)
    {
        printf("[%llx] num = %d\n", *(unsigned long long *) thrd_id, i);
    }
    return NULL;
    
}*/

void *ThrdGetInfo(void *thrd_id)
{
    for(int i = 0; i < 10; i++){
        printf("im getting info\n");
        sleep(1);
    }
    return NULL;
}

void *ThrdFileSave(void *thrd_id)
{
    int testFile = open("/Users/Eltrien/OS-X-Logger/OS-X-Logger/OS-X-Logger/test.txt", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IROTH);
    if(testFile < 0) {
        printf("failed to open file!\n");
    }
    else {
        printf("File opened\n");
        if(write(testFile,"This will be output to testfile.txt\n", 36) != 36)
        {
            write(2, "writing error\n", 40);
        }
        else {
            printf("File written\n");
        }
        if(close(testFile) < 0) {
            printf("File didnt close\n");
        }
        else {
            printf("File closed\n");
        }
        
    }
    for(int i = 0; i < 10; i++){
        printf("im working with files\n");
        sleep(2);
    }
    return NULL;
}

int daemoninit() {
    int thrNum = 2;
    pthread_t thrds[thrNum]; /* 1thrd = getinfo; 2tgrd = saveintofile*/
    /*int i;
    for (i = 0; i < 10; i++) {
        pthread_create(&thrds[i], NULL, PosixThreadMainRoutine, &thrds[i]);
        printf("Start thread: %llx\n", (unsigned long long) thrds[i]);
    }
    for (i = 0; i < 10; i++) {
        pthread_join(thrds[i], NULL);
    }
    printf("Finish\n\n");
    */
    
    pthread_create(&thrds[1], NULL, ThrdGetInfo, &thrds[1]);
    pthread_create(&thrds[2], NULL, ThrdFileSave, &thrds[2]);
    for (int i = 0; i < thrNum; i++) {
        pthread_join(thrds[i], NULL);
    }
    return 0;
}