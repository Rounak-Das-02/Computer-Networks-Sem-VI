#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 5555

void *sendingThread(void *argv)
{

    // Need to implement locks.

    char str[1024];

    int *s = (int *)argv;

    while (printf("> "), fgets(str, 1024, stdin), !feof(stdin))
    {
        if (send(*s, str, strlen(str), 0) == -1)
        {
            perror("send");
            exit(1);
        }
    }
}

void *receivingThread(void *argv)
{

    // Need to implement locks.

    int t;
    char str[1024];

    int *s = (int *)argv;
    while (1)
    {

        if ((t = recv(*s, str, 1024, 0)) > 0)
        {
            str[t] = '\0';
            printf("Server :  %s", str);
        }
        else
        {
            if (t < 0)
                perror("recv");
            else
                printf("Server closed connection\n");
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    int s, t, len;
    struct sockaddr_in remote;

    pthread_t tid;

    if (argc != 2)
    {
        printf("\n Invalid server address");
        exit(0);
    }
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect... to %s\n", argv[0]);

    bzero((char *)&remote, sizeof(remote));
    remote.sin_family = AF_INET;
    remote.sin_port = htons(PORT);
    remote.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(s, (struct sockaddr *)&remote, sizeof(remote)) == -1)
    {
        perror("connect");
        exit(1);
    }

    printf("Connected.\n");
    char str[1024];
    int n;

    // pthread_create(&tid, NULL, receivingThread, (void *)&s);

    // pthread_create(&tid, NULL, sendingThread, (void *)&s);

    // pthread_exit(NULL);

    while (1)
    {
        printf("\nYou : ");
        fgets(str, 1024, stdin);
        if (strncmp(str, "EOF", 3) == 0) // Use "EOF" to end communication with server
            break;
        n = send(s, str, 100, 0);
        if (n == -1)
        {
            printf("Error in sending");
            exit(1);
        }
        n = recv(s, str, 1024, 0);
        if (s == -1)
        {
            printf("Error in receiving");
            exit(1);
        }
        printf("Server : %s", str);
    }
    close(s);
    exit(0);
    return 0;
}