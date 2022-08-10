#include "csock.h"

int main() {
    init_sock();
    connect_to();
    send_to("client");
    return 0;
}