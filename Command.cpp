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

/**
 * connect as client, using ip and port
 */
void ConnectCommand::execute() {
    try {
        string ip = this->parameters[0];
        string tmp = "";
        for (int i = 1; i < this->parameters.size(); i++) {
            tmp += this->parameters[i];
        }
        // calc port
        ShuntingYard s(tmp, this);
        int port = (int) s.calculate();
        this->threadsList.push_back(new thread(ConnectClient, port, ip));

    } catch (...) {
        throw "Error in connectToClient";
    }
}

bool ConnectCommand::validate(vector<string> s) {
    // todo
    return false;
}

ConnectCommand::ConnectCommand(map<string, string> *mapPath, map<string, double> *serverMap) : Command(mapPath,
                                                                                                       serverMap) {}

/**
 * define new var, bind it or initial its value
 */
void DefineVarCommand::execute() {
    // not valid
    if (!this->validate(this->parameters)) {
        throw "Error on VarCommand";
    }
    string var = this->parameters[0];
    string path;
    // update map
    this->valMap->insert(pair<string, double>(var, 0));
    // ignore "=" "bind"
    if (this->parameters[2] == "bind") {
        path = this->parameters[3];
        if (path[0] != '"') {
            path = this->pathMap->at(path);
        }
        // update path map
        this->pathMap->insert(pair<string, string>(var, path));
        // not bind
    } else {
        string tmp = "";
        for (int i = 2; i < this->parameters.size(); i++) {
            tmp += this->parameters[i];
        }
        // calc initial value
        ShuntingYard s(tmp, this);
        this->valMap->at(var) = s.calculate();
    }
//    if (var[0] == '(') {
//        var = var.substr(1, var.size() - 1);
//    }
}

bool DefineVarCommand::validate(vector<string> s) {
    // todo
    return true;
}

/**
 * CTOR, for each var:
 * @param mapPath map for path
 * @param server map for value
 */
DefineVarCommand::DefineVarCommand(map<string, string> *mapPath, map<string, double> *server) : Command(mapPath,
                                                                                                        server) {
    this->isDad = false;
    this->dad = nullptr;
}

/**
 * add command in block to block commands list
 * @param c command
 */
void ConditionParser::addCommand(Command *c) {
    if (c == nullptr) {
        return;
    }
    this->conditionCommandList.push_back(c);
}

/**
 * calc condition
 * @return result
 */
bool ConditionParser::checkCondition() {
    //delete the "{"
    if (this->parameters[this->parameters.size() - 1] == "{") {
        this->parameters.erase(this->parameters.end());
        if (this->parameters.size() <= 1)
            return true;
    }
    // find operator index
    int index = getIndexOfOper(this->parameters);
    if (index == -1) {
        throw "not condition operator!";
    }
    // parse first and second expressions
    string exp1 = this->vectorToString(0, index);
    ShuntingYard sy1(exp1, this);
    double val1 = sy1.calculate();
    string exp2 = this->vectorToString(index + 1, this->parameters.size());
    ShuntingYard sy2(exp2, this);
    double val2 = sy2.calculate();
    string type = this->parameters[index];
    // calc condition
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

/**
 * return operator index in condeition vector
 * @param s vec
 * @return index
 */
int ConditionParser::getIndexOfOper(vector<string> s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == "==" || s[i] == ">=" || s[i] == "<=" || s[i] == "!=" || s[i] == "<" || s[i] == ">") {
            return i;
        }
    }
    return -1;
}

/**
 * cast vector to string, cut vec by 2 indexes
 * @param begin index
 * @param end index
 * @return cutted string
 */
string ConditionParser::vectorToString(int begin, int end) {
    string sub;
    for (int i = begin; i < end; i++) {
        sub += this->parameters[i];
    }
    return sub;
}
//
//vector<string> ConditionParser::rePhrser(vector<string> s) {
//    vector<string> newS;
//    for (auto tmp:s) {
//        if (isNumber(tmp)) {
//            newS.push_back(tmp);
//            continue;
//        }
//        int i = -1;
//        if (i == -1) {
//            i = tmp.find("<=");//split by <=
//        }
//        if (i == -1) {
//            i = tmp.find(">=");//split by >=
//        }
//        if (i == -1) {
//            i = tmp.find("==");//split by ==
//        }
//        if (i == -1) {
//            i = tmp.find("!=");//split by !=
//        }
//        if (i != -1) {
//            newS.push_back(tmp.substr(0, i));
//            newS.push_back(tmp.substr(i, i + 1));
//            newS.push_back(tmp.substr(i + 2));
//            continue;
//        }
//        i = tmp.find("<");//split by <
//        if (i == -1) {
//            i = tmp.find(">");//split by !=
//        }
//        if (i == -1) {
//            i = tmp.find(",");//split by !=
//        }
//        if (i != -1) {
//            newS.push_back(tmp.substr(0, i + 1));
//            string buf = tmp.substr(i + 1);
//            if (!buf.empty()) {
//                newS.push_back(buf);
//            }
//            buf = tmp.substr(i + 2);
//            if (!buf.empty()) {
//                newS.push_back(buf);
//            }
//            continue;
//
//        }
//        newS.push_back(tmp);
//    }
//    this->parameters = newS;
//    return newS;
//}

ConditionParser::ConditionParser(map<string, string> *mapPath, map<string, double> *serverMap) : Command(mapPath,
                                                                                                         serverMap) {
    this->isDad = true;
    this->dad = nullptr;
}

bool Command::isNumber(string s) {
    for (char c:s) {
        if ((!isdigit(c)) && (c != '.')) {
            return false;
        }
    }
    return true;
}

void ConditionParser::setParam(vector<string> parameters) {
    this->parameters = parameters;
}

void Command::setDad(ConditionParser *c) {
    this->dad = c;
}

/**
 * execute all command in block
 * @return
 */
void LoopCommand::execute() {
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

void IfCommand::execute() {
    if (this->checkCondition()) {
        for (auto tmp:this->conditionCommandList) {
            tmp->execute();
        }
    }
}

bool IfCommand::validate(vector<string> s) {
    return true;
}

IfCommand::IfCommand(map<string, string> *mapPath, map<string, double> *server) : ConditionParser(mapPath, server) {
}

void AssingmentCommand::execute() {
    string varName = this->parameters[0];
    string tmp = "";
    for (int i = 2; i < this->parameters.size(); i++) {
        tmp += this->parameters[i];
    }
    ShuntingYard s(tmp, this);
    double val = s.calculate();
    this->valMap->at(varName) = val;
    sendToClient(varName, val);
}

double Command::getFromSymbolTable(string s) {
    if (this->valMap->count(s) == 0) {
        cout << "not in map" << endl;
        throw "Not in Map";
    }
    return this->valMap->at(s);
//    string path = this->symbolTable->at(s);
//    if (path[0] != '"') {//var case
//        path = this->serverMap->at(path);
//    }
//    double val = 0;
//    if (serverMap != nullptr) {
//        //delete the " from start and end
//        //path = path.substr(1, path.size() - 2);
//        cout << path << endl;
//        val = this->serverMap->at(path);
//    }
//
//    return val;
}


void Command::setParam(vector<string> parameters) {
    this->parameters = parameters;
}

Command::Command(map<string, string> *mapPath, map<string, double> *valMap1) {
    this->isDad = false;
    this->dad = nullptr;
    this->pathMap = mapPath;
    this->valMap = valMap1;

}

ConditionParser *Command::getDad() {
    return this->dad;
}

int Command::getIndexOfDelimiter() {
    for (int i = 0; i < this->parameters.size(); i++) {


        if (this->parameters[i] == ",") {

            return i;
        }
        if (i > 0) {
            string par1 = this->parameters[i];
            string par2 = this->parameters[i - 1];
            if (isNumber(par1) && isNumber(par2)) {
                return i;
            }
        }
    }
    return -1;
}

bool Command::isOperator(string s) {
    for (char c:s) {
        if (c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')') {
            return false;
        }
    }
    return true;
}

Command::~Command() {
//    for (auto v:this->threadsList) {//todo
//        delete v;
//    }
}

bool PrintCommand::validate(vector<string> s) {
    return true;
}

void PrintCommand::execute() {
    string buffer = "";

    for (auto tmp:this->parameters) {
        buffer += tmp;
    }
    if (buffer[0] == '"') {
        buffer = buffer.substr(1, buffer.size() - 2);
        cout << buffer << endl;
    } else {
        ShuntingYard sy(buffer, this);
        cout << sy.calculate() << endl;
    }

}

PrintCommand::PrintCommand(map<string, string> *mapPath, map<string, double> *server) : Command(mapPath, server) {}

void SleepCommand::execute() {
    string buffer = "";
    for (auto tmp:this->parameters) {
        buffer += tmp;
    }
    ShuntingYard sy(buffer, this);
    double val = sy.calculate();
    sleep(val);
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
}


