
#include "Command.h"
#include "ServerSock.h"
#include "ShuntingYard.h"
#include "ReadData.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <functional>

using namespace std;

int ConnectCommand::execute() {
    try {

        string ip = this->parameters[0];
        int port = stoi(this->parameters[1]);
        this->c = new Client(ip, port);
        Client *cl = new Client(ip, port);
        // thread t(cl->connectClient(ref(port),ref(ip)));
//        thread *treadClient = new thread(this->c->connectClient(),port,ip);


        // this->c->connectClient();

    } catch (...) {
        throw "Error in connectToClient";
    }
    return 0;
}

bool ConnectCommand::validate(vector<string> s) {
    return false;
}


int DefineVarCommand::execute() {
    if (!this->validate(this->parameters)) {
        throw "Error on VarCommand";
    }
    string par = this->parameters[0];
    // ignore "=" "bind"

    string path = this->parameters[3];

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


int ConditionParser::execute() {
    if (!this->checkCondition(this->parameters)) {
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

bool ConditionParser::checkCondition(vector<string> s) {//todo rePharse
    //delete the "{"
    if (s[s.size() - 1] == "{") {
        s.erase(s.end());
    }
    int index = this->checkCondition(s);
    if (index == -1) {
        throw "not condition operator!";
    }
    string exp1 = this->vectorToString(s, 0, index);
    ShuntingYard sy1(exp1, this);
    double val1 = sy1.calculate();
    string exp2 = this->vectorToString(s, index + 1, s.size() - 1);
    ShuntingYard sy2(exp2, this);
    double val2 = sy2.calculate();
    if (s[index] == "==") {
        return val1 == val2;
    }
    if (s[index] == ">=") {
        return val1 >= val2;
    }
    if (s[index] == "<=") {
        return val1 <= val2;
    }
    if (s[index] == "!=") {
        return val1 != val2;
    }
    if (s[index] == ">") {
        return val1 > val2;
    }
    if (s[index] == "<") {
        return val1 < val2;
    } else {
        throw "There isnt eq operator";
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

string ConditionParser::vectorToString(vector<string> s, int begin, int end) {
    string sub;
    for (int i = begin; i < end; i++) {
        sub += s[i];
    }
    return sub;
}


int LoopCommand::execute() {
//   while(conditon){
//       for(auto tmp:this->conditionCommandList){
//           tmp->execute()
//       }
//   }
}

int IfCommand::execute() {
    0;
}

int assingmentCommand::execute() {
    string varName = this->parameters[0];
    Expression *e = new ShuntingYard(this->parameters[2], this);
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

Command::Command(const vector<string> &parameters) : parameters(parameters) {}

void Command::setParam(vector<string> parameters) {
    this->parameters = parameters;
}

Command::Command() {

}
