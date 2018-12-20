
#include "Command.h"
#include "Client.cpp"
#include "ServerSock.cpp"
#include "Expression.h"
#include "ComExp.h"
#include "ShuntingYard.h"
#include <thread>
//using namespace std;

int OpenServerCommand::execute(vector<string> s) {
    try {

        int port = stoi(s[0]);
        int hz = stoi(s[1]);
        this->serverMap=new map<string,double >;
        map<string,double >& sermap=*this->serverMap;
        std::thread t(ServerSock::openServer,port,hz,sermap);
        t.join();
//        ServerSock::openServer(port, hz);
    } catch (...) {
        throw "Error in openServer";
    }

}

bool OpenServerCommand::validate(vector<string> s) {
    return false;//todo
}

int ConnectCommand::execute(vector<string> s) {
    try {

        string ip = s[0];
        int port = stoi(s[1]);

        Client::connectClient(ip, port);
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
    string add = s[3];

    double val;//todo get num from server


    this->addVar(par, val);

}

void DefineVarCommand::addVar(string s, double val) {
    this->symbolTable.insert(pair<string, double>(s, val));
}

void DefineVarCommand::setVar(string s, double val) {
    this->symbolTable[s] = val;
}

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
    Expression *e = new ShuntingYard(s[2],this);
    double val = e->calculate();

//    if (this->symbolTable.count(s[2]) > 0) {
//        val = this->symbolTable[s[2]];
//    }else{
//        val=stoi
//    }

}

double Command::getFromSymbolTable(string s) {
    if (this->symbolTable.count(s) == 0) {
        throw "Not in Map";
    }
    return this->symbolTable[s];
}
