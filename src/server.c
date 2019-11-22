// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <stdio.h>
#include <stdlib.h>
#include "my_server.h"

int main(int argc, char const *argv[]) {
    //check arguments of program run
    if (argc != 3) {
        printf("Your input %d parameters, but must be 3.\n\tExample: server <number> <number of threads>\n", argc - 1);
        printf("\tWhere number is PORT number\n");
        exit(EXIT_FAILURE);
    }

    // init parameters
    struct my_server my_new_server;
    // read server port
    if (!(my_new_server.server_port = atoi(argv[1]))) {
        printf("\n Invalid port number \n");
        exit(EXIT_FAILURE);
    }

    // init structure my_server
    init_defaults_parameters_of_server(&my_new_server);
    init_server(&my_new_server);

    // run server with copy of parameters
    server_start_threads(my_new_server, atoi(argv[2]));

    return 0;
}
