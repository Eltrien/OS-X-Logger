#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <pcap.h>
#include <stdio.h>
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
        //printf("im working with files\n");
        sleep(2);
    }
    return NULL;
}

int ThrdFileSend(void *thrd_id) {
    /*for (int i = 5; i > 0; i--){
        printf("i = %i\n", i);
        sleep(1);
    }*/
    //sleep(30);
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
        printf("[error]\tConnecting to server\n");
        return -1;
    }
    
    /*
    // Get size of tar file
    struct stat st;
    stat(filename, &st);
    int size = st.st_size;
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    
    // File to buffer
    int tmp = 0;
    unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char) * size);
    memset(buffer, 0, size);
    FILE *f = fopen(filename, "rb");
    for (int i = 0; i < size; ++i) {
        unsigned char c = getc(f);
        buffer[i] = c;
        if (c == 0) {
            n = write(sockfd, buffer + tmp, strlen((char*)buffer + tmp) + 1);
            tmp = i + 1;
        }
    }
    fclose(f);
    free(buffer);
    */
    n = write(sockfd, "test", 5);
    if (n < 0) return -1;
    
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
    pthread_create(&thrds[2], NULL, ThrdFileSave, &thrds[2]);
    pthread_create(&thrds[3], NULL, ThrdFileSend, &thrds[3]);
    for (int i = 0; i < thrNum; i++) {
        pthread_join(thrds[i], NULL);
    }
    return 0;
}