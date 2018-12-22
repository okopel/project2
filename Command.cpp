
#include "Command.h"


int OpenServerCommand::execute(vector<string> s) {
    try {
        this->initMap();
        int port = stoi(s[0]);
        int hz = stoi(s[1]);
        ServerSock *serverSock = new ServerSock(port, hz);
        std::thread(serverSock->openServer());


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

int ConnectCommand::execute(vector<string> s) {
    try {

        string ip = s[0];
        int port = stoi(s[1]);

        this->c = new Client(ip, port);
        std::thread clientThread(this->c->connectClient());

        // this->c->connectClient();

    } catch (...) {
        throw "Error in connectToClient";
    }
}

bool ConnectCommand::validate(vector<string> s) {
    return false;
}

int DefineVarCommand::execute(vector<string> s) {
    if (!this->validate(s)) {
        throw "Error on VarCommand";
    }
    string par = s[0];
    // ignore "=" "bind"

    string path = s[3];

    this->symbolTable[par] = path;
//    this->addVar(par, val);

}

/*
void DefineVarCommand::addVar(string s, double val) {
    this->symbolTable.insert(pair<string, double>(s, val));
}

void DefineVarCommand::setVar(string s, double val) {
    this->symbolTable[s] = val;
}
*/
bool DefineVarCommand::validate(vector<string> s) {
    if (s.size() != 2) {
        return false;
    }
    //todo validate that the args is numbers
    return true;
}

int FuncCommand::execute(vector<string> s) {
    0;
}

int ConditionParser::execute(vector<string> s) {
    0;
}

void ConditionParser::addCommand(Command *c) {
    this->conditionCommandList.push_back(c);
}

int LoopCommand::execute(vector<string> s) {
//   while(conditon){
//       for(auto tmp:this->conditionCommandList){
//           tmp->execute()
//       }
//   }
}

int IfCommand::execute(vector<string> s) {
    0;
}

int assingmentCommand::execute(vector<string> s) {
    string varName = s[0];
    Expression *e = new ShuntingYard(s[2], this);
    double val = e->calculate();
    delete e;
    string path = this->symbolTable[varName];
    this->c->sendToClient(path, val);

}

double Command::getFromSymbolTable(string s) {
    if (this->symbolTable.count(s) == 0) {
        throw "Not in Map";
    }
    string path = this->symbolTable[s];
    double val = this->serverMap->at(path);
    return val;
}
