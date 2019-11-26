// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <stdio.h>
#include <stdlib.h>

#include "my_client.h"

int main(int argc, char const *argv[]) {

    //check arguments of program run
    if (argc < 4) {
        printf("Your input %d parameters, but must be at least 3.\n", argc - 1);
        printf("\tExample: client <address> <number> <type_of_message> <message>\n");
        printf("\tWhere address is address of server.\n");
        printf("\tWhere number is PORT number.\n");
        printf("\tWhere message is your message that you send to server.\n");
        exit(EXIT_FAILURE);
    }

    //initialises variables
    my_client my_new_client;
    // init port numbers
    my_new_client.server_port = atoi(argv[2]);
    // read socket port and new socket port, check if server port isn`t equal to new_server_port
    if (!my_new_client.server_port) {
        printf("\n\tInvalid port number \n");
        exit(EXIT_FAILURE);
    }
    if (argv[3][0] == 'm' && argc == 4) {
        printf("\n\tInvalid message!\n");
        exit(EXIT_FAILURE);
    }

    // init structure my_client
    init_defaults_parameters_of_client(&my_new_client);
    init_client(&my_new_client, argv[1]);
    client_run(&my_new_client, argc, argv);

    // close socket
    close_sock(my_new_client.sock);
    return 0;
}
