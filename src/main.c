#pragma clang diagnostic ignored "-Weverything"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 43594
#define MAX_CONNS 10

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed.\n");
        exit(0);
    }

    struct sockaddr_in server_addr, client_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        printf("Bind creation failed.\n");
        return 0;
    }

    if (listen(sockfd, MAX_CONNS) == -1) {
        printf("Socket listening failed.\n");
        return 0;
    };

    printf("Server listening on port %d.\n", PORT);
    socklen_t client_len;

    while (true) {
        client_len = sizeof(client_addr);

        int new_connfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);

        if (new_connfd == -1) {
            printf("Server accept failed.\n");
            return 0;
        }

        printf("Someone connected!\n");
    }

    return 0;
}
