
#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H


#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <string>

using namespace std;

class Client {
    int socketId;
    const string ip;
    int portno;
public:
    Client(const string ip, int port);

    void sendToClient(const string address, double val);

    void static connectClient(int portNumber, string ipPath, int sockfd) {
        int n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
        char buffer[256];

        /* Create a socket point */
//        sockfd = socket(AF_INET, SOCK_STREAM, 0);
//        this->socketId = sockfd;

        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }

        server = gethostbyname(ipPath.c_str());

        if (server == NULL) {
            fprintf(stderr, "ERROR, no such host\n");
            exit(0);
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portNumber);

        /* Now connect to the server */
        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR connecting");
            exit(1);
        }

        /* Now ask for a message from the user, this message
           * will be read by server
        */

        printf("Please enter the message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);

        /* Send message to the server */
        n = write(sockfd, buffer, strlen(buffer));

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        /* Now read server response */
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        printf("%s\n", buffer);
    }
};


#endif //PROJECT_CLIENT_H
