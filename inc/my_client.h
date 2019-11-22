// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef FIRST_TASK_MY_CLIENT_H
#define FIRST_TASK_MY_CLIENT_H

#include "includes.h"

/*
 * struct my_client - represents my own file descriptor for client
 */
typedef struct my_client {
#ifdef __linux__
    int sock;
    struct sockaddr_in addr;
#else
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN addr;
#endif
    int addrlen;
    int server_port;
} my_client;

/*
 * Close existed socket
 * @param socket - file descriptor to existed socket
 * @return None
 */
void close_sock(int sock);

/*
 * Initialize client
 * Create new socket file descriptor
 * @param my_new_client - pointer to existed client
 * @return None
 */
void init_client(my_client *my_new_client, const char *address);

/*
 * Connect user to server
 * @param my_new_client - pointer to existed client
 * @return None
 */
void client_connect_to_server(my_client *my_new_client);

/*
 * Change connection port
 * @param my_new_client - pointer to existed client
 * @new_port - new port number
 * @return None
 */
void change_port(my_client *my_new_client, int new_port);

/*
 * Waiting for connection to server
 * Server can`t change port in moment so that we must wait for him response
 * @param my_new_client - pointer to existed client
 * @return None
 */
void wait_for_response_from_server(my_client *my_new_client);

/*
 * Send message from client to server
 * @param my_void_server - special void * parameter for multithreading - represents my own structure
 * @param message - message which we will transmit to server
 * @return None
 */
void send_message_from_client(int socket, const char *message);

/*
 * Init default parameters of server instead of system
 * @param my_new_client - pointer to existed client
 * @return None
 */
void init_defaults_parameters_of_client(my_client *my_new_client);

/*
 * Client run
 * Communicate with user by one port to get new port of communication, dir name and number of files
 * Then reinitialized to another port and start transmitting files
 * @param my_new_client - pointer to existed client
 * @param argc - number of arguments(length of argv)
 * @param argv - char arguments of run main function
 * @return None
 */
void client_run(my_client *my_new_client, int argc, const char *argv[]);

#endif //FIRST_TASK_MY_CLIENT_H
