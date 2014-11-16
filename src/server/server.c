//
//      Tomas Petras Rupsys
//

#include "server.h"

void start_server() {

  // Server variables
  int serverSocket;
  struct sockaddr_in serverAddress;

  // Client that connects variables
  int clientSocket;
  struct sockaddr_in clientAddress;
  socklen_t clientAddressLength;

  // Operation data
  char buffer[MAX_BUFFER_LEN];
  int serverRequestLength;
  int serverResponseLength;

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
  serverAddress.sin_port = htons(SERVER_PORT);       // Accepting port

  // Binding server's address to server's socket
  int bindStatus = bind(
    serverSocket,
    (struct sockaddr *) &serverAddress,
    sizeof(serverAddress));

  if (bindStatus < 0) {
    perror("Failed to bind server's address to server's socket");
    exit(2);
  }

  // Starting to listen to clients to connect
  int startListeningStatus = listen(serverSocket, MAX_CLIENTS);

  if (startListeningStatus < 0) {
    perror("Failed to start listening to clients");
    exit(3);
  }

  // Entering the app lifecycle loop
  while (1) {

    // Refreshing buffer and client's address
    memset(&buffer, 0, sizeof(buffer));
    memset(&clientAddress, 0, sizeof(clientAddress));

    // Awaiting for a new client to connect
    clientAddressLength = sizeof(struct sockaddr);
    int clientAcceptStatus = (clientSocket = accept(
      serverSocket,
      (struct sockaddr*) &clientAddress,
      &clientAddressLength));

    if (clientAcceptStatus < 0) {
      perror("Failed to accept a new connection");
      exit(1);
    }

    // Once connection has been received, reading input
    serverRequestLength = recv(clientSocket, buffer, sizeof(buffer), 0);

    // Process the received message
    char *timeString = calloc(MAX_BUFFER_LEN, sizeof(char));
    get_time(timeString, MAX_BUFFER_LEN);

    // Sending back the same what was sent
    serverResponseLength = send(
      clientSocket,
      timeString,
      strlen(timeString),
      0);

    // Disconnecting from the client
    close(clientSocket);

    // Printing status
    printf(
      "%s - got: %d - sent: %d\n",
      inet_ntoa(clientAddress.sin_addr),
      serverRequestLength,
      serverResponseLength);
  }
}
