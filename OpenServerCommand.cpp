/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#include "OpenServerCommand.h"
#include <bits/locale_facets.tcc>
#include "ServerSock.h"
#include <string>
#include <string.h>
#include <thread>

using namespace std;

int OpenServerCommand::execute() {
    try {
        int port = stoi(this->parameters[0]);
        int hz = stoi(this->parameters[1]);
        map<string, double> &sermap = *this->serverMap;
        thread *openServ = new thread(ServerSock::openServer, (port), (hz), ref(sermap));
        this->threadsList.push_back(openServ);

    } catch (...) {
        throw "Error in openServer";
    }
    return 1;
}

bool OpenServerCommand::validate(vector<string> s) {
    return false;//todo
}


OpenServerCommand::OpenServerCommand(map<string, string> *mapPath, map<string, double> *server) : Command(mapPath,
                                                                                                          server) {
}
