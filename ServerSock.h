/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#ifndef PROJECT_SERVERSOCK_H
#define PROJECT_SERVERSOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <cstdlib>
#include <map>
#include <chrono>
#include "OpenServerCommand.h"


class ServerSock : public OpenServerCommand {
public:
    void static
    openServer(int portNumber, int myHz, map<string, string> pathMapServer, map<string, double> &valMapServer) {
        cout << "try to connect.." << endl;
        int sockfd, newsockfd, clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        int n;

        /* First call to socket() function */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }

        /* Initialize socket structure */
        bzero((char *) &serv_addr, sizeof(serv_addr));


        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portNumber);

        /* Now bind the host address using bind() call.*/
        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR on binding");
            exit(1);
        }

        /* Now start listening for the clients, here process will
           * go in sleep mode and will wait for the incoming connection
        */

        listen(sockfd, myHz);
        clilen = sizeof(cli_addr);

        /* Accept actual connection from the client */
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        cout << "connection has started" << endl;
        /* If connection is established then start communicating */
        while (true) {

            this_thread::sleep_for(0.1s);
            bzero(buffer, 256);
            n = read(newsockfd, buffer, 255);
            std::string segment;
            std::vector<std::string> seglist;

            for (char c:buffer) {
                if ((c != ',') && (c != '\n')) {

                    segment += c;
                } else {
                    seglist.push_back(segment);
                    segment = "";
                }
            }
            if (seglist.size() >= 22) {
//
//                this->serverMap->insert(pair<string, double>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/altimeter/indicated-altitude-ft", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/altimeter/pressure-alt-ft", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/internal-roll-deg", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/encoder/indicated-altitude-ft", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/encoder/pressure-alt-ft", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/gps/indicated-altitude-ft", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/gps/indicated-ground-speed-kt", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/gps/indicated-vertical-speed", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/heading-indicator/indicated-heading-deg", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/turn-indicator/indicated-turn-rate", 0));
//                this->serverMap->insert(pair<string, double>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
//                this->serverMap->insert(pair<string, double>("/controls/flight/aileron", 0));
//                this->serverMap->insert(pair<string, double>("/controls/flight/elevator", 0));
//                this->serverMap->insert(pair<string, double>("/controls/flight/rudder", 0));
//                this->serverMap->insert(pair<string, double>("/controls/flight/flaps", 0));
//                this->serverMap->insert(pair<string, double>("/controls/engines/engine/throttle", 0));
//

            } else {
                cout << "the simulator doesn't give 22 args" << endl;
            }
//            if (n < 0) {
//                perror("ERROR reading from socket");
//                exit(1);
//            }

            /* Write a response to the client */
//            n = write(newsockfd, "I got your message", 18);
//
//            if (n < 0) {
//                perror("ERROR writing to socket");
//                exit(1);
//            }
        }
    }
};


#endif //PROJECT_SERVERSOCK_H
