/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

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
#include <mutex>
#include "Global.h"

string msgToServer;

/**
 * send message to simulator
 * @param address - path of var to set
 * @param val - new value
 */
void sendToClient(const string address, double val) {
//        if(!valifation()){throw..}
    locker.lock();
    msgToServer = "set " + address + " " + to_string(val) + "\r\n";
    locker.unlock();
}

/**
 * Connect to client.
 * @param portNumber
 * @param ipPath
 */
void ConnectClient(int portNumber, string ipPath) {
    cout << "client started" << endl;
    int n, sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

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
    /* Send message to the server */
    while (true) {
        this_thread::sleep_for(0.1s);
        if (!msgToServer.empty()) {
            const char *c = msgToServer.c_str();
            //n = write(sockfd, c, strlen(buffer));
            n = send(sockfd, c, strlen(buffer), MSG_EOR);//todo MSG_OOB?
            locker.lock();
            msgToServer = "";
            locker.unlock();
        }
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }

}

#endif //PROJECT_CLIENT_H
