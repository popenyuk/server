// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "my_server.h"

/*
 * copy data from one my_struct to another
 * make deep copy
 * additional function
 * @param my_new_new_server - new struct in which we will copy data
 * @param my_new_new_server - struct from which we will copy data
 * @return None
 */
void make_copy(my_server *my_new_new_server, my_server my_new_server) {
    init_defaults_parameters_of_server(my_new_new_server);
#ifdef _WIN32
    my_new_new_server->WSAData = my_new_server.WSAData;
#endif
    my_new_new_server->server = my_new_server.server;
    my_new_new_server->server_port = my_new_server.server_port;
    my_new_new_server->addr_len = my_new_server.addr_len;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"


void *server_run(void *my_void_server) {
    my_server *my_new_server = (my_server *) (my_void_server);
    char *len_of_message = (char *) (malloc(2 * sizeof(char)));
    char *type_of_message = (char *) (malloc(sizeof(char)));
    char *message;
    size_t size_of_message;
    while (1) {
        // accept new client
        server_accept_user(my_new_server);
        while (1) {
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            // reveive lenght of message
            read_message_from_client(my_new_server->new_socket, type_of_message, 1);
            switch (type_of_message[0]) {
                char *send_mess;
                case 'd':
                    send_mess = (char *) (malloc(8 * sizeof(char)));
                    sprintf(send_mess, "%d.%d.%d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
                    send_message_to_client(my_new_server->new_socket, send_mess);
                    free(send_mess);
                    break;
                case 't':
                    send_mess = (char *) (malloc(8 * sizeof(char)));
                    sprintf(send_mess, "%d:%d:%d", t->tm_hour, t->tm_min, t->tm_sec);
                    send_message_to_client(my_new_server->new_socket, send_mess);
                    free(send_mess);
                    break;
                case 'h':
                    send_message_to_client(my_new_server->new_socket, "Hello user!");
                    break;
                case 'm':
                    read_message_from_client(my_new_server->new_socket, len_of_message, 2);
                    size_of_message = len_of_message[0] | len_of_message[1] << 8;
                    message = (char *) (malloc(size_of_message * sizeof(char)));
                    read_message_from_client(my_new_server->new_socket, message, size_of_message);
                    size_t size = strlen(message);
                    int number_of_words = 1;
                    if (strlen(message) == 0) {
                        number_of_words = 0;
                    } else {
                        for (size_t index = 0; index < size; ++index) {
                            char letter = *(message + index);
                            if (letter == ' ' || letter == '\n' || letter == '\t') {
                                ++number_of_words;
                            }
                        }
                    }
                    send_mess = (char *) (malloc(2 * sizeof(char)));
                    sprintf(send_mess, "%d", number_of_words);
                    send_message_to_client(my_new_server->new_socket, send_mess);
                    free(send_mess);
                    break;
                case 'q':
                    break;
                default:
                    send_message_to_client(my_new_server->new_socket, "Unknown function!");
                    break;
            }
            if (type_of_message[0] == 'q') {
                break;
            }
        }
    }
}

#pragma clang diagnostic pop

void read_message_from_client(int socket, char *buffer, size_t len_of_buffer) {
    // read message from client
    if (!(recv(socket, buffer, len_of_buffer, 0))) {
        // stop server
        printf("\n Received data Failure \n");
        exit(EXIT_FAILURE);
    }
}

void send_message_to_client(int socket, char *buffer) {
    char *buff = (char *) (malloc(2 * sizeof(char)));
    sprintf(buff, "%lu", strlen(buffer));
    if (!send(socket, buff, 2, 0)) {
        // stop server
        printf("\n Send data Failure \n");
        free(buff);
        exit(EXIT_FAILURE);
    }
    if (!send(socket, buffer, strlen(buffer), 0)) {
        // stop server
        printf("\n Send data Failure \n");
        free(buff);
        exit(EXIT_FAILURE);
    }
    free(buff);
}

void init_server(my_server *my_new_server) {
#ifdef _WIN32
    WSAStartup(MAKEWORD(2, 0), &my_new_server->WSAData);
#endif
    // Creating socket file descriptor
    my_new_server->server = socket(AF_INET, SOCK_STREAM, 0);
    // binds the socket to the address and port number specified in addr
    if (bind(my_new_server->server, (struct sockaddr *) &my_new_server->server_addr, my_new_server->addr_len)) {
        printf("\n\tBind failed \n");
        printf("\tIf you run multithreading server it`s okey that adrdress is used\n\n");
    }
    // puts server socket to passive mode to wait a new client to server
    if (listen(my_new_server->server, MAX_CONNECTIONS)) {
        printf("\n\tChange server status to listen FAILURE \n\n");
        exit(EXIT_FAILURE);
    }
}

void init_defaults_parameters_of_server(my_server *my_new_server) {
    my_new_server->server_addr.sin_family = AF_INET;
    my_new_server->server_addr.sin_addr.s_addr = INADDR_ANY;
    my_new_server->server_addr.sin_port = htons(my_new_server->server_port);
    my_new_server->addr_len = sizeof(my_new_server->server_addr);
}

void server_accept_user(my_server *my_new_server) {
    // accept new user
    while (INVALID_SOCKET ==
           (my_new_server->new_socket = accept(my_new_server->server, (struct sockaddr *) &my_new_server->server_addr,
                                               &my_new_server->addr_len)));
}

void server_start_threads(my_server my_new_server, int number_of_threads) {
    // start threads
#ifdef __linux__
    my_server *my_servers = (my_server *) (malloc(number_of_threads * sizeof(my_server)));
    pthread_t *threads = (pthread_t *) (malloc(number_of_threads * sizeof(pthread_t)));
#elif _WIN32
    my_server *my_servers = (my_server *) (malloc(number_of_threads * sizeof(my_server)));
    HANDLE *threads = (HANDLE *) (malloc(number_of_threads * sizeof(HANDLE)));
#endif

    for (int i = 0; i < number_of_threads; i++) {
#ifdef __linux__
        pthread_create(&threads[i], NULL, server_run, &my_new_server);
#elif _WIN32
        make_copy(&my_servers[i], my_new_server);
        threads[i] = (HANDLE) _beginthread((void (*)(void *)) server_run, 0, &my_servers[i]);
#endif
    }

    for (int i = 0; i < number_of_threads; i++) {
#ifdef __linux__
        pthread_join(threads[i], NULL);
#elif _WIN32
        WaitForSingleObject(threads[i], INFINITE);
#endif
    }

    free(my_servers);
    free(threads);
}
