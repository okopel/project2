#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "Command.h"
#include <map>

typedef void *(*THREADFUNCPTR)(void *);


class ServerSock : public OpenServerCommand {
public:
    void setValues(std::string buffer) {

    }

    int static openServer(int portno, int hz, map<string, double> &map) {
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
//        portno = 5001;

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);

        /* Now bind the host address using bind() call.*/
        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR on binding");
            exit(1);
        }

        /* Now start listening for the clients, here process will
           * go in sleep mode and will wait for the incoming connection
        */

        listen(sockfd, hz);
        clilen = sizeof(cli_addr);

        /* Accept actual connection from the client */
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }

        /* If connection is established then start communicating */
        while (n > 0) {
            bzero(buffer, 256);
            n = read(newsockfd, buffer, 255);

            std::string segment;
            std::vector<std::string> seglist;

            for (char c:buffer) {
                if (c != ',') {
                    segment += c;
                } else {
                    seglist.push_back(segment);
                    segment = "";
                }
            }


            map["/instrumentation/airspeed-indicator/indicated-speed-kt"] = stod(seglist[0]);
            map["/instrumentation/altimeter/indicated-altitude-ft"] = stod(seglist[1]);
            map["/instrumentation/altimeter/pressure-alt-ft"] = stod(seglist[2]);
            map["/instrumentation/attitude-indicator/indicated-pitch-deg"] = stod(seglist[3]);
            map["/instrumentation/attitude-indicator/indicated-roll-deg"] = stod(seglist[4]);
            map["/instrumentation/attitude-indicator/internal-pitch-deg"] = stod(seglist[5]);
            map["/instrumentation/attitude-indicator/internal-roll-deg"] = stod(seglist[6]);
            map["/instrumentation/encoder/indicated-altitude-ft"] = stod(seglist[7]);
            map["/instrumentation/encoder/pressure-alt-ft"] = stod(seglist[8]);
            map["/instrumentation/gps/indicated-altitude-ft"] = stod(seglist[9]);
            map["/instrumentation/gps/indicated-ground-speed-kt"] = stod(seglist[10]);
            map["/instrumentation/gps/indicated-vertical-speed"] = stod(seglist[11]);
            map["/instrumentation/heading-indicator/indicated-heading-deg"] = stod(seglist[12]);
            map["/instrumentation/magnetic-compass/indicated-heading-deg"] = stod(seglist[13]);
            map["/instrumentation/slip-skid-ball/indicated-slip-skid"] = stod(seglist[14]);
            map["/instrumentation/turn-indicator/indicated-turn-rate"] = stod(seglist[15]);
            map["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = stod(seglist[16]);
            map["/controls/flight/aileron"] = stod(seglist[17]);
            map["/controls/flight/elevator"] = stod(seglist[18]);
            map["/controls/flight/rudder"] = stod(seglist[19]);
            map["/controls/flight/flaps"] = stod(seglist[20]);
            map["/controls/engines/engine/throttle"] = stod(seglist[21]);
            map["/engines/engine/rpm"] = stod(seglist[22]);

//                        printf("Here is the message: %s\n", buffer);

        }
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        printf("Here is the message: %s\n", buffer);

        /* Write a response to the client */
        n = write(newsockfd, "I got your message", 18);

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        return 0;
    }
};