#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "headers.h"

// ------------------------------
// Create the server socket
// ------------------------------
int startServer(int port) {
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;   // listen on all interfaces
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(1);
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen failed");
        exit(1);
    }

    printf("Waiting for a client to connect on port %d...\n", port);

    client_fd = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (client_fd < 0) {
        perror("accept failed");
        exit(1);
    }

    printf("Client connected!\n");

    close(server_fd); // We only need client socket now
    return client_fd;
}


// ------------------------------
// Connect to server as a client
// ------------------------------
int startClient(const char* ip, int port) {
    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket failed");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Not supported\n");
        exit(1);
    }

    printf("Connecting to server %s:%d...\n", ip, port);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        exit(1);
    }

    printf("Connected!\n");
    return sock;
}


// ------------------------------
// Send a move
// ------------------------------
void sendMove(int sock, int move) {
    send(sock, &move, sizeof(move), 0);
}


// ------------------------------
// Receive a move
// ------------------------------
int receiveMove(int sock) {
    int move;
    int bytes = recv(sock, &move, sizeof(move), 0);

    if (bytes <= 0) {
        printf("Connection closed.\n");
        exit(1);
    }

    return move;
}
