#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int sockid = 0;
int client_sock = 5;
void none() {
}

int init_socket() {
    sockid = socket(PF_INET, SOCK_STREAM, 0);
    if (sockid < 0) {
        printf("failed to establish a socket\n");
        return -1;
    }
    return sockid;
}

int start_server() {
    struct sockaddr_in inaddr;
    inaddr.sin_family = AF_INET;
    inaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    inaddr.sin_port = htons(8080);
    int stat = bind(sockid, (struct sockaddr*)&inaddr, sizeof(inaddr));
    if (stat < 0) {
        printf("failed to attach\n");
        exit(-1);
    }
    stat = listen(sockid, 10);
    if (stat < 0) {
        printf("failed to listen\n");
        exit(-1);
    }
    return 0;
}

int accept_clients() {
    struct sockaddr_in clientaddr;
    clientaddr.sin_addr.s_addr = INADDR_ANY;
    socklen_t client_len = sizeof(clientaddr);

    printf("listening on port 8080\n");
    if ((client_sock = accept(sockid, (struct sockaddr*)&clientaddr, &client_len)) < 0) {
        printf("failed to accept a client");
        exit(-1);
    }
    return client_sock;
}

void send_to(void* data) {
    ssize_t sent = send(client_sock, data, strlen(data), 0);
    if (sent > 0)
        printf("sent %ld bytes to socket\n", sockid);

    if (sent < 0) {
        printf("failed to send to socket %d\n", client_sock);
    }
}

char* recv_from() {
    char* data = malloc(256);
    ssize_t recvd = recv(client_sock, data, 256, 0);
    if (recvd <= 0) {
        send_to("empty");
    }
    printf("received %ld bytes from socket %d\n", recvd, client_sock);
    return data;
}

void* pthread_accept() {
    accept_clients();
    return NULL;
}
