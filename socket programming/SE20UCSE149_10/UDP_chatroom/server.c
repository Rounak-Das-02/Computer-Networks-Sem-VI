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

    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1) // Creating a socket
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

    printf("Server is Up and Running.\n");

    int done, n;

    while (1)
    {
        t = sizeof(remote);
        n = recvfrom(s, str, 1024, MSG_WAITALL, (struct sockaddr *)&remote, &t);
        if (n == -1)
        {
            printf("Error in receiving");
            close(s2);
            close(s);
            exit(1);
        }
        printf("Client : %s", str);
        printf("\nYou : ");

        fgets(str, 1024, stdin);
        if (strncmp(str, "EOF", 3) == 0)
            break;

        n = sendto(s, (const char *)str, strlen(str), MSG_CONFIRM, (struct sockaddr *)&remote, sizeof(remote));
        if (n == -1)
        {
            printf("Error in sending");
            close(s2);
            close(s);
            exit(1);
        }
    }
    close(s2);

    return 0;
}
