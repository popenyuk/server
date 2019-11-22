// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "my_client.h"

void close_sock(int sock) {
#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
}

void init_client(my_client *my_new_client, const char *address) {
#ifdef _WIN32
    WSAStartup(MAKEWORD(2, 0), &my_new_client->WSAData);
#endif
    // create socket
    my_new_client->sock = socket(AF_INET, SOCK_STREAM, 0);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, address, &my_new_client->addr.sin_addr) <= 0) {
        printf("\n Invalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
}

void client_connect_to_server(my_client *my_new_client) {
    // coonect file socket descriptor and adress speciavied by adress
    if (INVALID_SOCKET ==
        connect(my_new_client->sock, (struct sockaddr *) &my_new_client->addr, my_new_client->addrlen)) {
        printf("\n Connection Failed \n");
        exit(EXIT_FAILURE);
    }
}

void init_defaults_parameters_of_client(my_client *my_new_client) {
    my_new_client->addr.sin_family = AF_INET;
    my_new_client->addr.sin_port = htons(my_new_client->server_port);
    my_new_client->addrlen = sizeof(my_new_client->addr);
}

void send_message_from_client(int socket, const char *message) {
    if (!send(socket, message, strlen(message), 0)) {
        printf("\n Send data FAILURE \n");
        exit(EXIT_FAILURE);
    }
}

void recv_message_from_server(int socket, char *message) {
    free(message);
    message = (char *) (malloc(2 * sizeof(char)));
    if (!recv(socket, message, 2, 0)) {
        printf("\n Send data FAILURE \n");
        exit(EXIT_FAILURE);
    }
    size_t len_of_buffer = atoi(message);
    free(message);
    message = (char *) (malloc(len_of_buffer * sizeof(char)));
    if (!recv(socket, message, len_of_buffer, 0)) {
        printf("\n Send data FAILURE \n");
        exit(EXIT_FAILURE);
    }
    *(message + len_of_buffer) = '\0';
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void client_run(my_client *my_new_client, int argc, const char **argv) {
    char *len_of_message = (char *) (malloc(2 * sizeof(char)));
    char *str = (char *) (malloc(2048 * sizeof(char)));
    // connect to server
    client_connect_to_server(my_new_client);

    send_message_from_client(my_new_client->sock, argv[3]);
    if (argc == 5) {
        sprintf(len_of_message, "%lu", strlen(argv[4]));
        send_message_from_client(my_new_client->sock, len_of_message);
        send_message_from_client(my_new_client->sock, argv[4]);
    }
    recv_message_from_server(my_new_client->sock, str);
    printf("%s\n", str);
    while (1) {
        scanf("%99[^\n]%*c", str);
        if (strlen(str) == 1 && str[0] == 'm') {
            send_message_from_client(my_new_client->sock, str);
            scanf("%99[^\n]%*c", str);
            sprintf(len_of_message, "%lu", strlen(str));
            send_message_from_client(my_new_client->sock, len_of_message);
        }
        send_message_from_client(my_new_client->sock, str);
        if (strlen(str) == 1 && str[0] == 'q') {
            break;
        }
        recv_message_from_server(my_new_client->sock, str);
        printf("%s\n", str);
    }
    free(len_of_message);
    free(str);
}

#pragma clang diagnostic pop
