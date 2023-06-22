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

int main(void)
{
    int s, s2, t, len;
    struct sockaddr_in local, remote;
    char str[1024];

    memset(&local, 0, sizeof(local));
    memset(&remote, 0, sizeof(remote));

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
    int n;
    while (1)
    {

        t = sizeof(remote);
        n = recvfrom(s, str, 1024, MSG_WAITALL, (struct sockaddr *)&remote, &t);
        if (n <= 0)
        {
            if (n < 0)
                perror("recvfrom");
        }

        str[n] = '\0';

        printf("serverecho> %s\n", str);

        char *hello = "Hello from server";

        if (sendto(s, (const char *)hello, strlen(hello), MSG_CONFIRM, (struct sockaddr *)&remote, sizeof(remote)) < 0)
        {
            perror("send");
        }
    }
    close(s);

    return 0;
}
