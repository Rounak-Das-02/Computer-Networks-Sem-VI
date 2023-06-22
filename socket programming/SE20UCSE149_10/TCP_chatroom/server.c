#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>

#define PORT 5555

int s2, s;

void INThandler(int sig)
{
    close(s2);
    close(s);
    exit(0);
}

void *sendingThread(void *argv)
{

    char str[1024];

    int *s = (int *)argv;

    while (printf("> "), fgets(str, 1024, stdin), !feof(stdin))
    {
        int n;
        // printf("You :  %s\n", str);
        if (send(s, str, strlen(str), 0) < 0)
        {
            perror("send");
            break;
        }
    }
}

void *receivingThread(void *argv)
{
    int t;
    char str[1024];

    int *s = (int *)argv;
    while (1)
    {
        int n = recv(s, str, 1024, 0);
        if (n <= 0)
        {
            if (n < 0)
            {
                perror("recv");
                break;
            }
        }
        else
        {
            printf("Client :  %s\n", str);
        }
    }
}

int main(void)
{

    signal(SIGINT, INThandler);

    int t, len;
    struct sockaddr_in local, remote;
    char str[1024];

    pthread_t tid;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) // Creating a socket
    {
        perror("socket creation failed…\n");
        exit(1);
    }

    bzero((char *)&local, sizeof(local));
    local.sin_family = AF_INET;                // Address Family
    local.sin_port = htons(PORT);              // Port of server to bind
    local.sin_addr.s_addr = htonl(INADDR_ANY); // Local Host for now

    if (bind(s, (struct sockaddr *)&local, sizeof(local)) == -1)
    {
        perror("bind");
        exit(1);
    }

    if (listen(s, 5) == -1)
    {
        perror("listen");
        exit(1);
    }

    int done, n;
    printf("Waiting for a connection...\n");
    t = sizeof(remote);
    if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1)
    {
        perror("accept");
        exit(1);
    }

    printf("Connected.\n");

    while (1)
    {
        n = recv(s2, str, 1024, 0);
        if (n == -1)
        {
            printf("Error in receiving");
            exit(1);
        }
        printf("Client : %s", str);
        printf("\nYou : ");
        fgets(str, 1024, stdin);
        if (strncmp(str, "EOF", 3) == 0)
            break;
        n = send(s2, str, 1024, 0);
        if (n == -1)
        {
            printf("Error in sending");
            exit(1);
        }
    }
    close(s2);

    // pthread_create(&tid, NULL, receivingThread, (void *)&s2);

    // pthread_create(&tid, NULL, sendingThread, (void *)&s2);

    // pthread_exit(NULL);

    return 0;
}
