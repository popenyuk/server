// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef FIRST_TASK_MY_SERVER_H
#define FIRST_TASK_MY_SERVER_H

#include "includes.h"

/*
 * struct my_server - represents my own file descriptor for server
 */
typedef struct my_server {
#ifdef __linux__
    int server;
    struct sockaddr_in server_addr;
#else
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN server_addr;
#endif
    int addr_len;
    int new_socket;
    int server_port;
} my_server;

/*
 * Start processing users one by one
 * Communicate with user by one port to get new port of communication, dir name and number of files
 * Then reinitialized to another port and start transmitting files
 * @param my_void_server - special void * parameter for multithreading - represents my own structure
 * @return None
 */
void *server_run(void *my_void_server);

/*
 * Initialize server
 * Create new socket file descriptor
 * Bind the socket to the address and port number specified in addr
 * Put server socket to passive mode to wait a new client to server
 * @param my_new_server - pointer to existed server
 * @return None
 */
void init_server(my_server *my_new_server);

/*
 * Accept new user from socket
 * @param my_new_server - pointer to existed server
 * @return None
 */
void server_accept_user(my_server *my_new_server);

/*
 * Init default parameters of server instead of system
 * @param my_new_server - pointer to existed server
 * @return None
 */
void init_defaults_parameters_of_server(my_server *my_new_server);

/*
 * Start new threads for server
 * Create and run threads
 * @param my_new_server - pointer to existed server
 * @param number_of_threads - number of threads
 * @return None
 * @Note it is bad idea to create more threads than you have logical cores
 */
void server_start_threads(my_server my_new_server, int number_of_threads);

/*
 * Read message from user
 * @param socket - file descriptor to existed server
 * @param buffer - buffer in which we will read message from user
 * @param len_of_buffer - length of readied buffer
 * @return None
 */
void read_message_from_client(int socket, char *buffer, size_t len_of_buffer);

/*
 * Send message to user
 * @param socket - file descriptor to existed server
 * @param buffer - buffer in which we will read message from user
 * @param len_of_buffer - length of readied buffer
 * @return None
 */
void send_message_to_client(int socket, char *buffer);

#endif //FIRST_TASK_MY_SERVER_H
