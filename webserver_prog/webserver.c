#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define PORT 5131
#define BUFFER_SIZE 1024

sem_t semaphore;

void *process_client(void *newsockfd_ptr) {
    sem_wait(&semaphore);
    int newsockfd = *(int *)newsockfd_ptr;
    free(newsockfd_ptr);

    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);

    int valread = read(newsockfd, buffer, BUFFER_SIZE);
    if (valread < 0) {
        perror("ERROR Reading file");
        close(newsockfd);
        return NULL;
    }

    char *f = buffer + 5;
    *strchr(f, ' ') = 0;

    int opened_fd = open(f, O_RDONLY);

    bzero(buffer, BUFFER_SIZE);
    read(opened_fd, buffer, BUFFER_SIZE);

    char s[BUFFER_SIZE];
    strcpy(s, buffer);
        

    char resp[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n";
        
    strcat(resp, s);
        
    int valwrite = write(newsockfd, resp, strlen(resp));

    if (valwrite < 0) {
        perror("ERROR writing error");
        close(opened_fd);
        close(newsockfd);
        return NULL;
    }

    close(opened_fd);
    close(newsockfd);
    sem_post(&semaphore);
    return NULL;
}


int main()
{
    pthread_t tid;
    char buffer[BUFFER_SIZE];
    sem_init(&semaphore, 0, 1);

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("ERROR webserver socket did not start successfully");
        return 1;
    }
    printf("Socket created successfully\n");

    struct sockaddr_in server_addr;
    int server_addrlen = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);

    if (bind(socketfd, (struct sockaddr *)&server_addr, server_addrlen) < 0)
    {
        perror("ERROR Binding unsuccessfull");
        exit(1);
    }
    printf("Socket successfully bound to address\n");

    int SOCKMAXCONN = 5;
    if (listen(socketfd, SOCKMAXCONN) < 0)
    {
        perror("ERROR listening failed");
    }

    while (1)
    {
        int *newsockfd_ptr = malloc(sizeof(int));
        if (newsockfd_ptr == NULL) {
            perror("ERROR allocating memory");
            continue;
        }

        *newsockfd_ptr = accept(socketfd, (struct sockaddr *)&server_addr, (socklen_t *)&server_addrlen);
        if (*newsockfd_ptr < 0) {
            perror("ERROR on accepting");
            free(newsockfd_ptr);
            continue;
        }
        printf("Connection Accepted\n");

        pthread_create(&tid, NULL, process_client, (void *)newsockfd_ptr);

        int sockn = getpeername(*newsockfd_ptr, (struct sockaddr *)&client_addr, (socklen_t *)&client_addrlen);

        if (sockn < 0)
        {
            perror("ERRROR in client");
            return 0;
        }

   }
   sem_destroy(&semaphore);

    return 0;
}