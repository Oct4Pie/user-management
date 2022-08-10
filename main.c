#include <pthread.h>
#include <unistd.h>
#include "ssock.h"

void* handle_server() {
    int sock_id = init_socket();
    int c_sock = 1;
    start_server();
    while (c_sock) {
        c_sock = accept_clients();
        char* data = recv_from();
        printf("data %s\n", data);
    }

    return NULL;
}

int main() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, handle_server, NULL);
    while (1) {
        sleep(1000);
    }
    return 0;
}