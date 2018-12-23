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
        this->initMap();
        int port = stoi(this->parameters[0]);
        int hz = stoi(this->parameters[1]);
        ServerSock *serverSock = new ServerSock();
//        thread t(serverSock->openServer());
        map<string, double> &sermap = *this->serverMap;
        thread *openServ = new thread(ServerSock::openServer, (port), (hz), ref(sermap));
        this->threadsList.push_back(openServ);

        //openServ->join();

//        t.join();
    } catch (...) {
        throw "Error in openServer";
    }
    return 1;
}

bool OpenServerCommand::validate(vector<string> s) {
    return false;//todo
}

void OpenServerCommand::initMap() {
    this->serverMap = new map<string, double>();
    this->serverMap->insert(pair<string, double>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/altimeter/indicated-altitude-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/altimeter/pressure-alt-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/internal-roll-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/encoder/indicated-altitude-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/encoder/pressure-alt-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/gps/indicated-altitude-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/gps/indicated-ground-speed-kt", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/gps/indicated-vertical-speed", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/heading-indicator/indicated-heading-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/turn-indicator/indicated-turn-rate", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
    this->serverMap->insert(pair<string, double>("/controls/flight/aileron", 0));
    this->serverMap->insert(pair<string, double>("/controls/flight/elevator", 0));
    this->serverMap->insert(pair<string, double>("/controls/flight/rudder", 0));
    this->serverMap->insert(pair<string, double>("/controls/flight/flaps", 0));
    this->serverMap->insert(pair<string, double>("/controls/engines/engine/throttle", 0));

}
