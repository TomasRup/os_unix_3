//
//      Tomas Petras Rupsys
//

#include "server.h"

void start_server() {

  // Server variables
  unsigned int serverPort = SERVER_PORT;
  int serverSocket;
  struct sockaddr_in serverAddress;

  // Client that connects variables
  int clientSocket;
  struct sockaddr_in clientAddress;
  socklen_t clientAddressLength;

  // Operation data
  char buffer[MAX_BUFFER_LEN];
  int sendLength;
  int readLength;

  // Initializing server socket
  serverSocket = socket(
    AF_INET,     // IPv4 internet protocols
    SOCK_STREAM, // Sequenced, reliable, two-way connection-based byte streams
    0);          // Default protocol

  if (serverSocket < 0) {
    perror("Failed to initialize server socket");
    exit(1);
  }

  // Initializing server address
  memset(&serverAddress, 0, sizeof(serverAddress));  // Clearing
  serverAddress.sin_family = AF_INET;                // IPv4
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Any address accepted
  serverAddress.sin_port = htons(serverPort);        // Accepting port

  // Binding server's address to server's socket
  int bindCode = bind(
    serverSocket,
    (struct sockaddr *) &serverAddress,
    sizeof(serverAddress));

  if (bindCode < 0) {
    perror("Failed to bind server's address to server's socket");
    exit(2);
  }

  // Entering the app lifecycle loop
  while (1) {

  }
}
