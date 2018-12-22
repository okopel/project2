

#ifndef PROJECT_SERVERSOCK_H
#define PROJECT_SERVERSOCK_H

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
#include <chrono>


typedef void *(*THREADFUNCPTR)(void *);


class ServerSock : public OpenServerCommand {
    int portno;
    int hz;
public:
    void setValues(std::string buffer);

    ServerSock(int portno, int hz);

    int openServer();
};


#endif //PROJECT_SERVERSOCK_H
