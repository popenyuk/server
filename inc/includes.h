// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef FIRST_TASK_INCLUDES_H
#define FIRST_TASK_INCLUDES_H

#ifdef _WIN32

#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <ws2tcpip.h>

#else
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define INVALID_SOCKET -1
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_CONNECTIONS 1000

#endif //FIRST_TASK_INCLUDES_H
