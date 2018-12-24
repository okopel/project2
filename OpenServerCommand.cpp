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
#include "ShuntingYard.h"

using namespace std;

void OpenServerCommand::execute() {
    try {
        int index = this->getIndexOfDelimiter();
        if (index == -1) {
            throw "just one arg!";
        }
        string ex1;
        string ex2;
        for (int i = 0; i < this->parameters.size(); i++) {
            if (i < index) {
                ex1 += this->parameters[i];
            } else {
                ex2 += this->parameters[i];
            }
        }
        ShuntingYard s1(ex1, this);//todo check if work
        ShuntingYard s2(ex2, this);
        int port = (int) s1.calculate();
        int hz = (int) s2.calculate();
        map<string, string> &refPathMap = *this->pathMap;
        map<string, double> &refValMap = *this->valMap;
        thread *openServ = new thread(ServerSock::openServer, (port), (hz), refPathMap, ref(refValMap));
        this->threadsList.push_back(openServ);

    } catch (...) {
        throw "Error in openServer";
    }
}

bool OpenServerCommand::validate(vector<string> s) {
    return false;
}


OpenServerCommand::OpenServerCommand(map<string, string> *mapPath, map<string, double> *server) : Command(mapPath,
                                                                                                          server) {
}
