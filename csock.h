#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int sockid = 0;

int init_sock() {
    sockid = socket(PF_INET, SOCK_STREAM, 0);
    if (sockid < 0) {
        printf("failed to establish a socket");
        return -1;
    }
    return sockid;
}

int connect_to() {
    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    server_addr.sin_port = htons(8080);
    server_addr.sin_family = AF_INET;
    if (connect(sockid, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("failed to connect to socket %d", sockid);
        return -1;
    }
    return 0;
}

char* recv_from() {
    char* data = malloc(256);
    ssize_t recvd = recv(sockid, data, 256, 0);
    if (recvd <= 0) {
        send_to("empty");
    }
    printf("received %ld bytes from socket %d\n", recvd, sockid);
    return data;
}

void send_to(void* data) {
    ssize_t sent = send(sockid, data, strlen(data), 0);
    if (sent > 0)
        printf("sent %ld bytes to socket\n", sockid);

    if (sent < 0) {
        printf("failed to send to socket %d\n", sockid);
    }
}