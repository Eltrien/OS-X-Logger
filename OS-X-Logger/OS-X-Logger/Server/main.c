#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *connection_handler(void *);
char *get_name_by_current_time();

int servermain() {
    int sid, client_sock, c;
    struct sockaddr_in server, client;

    // Create socket
    sid = socket(AF_INET, SOCK_STREAM, 0); /*socket(domain, type, protocol); 
                                            domain = AF_INET - internet protokoly;
                                            type = type of the socket - SOCK_STREAM; etot tip obespechvaet posledovatel'nyj, 
                                            dadeshnyj, orientirovannyj na ustanovlenije dvustoronnej svazi potok dannih;
                                            -Takshe est' Datagram socket (poddershivaet dvustoronnij potok dannih; ne garantiruet
                                            chto potok budet posledovatel'nim, nadeshnim, i chto dannije ne budut dublirovat'sja; 
                                            Granici zapisi dannih predopredeleni) i Raw socket (obespechivaet vozmoshnost' polzovatel'skogo 
                                            dostupa k nizleshaschim kommunikacionnim protokolam, poddershivauschim soket-abstrakcii)*/
    if (sid == -1) {
        printf("[Error]\tServer can't create socket\n");
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8000);
    
    // Bind
    if (bind(sid, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("[Error]\tServar failed the binding\n");
        return 1;
    }

    // Listen
    
    listen(sid, 128);  // backlog - size of queue
    
    // Accept and incoming connection
    c = sizeof(struct sockaddr_in);
    pthread_t thread;

    while ((client_sock = accept(sid, (struct sockaddr *)&client,(socklen_t *)&c))) {
        if (client_sock == -1) {
            printf("\t\tWaiting for incoming connections...\n");
        }
        else {
            //printf("clsock = %i\n", client_sock);
            //printf("Connection accepted\n");
            printf("\t\tIP address is: %s\n", inet_ntoa(client.sin_addr));

            if (pthread_create(&thread, NULL, connection_handler,
                           (void *)&client_sock) < 0) {
                perror("[Error]\tServer can't create thread\n");
                return 1;
            }

            //printf("Handler assigned\n");
        }
        
        
    }

    if (client_sock < 0) {
        printf("[Error]\tServer failed to accept connection");
        return 1;
    }

    return 0;
}

void *connection_handler(void *socket_desc) {
    // Get the socket descriptor
    //printf("qwerty\n\n");
    int sock = *(int *)socket_desc;
    int read_size;
    int message_size = 2024;
    //char *message, *filename;
    char client_message[message_size];
    //read_size = recv(sock, client_message, message_size, 0);
    //filename = get_name_by_current_time();
    //FILE *f = fopen(filename, "w");
    //free(filename);

    //int i = 0;
    int testFile = open("/Users/Shared/server.tmp", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IROTH);
    if(testFile < 0) {
        printf("[Error]\tServer failed to open file\n");
    }
    else {
        //printf("File opened\n");
        while ((read_size = recv(sock, client_message, message_size, 0)) > 0) {
            //printf("size = %i\n", sizeof(client_message));
            printf("\t\tMy Message = %s\n", client_message);
            //char mess[read_size]
            if(strcmp(client_message, "")){
                if(write(testFile, strcat(client_message, "\n"), read_size + 1) != read_size + 1)
                {
                    write(2, "[Error]\tServer can't write file\n", 40);
                }
                else {
                    printf("[Note]\tServer updated file\n");
                }
            }
            else{
                printf("[Warn]\tNull was sent\n");
            }
        }
    memset(client_message, 0, message_size);
    }
    if(close(testFile) < 0) {
        printf("[Error]\tServer can't close file\n");
    }
    else {
        //printf("File closed\n");
    }
    return 0;
}