/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#include "ServerSock.h"
#include "ShuntingYard.h"

using namespace std;

/**
 * Open server
 * using to get simulator values
 */
void OpenServerCommand::execute() {
    try {
        int index = this->getIndexOfDelimiter();
        if (index == -1) {
            throw "just one arg!";
        }
        // calc port & Hz
        string ex1;
        string ex2;
        for (int i = 0; i < this->parameters.size(); i++) {
            if (i < index) {
                ex1 += this->parameters[i];
            } else {
                ex2 += this->parameters[i];
            }
        }
        ShuntingYard s1(ex1, this);
        ShuntingYard s2(ex2, this);
        int port = (int) s1.calculate();
        int hz = (int) s2.calculate();
        // hold 2 maps, get path and return value
        DoubleMap &refPathMap = *this->pathMap;
//        map<string, double> &refValMap = *this->valMap;
        // open server in new thread
        thread *openServ = new thread(ServerSock::openServer, (port), (hz), ref(refPathMap), ref(this->valMap));
        this->threadsList.push_back(openServ);

    } catch (...) {
        throw "Error in openServer";
    }
}

bool OpenServerCommand::validate(vector<string> s) {
    // todo, now no one using this func
    return true;
}


OpenServerCommand::OpenServerCommand(DoubleMap *mapPath, map<string, double> *server) : Command(mapPath,
                                                                                                server) {}

