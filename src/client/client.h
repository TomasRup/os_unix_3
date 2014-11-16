//
//      Tomas Petras Rupsys
//

#ifndef client_H
#define client_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER_LEN 1024
#define SERVER_PORT 65000

void start_client();

#endif
