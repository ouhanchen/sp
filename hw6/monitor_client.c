#include "../net.h"

int main(int argc, char *argv[]) {
    int port = (argc >= 2) ? atoi(argv[1]) : PORT;
    char *host = (argc >= 3) ? argv[2] : "localhost";
    net_t net;
    net_init(&net, TCP, CLIENT, port, host);
    if (net_connect(&net) < 0) {
        perror("connect");
        return 1;
    }

    char cmd[SMAX], recvBuff[TMAX];
    printf("Connected to server %s\n", net.serv_ip);

    pthread_t recv_thread;
    void *recv_message(void *arg) {
        while (1) {
            int n = read(net.sock_fd, recvBuff, TMAX - 1);
            if (n <= 0) {
                break;
            }
            recvBuff[n] = '\0';
            printf("%s", recvBuff);
        }
        return NULL;
    }

    pthread_create(&recv_thread, NULL, recv_message, NULL);

    while (1) {
        printf("%s $ ", net.serv_ip);
        fgets(cmd, SMAX, stdin);
        write(net.sock_fd, cmd, strlen(cmd));
        if (strncmp(cmd, "exit", 4) == 0) break;
    }

    close(net.sock_fd);
    return 0;
}
