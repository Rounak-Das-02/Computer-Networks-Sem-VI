// Author : Rounak Das
// SE20UCSE149

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5555

int main(int argc, char *argv[])
{
    int s, t;
    struct sockaddr_in remote;
    char str[1024];

    if (argc != 2)
    {
        printf("\n Invalid server address");
        exit(0);
    }
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect... to %s\n", argv[0]);

    bzero((char *)&remote, sizeof(remote));
    remote.sin_family = AF_INET;
    remote.sin_port = htons(PORT);
    remote.sin_addr.s_addr = INADDR_ANY;

    char *hello = "Hello from Client";
    while (printf("You : "), fgets(str, 100, stdin), !feof(stdin))
    {
        if (sendto(s, (const char *)str, strlen(str), MSG_CONFIRM, (struct sockaddr *)&remote, sizeof(remote)) == -1)
        {
            perror("send");
            exit(1);
        }

        int len;

        if ((t = recvfrom(s, str, 1024, MSG_WAITALL, (struct sockaddr *)&remote, &len)) > 0)
        {
            str[t] = '\0';
            printf("Server : %s\n", str);
        }
    }

    close(s);
    return 0;
}
