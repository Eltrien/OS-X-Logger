#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


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
    for(int i = 0; i < 2; i++){
        //printf("im getting info\n");
        sleep(1);
    }
    return NULL;
}

void *ThrdFileSave(void *thrd_id)
{
    int testFile = open("/Users/Shared/daemon.tmp", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IROTH);
    if(testFile < 0) {
        printf("[Error]\tDaemon can't open file\n");
    }
    else {
        //printf("File opened\n");
        if(write(testFile,"This will be output to testfile.txt\n", 36) != 36)
        {
            write(2, "[Error]\tDaemon can't write file\n", 40);
        }
        else {
            //printf("File written\n");
        }
        if(close(testFile) < 0) {
            printf("[Error]\tDaemon can't close file\n");
        }
        else {
            //printf("File closed\n");
        }
        
    }
    return NULL;
}

int ThrdFileSend(void *thrd_id) {
    
    //Read info
    char *str;
    int trytick = 3;
    ssize_t stractsize;
    while (trytick > 0) {
        int testFile = open("/Users/Shared/daemon.tmp", O_RDONLY);
        if(testFile < 0) {
            printf("[Error]\tDaemon can't open file. Retrying %i\n", trytick);
            trytick--;
            sleep(1);
        }
        else {
            ssize_t ret = 1;
            int stractsize = 0, strsize = 64;
            char ch;
            str = (char*) malloc(strsize * sizeof(char));
            trytick = -1;
            //printf("File opened\n");
            //printf("ret = %zi\n", read(testFile, &ch, 1));
            
            while ((ret = read(testFile, &ch, 1)) > 0)
            {
                if (stractsize >= strsize - 1){
                    strsize *= 2;
                    str = (char*) realloc(str, strsize);
                }
                str[stractsize] = ch;
                stractsize++;
            }
            
            //printf("i = %i\n", stractsize);
            //printf("sizeof = %i\n", sizeof(str));
            for (int a = 0; a <= stractsize; a++){
                //printf("%c",str[a]);
            }
            if(close(testFile) < 0) {
                printf("[Error]\tDaemon can't close file\n");
            }
            else {//printf("File closed\n");
            }
            testFile = open("/Users/Shared/daemon.tmp", O_TRUNC);
            close(testFile);
        }
    }
    
    //Send info
    //sleep(5);
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    portno = 8000;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return -1;
    
    server = gethostbyname("127.0.0.1");
    if (server == NULL) return -1;
    
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    
    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("[Error]\tConnecting to server\n");
        free(str);
        return -1;
    }
    n = write(sockfd, str, strlen((char*)str) + 1);
    if (n < 0) {
        printf("[Error]\tDaemon can't send info\n");
        free(str);
        return -1;
    }

    close(sockfd);
    free(str);
    return 0;
}

int daemoninit() {
    int thrNum = 3;
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
    //pthread_create(&thrds[2], NULL, ThrdFileSave, &thrds[2]);
    pthread_create(&thrds[3], NULL, ThrdFileSend, &thrds[3]);
    for (int i = 0; i < thrNum; i++) {
        pthread_join(thrds[i], NULL);
    }
    return 0;
}