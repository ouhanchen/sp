#include "../net.h"
#include <pthread.h>

#define MAX_CLIENTS 10

typedef struct {
    int socket;
    struct sockaddr_in addr;
} client_t;

client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(const char *message) {
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i]) {
            if (send(clients[i]->socket, message, strlen(message), 0) < 0) {
                perror("send");
                break;
            }
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    char buffer[SMAX];
    client_t *cli = (client_t *)arg;

    while (1) {
        int receive = recv(cli->socket, buffer, SMAX, 0);
        if (receive > 0) {
            buffer[receive] = '\0';
            printf("%s\n", buffer);
            broadcast_message(buffer);
        } else if (receive == 0 || strcmp(buffer, "exit") == 0) {
            printf("Client disconnected\n");
            break;
        } else {
            perror("recv");
            break;
        }
    }

    close(cli->socket);
    free(cli);
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i] == cli) {
            clients[i] = NULL;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int port = (argc >= 2) ? atoi(argv[1]) : PORT;
    net_t net;
    net_init(&net, TCP, SERVER, port, NULL);
    net_bind(&net);
    net_listen(&net);
    printf("Server started on port %d\n", port);

    while (1) {
        int connfd = net_accept(&net);
        if (connfd < 0) {
            perror("accept");
            continue;
        }

        pthread_t tid;
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->socket = connfd;
        cli->addr = net.serv_addr;

        pthread_mutex_lock(&clients_mutex);
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (!clients[i]) {
                clients[i] = cli;
                break;
            }
        }
        pthread_mutex_unlock(&clients_mutex);

        pthread_create(&tid, NULL, handle_client, (void *)cli);
        pthread_detach(tid);
    }

    return 0;
}
