
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
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        thread *client = new thread(Client::connectClient, port, ip, sockfd);
        this->threadsList.push_back(client);
        //Client *cl = new Client(ip, port);
        // thread t(cl->connectClient(ref(port),ref(ip)));

        //thread *treadClient = new thread(new Client(),ip,port);


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

    //this->symbolTable[par] = path;
    this->symbolTable.insert(pair<string, string>(par, path));
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
    }
    int index = getIndexOfOper(this->parameters);
    if (index == -1) {
        throw "not condition operator!";
    }
    string exp1 = this->vectorToString(0, index);
    ShuntingYard sy1(exp1, this);
    double val1 = sy1.calculate();
    string exp2 = this->vectorToString(index + 1, this->parameters.size() - 1);
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
            newS.push_back(tmp.substr(0, i));
            newS.push_back(tmp[i] + "");
            newS.push_back(tmp.substr(i + 1));
            continue;
        }

    }
    return newS;
}

ConditionParser::ConditionParser() : Command() {
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
    this->isDad = false;
    this->dad = nullptr;
}

ConditionParser *Command::getDad() {
    return this->dad;
}

bool PrintCommand::validate(vector<string> s) {
    return true;
}

int PrintCommand::execute() {
    for (auto tmp:this->parameters) {
        if (tmp[0] == '"') {
            cout << tmp << endl;
        } else {
            cout << this->getFromSymbolTable(tmp) << endl;
        };
    }

}

int SleepCommand::execute() {
    ShuntingYard sy(this->parameters[0], this);
    double val = sy.calculate();
    sleep(val);
    return val;
}

bool SleepCommand::validate(vector<string> s) {
    return true;
}
