/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#ifndef PROJECT_SERVERSOCK_H
#define PROJECT_SERVERSOCK_H

#include <mutex>
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
#include "Global.h"
#include "ServerSock.h"

class ServerSock : public OpenServerCommand {
public:
    void static
    openServer(int portNumber, int myHz, DoubleMap &pathMapServer, map<string, double> *valMapServer) {
        cout << "try to connect.." << endl;
        int sockfd, newsockfd, clilen, n;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
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
        //pathes from the XML
        vector<string> pathes = {"/instrumentation/airspeed-indicator/indicated-speed-kt",
                                 "/instrumentation/altimeter/indicated-altitude-ft",
                                 "/instrumentation/altimeter/pressure-alt-ft",
                                 "/instrumentation/attitude-indicator/indicated-pitch-deg",
                                 "/instrumentation/attitude-indicator/indicated-roll-deg",
                                 "/instrumentation/attitude-indicator/internal-pitch-deg",
                                 "/instrumentation/attitude-indicator/internal-roll-deg",
                                 "/instrumentation/encoder/indicated-altitude-ft",
                                 "/instrumentation/encoder/pressure-alt-ft",
                                 "/instrumentation/gps/indicated-altitude-ft",
                                 "/instrumentation/gps/indicated-ground-speed-kt",
                                 "/instrumentation/gps/indicated-vertical-speed",
                                 "/instrumentation/heading-indicator/indicated-heading-deg",
                                 "/instrumentation/magnetic-compass/indicated-heading-deg",
                                 "/instrumentation/slip-skid-ball/indicated-slip-skid",
                                 "/instrumentation/turn-indicator/indicated-turn-rate",
                                 "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
                                 "/controls/flight/aileron",
                                 "/controls/flight/elevator",
                                 "/controls/flight/rudder",
                                 "/controls/flight/flaps",
                                 "/controls/engines/current-engine/throttle"
        };
        string nextBuf;
        bool flash = false;
        /* If connection is established then start communicating */
        while (true) {
            this_thread::sleep_for(0.1s);
            bzero(buffer, 256);
            n = read(newsockfd, buffer, 255);
            //n = recv(newsockfd, buffer, 255, MSG_PEEK);
            string conectedBuffer = nextBuf + buffer;
            nextBuf = "";
            std::string segment;
            std::vector<std::string> seglist;
            flash = false;
            for (auto c:conectedBuffer) {
                if (c == '\n') {
                    flash = true;
                    continue;
                }
                if (flash) {
                    nextBuf += c;
                    continue;
                }
                if (c != ',') {
                    segment += c;
                } else {
                    seglist.push_back(segment);
                    segment = "";
                }
            }
            if (!segment.empty()) {
                seglist.push_back(segment);
            }
            for (int i = 0; i < min(pathes.size(), seglist.size()); i++) {
                string var = pathMapServer.getVar(pathes[i]);
                if (var == "") {
                    continue;
                }
                cout << var << ":" << stod(seglist[i]) << endl;
                if (var == "alt") {
                    cout << "alt:" << stod(seglist[i]);

                }
                locker.lock();
                valMapServer->at(var) = stod(seglist[i]); //todo arrange the SHEERIOT
                locker.unlock();
            }
        }
    }
};

#endif //PROJECT_SERVERSOCK_H
