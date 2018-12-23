/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#include "Command.h"
#include "ServerSock.h"
#include "ShuntingYard.h"
#include "ReadData.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <functional>
#include "Client.h"

using namespace std;


int ConnectCommand::execute() {
    try {
        string ip = this->parameters[0];
        int port = stoi(this->parameters[1]);
        this->threadsList.push_back(new thread(ConnectClient, port, ip));

    } catch (...) {
        throw "Error in connectToClient";
    }
    return 0;
}

bool ConnectCommand::validate(vector<string> s) {
    return false;
}

ConnectCommand::ConnectCommand(map<string, string> *mapPath, map<string, double> *serverMap) : Command(mapPath,
                                                                                                       serverMap) {}


int DefineVarCommand::execute() {
    if (!this->validate(this->parameters)) {
        throw "Error on VarCommand";
    }
    string par = this->parameters[0];
    string path;
    // ignore "=" "bind"
    if (this->parameters[2] == "bind") {
        path = this->parameters[3];
    } else {
        path = this->parameters[2];
    }

    //this->symbolTable[par] = path;
    if (par[0] == '(') {
        par = par.substr(1, par.size() - 1);
    }
    this->symbolTable->insert(pair<string, string>(par, path));
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

    //todo validate that the args is numbers
    return true;
}

DefineVarCommand::DefineVarCommand(map<string, string> *mapPath, map<string, double> *server) : Command(mapPath,
                                                                                                        server) {
    this->isDad = false;
    this->dad = nullptr;
}


int ConditionParser::execute() {
    if (!this->checkCondition()) {
        return 0;
    }
    // ReadData readData;
    // readData.lexer();

    for (auto tmp:this->conditionCommandList) {
        tmp->execute();
    }


}

void ConditionParser::addCommand(Command *c) {
    this->conditionCommandList.push_back(c);
}

bool ConditionParser::checkCondition() {//todo rePharse
    //delete the "{"
    if (this->parameters[this->parameters.size() - 1] == "{") {
        this->parameters.erase(this->parameters.end());
        if (this->parameters.size() <= 1)
            return true;
    }

    int index = getIndexOfOper(this->parameters);
    if (index == -1) {
        throw "not condition operator!";
    }
    string exp1 = this->vectorToString(0, index);
    ShuntingYard sy1(exp1, this);
    double val1 = sy1.calculate();
    string exp2 = this->vectorToString(index + 1, this->parameters.size());
    ShuntingYard sy2(exp2, this);
    double val2 = sy2.calculate();
    string type = this->parameters[index];
    if (type == "==") {
        return val1 == val2;
    }
    if (type == ">=") {
        return val1 >= val2;
    }
    if (type == "<=") {
        return val1 <= val2;
    }
    if (type == "!=") {
        return val1 != val2;
    }
    if (type == ">") {
        return val1 > val2;
    }
    if (type == "<") {
        return val1 < val2;
    } else {
        throw "There isn't eq operator";
    }

}

// todo if is one word
int ConditionParser::getIndexOfOper(vector<string> s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == "==" || s[i] == ">=" || s[i] == "<=" || s[i] == "!=" || s[i] == "<" || s[i] == ">") {
            return i;
        }
    }
    return -1;
}

string ConditionParser::vectorToString(int begin, int end) {
    string sub;
    for (int i = begin; i < end; i++) {
        sub += this->parameters[i];
    }
    return sub;
}

vector<string> ConditionParser::rePhrser(vector<string> s) {
    vector<string> newS;
    for (auto tmp:s) {
        if (isNumber(tmp)) {
            newS.push_back(tmp);
            continue;
        }
        int i = -1;
        if (i == -1) {
            i = tmp.find("<=");//split by <=
        }
        if (i == -1) {
            i = tmp.find(">=");//split by >=
        }
        if (i == -1) {
            i = tmp.find("==");//split by ==
        }
        if (i == -1) {
            i = tmp.find("!=");//split by !=
        }
        if (i != -1) {
            newS.push_back(tmp.substr(0, i));
            newS.push_back(tmp.substr(i, i + 1));
            newS.push_back(tmp.substr(i + 2));
            continue;
        }
        i = tmp.find("<");//split by <
        if (i == -1) {
            i = tmp.find(">");//split by !=
        }
        if (i == -1) {
            i = tmp.find(",");//split by !=
        }
        if (i != -1) {
            newS.push_back(tmp.substr(0, i + 1));
            string buf = tmp.substr(i + 1);
            if (!buf.empty()) {
                newS.push_back(buf);
            }
//            buf = tmp.substr(i + 2);
//            if (!buf.empty()) {
//                newS.push_back(buf);
//            }
            continue;

        }
        newS.push_back(tmp);
    }
    this->parameters = newS;
    return newS;
}

ConditionParser::ConditionParser(map<string, string> *mapPath, map<string, double> *serverMap) : Command(mapPath,
                                                                                                         serverMap) {
    this->isDad = true;
    this->dad = nullptr;


}

bool ConditionParser::isNumber(string s) {
    for (char c:s) {
        if ((!isdigit(c)) && (c != '.')) {
            return false;
        }
    }
    return true;

}

void ConditionParser::setParam(vector<string> parameters) {
//    this->parameters = this->rePhrser(parameters);
    this->parameters = parameters;
}

void Command::setDad(ConditionParser *c) {
    this->dad = c;
}


int LoopCommand::execute() {
    while (this->checkCondition()) {
        for (auto tmp:this->conditionCommandList) {
            tmp->execute();
        }
    }
}

bool LoopCommand::validate(vector<string> s) {
    return true;
}

LoopCommand::LoopCommand(map<string, string> *mapPath, map<string, double> *server) : ConditionParser(mapPath,
                                                                                                      server) {}

int IfCommand::execute() {
    0;
}

bool IfCommand::validate(vector<string> s) {
    return true;
}

IfCommand::IfCommand(map<string, string> *mapPath, map<string, double> *server) : ConditionParser(mapPath, server) {
}

int AssingmentCommand::execute() {
    string varName = this->parameters[0];
    Expression *e = new ShuntingYard(this->parameters[2], this);
    double val = e->calculate();
    delete e;
    string path = this->symbolTable->at(varName);
    sendToClient(path, val);
    return val;
}

double Command::getFromSymbolTable(string s) {
    if (this->symbolTable->count(s) == 0) {
        cout << "not in map" << endl;
        throw "Not in Map";
    }
    string path = this->symbolTable->at(s);
    if (path[0] != '"') {//var case
        path = this->symbolTable->at(path);
    }
    double val = 0;
    if (serverMap != nullptr) {
        //delete the " from start and end
        path = path.substr(1, path.size() - 2);
        val = this->serverMap->at(path);
    }

    return val;
}


void Command::setParam(vector<string> parameters) {
    this->parameters = parameters;
}

Command::Command(map<string, string> *mapPath, map<string, double> *serverMap) {
    this->isDad = false;
    this->dad = nullptr;
    this->symbolTable = mapPath;
    this->serverMap = serverMap;
}

ConditionParser *Command::getDad() {
    return this->dad;
}

bool PrintCommand::validate(vector<string> s) {
    return true;
}

int PrintCommand::execute() {
    string buffer;

    for (auto tmp:this->parameters) {
        buffer += tmp;
    }
    if (buffer[0] == '"') {
        cout << buffer << endl;
    } else {
        ShuntingYard sy(buffer, this);
        cout << sy.calculate() << endl;
    }

}

PrintCommand::PrintCommand(map<string, string> *mapPath, map<string, double> *server) : Command(mapPath, server) {}

int SleepCommand::execute() {
    ShuntingYard sy(this->parameters[0], this);
    double val = sy.calculate();
    sleep(val);
    return val;
}

bool SleepCommand::validate(vector<string> s) {
    return true;
}

SleepCommand::SleepCommand(map<string, string> *mapPath, map<string, double> *server) : Command(mapPath, server) {}

bool AssingmentCommand::validate(vector<string> s) {
    return false;
}

AssingmentCommand::AssingmentCommand(map<string, string> *mapPath, map<string, double> *server) : Command(mapPath,
                                                                                                          server) {
    this->serverMap = server;
}


