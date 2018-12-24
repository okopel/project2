/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#include "Command.h"
#include "ServerSock.h"
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

ConnectCommand::ConnectCommand(DoubleMap *mapPath, map<string, double> *serverMap) : Command(mapPath,
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
        //get var name (no path)
        if (path[0] != '"') {
            //get the path of the other var
            path = this->pathMap->getPath(path);
//            path = this->pathMap->at(path);
        }
        // update path map
        //this->pathMap->insert(pair<string, string>(var, path));
        path = path.substr(1, path.size() - 2);
        this->pathMap->addArg(var, path); // todo if there are 2 arg
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
DefineVarCommand::DefineVarCommand(DoubleMap *mapPath, map<string, double> *server) : Command(mapPath,
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

ConditionParser::ConditionParser(DoubleMap *mapPath, map<string, double> *serverMap) : Command(mapPath,
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
    //todo
    return true;
}

LoopCommand::LoopCommand(DoubleMap *mapPath, map<string, double> *server) : ConditionParser(mapPath,
                                                                                            server) {}

/**
 * execute all commands in if block
 */
void IfCommand::execute() {
    if (this->checkCondition()) {
        for (auto tmp:this->conditionCommandList) {
            tmp->execute();
        }
    }
}

bool IfCommand::validate(vector<string> s) {
    // todo
    return true;
}

IfCommand::IfCommand(DoubleMap *mapPath, map<string, double> *server) : ConditionParser(mapPath, server) {
}

/**
 * set vat value
 */
void AssingmentCommand::execute() {
    string varName = this->parameters[0];
    string tmp = "";
    for (int i = 2; i < this->parameters.size(); i++) {
        tmp += this->parameters[i];
    }
    ShuntingYard s(tmp, this);
    // calc var value
    double val = s.calculate();
    this->valMap->at(varName) = val;
    // update simulator
    sendToClient(varName, val);
}

/**
 * return var value
 * @param s var name
 * @return value
 */
double Command::getFromSymbolTable(string s) {
    if (this->valMap->count(s) == 0) {
        throw "Not in Map";
    }
    return this->valMap->at(s);
}


void Command::setParam(vector<string> parameters) {
    this->parameters = parameters;
}

/**
 * CTOR
 * @param mapPath
 * @param valMap1
 */
Command::Command(DoubleMap *mapPath, map<string, double> *valMap1) {
    this->isDad = false;
    this->dad = nullptr;
    this->pathMap = mapPath;
    this->valMap = valMap1;

}

/**
 * @return condition command whice this command under it
 */
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
    // delimiter error case
    return -1;
}

/**
 * @param s string
 * @return true if is operator
 */
bool Command::isOperator(string s) {
    for (char c:s) {
        if (c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')') {
            return false;
        }
    }
    return true;
}

Command::~Command() {
    for (thread *t:this->threadsList) {
        delete t;
    }
}

bool PrintCommand::validate(vector<string> s) {
    return true;
}

/**
 * print in monitor
 */
void PrintCommand::execute() {
    string buffer = "";

    for (auto tmp:this->parameters) {
        buffer += tmp;
    }
    // if string - print it
    if (buffer[0] == '"') {
        buffer = buffer.substr(1, buffer.size() - 2);
        //print the string
        cout << buffer << endl;
        return;
    }
    // if num - calc & print
    //cout << "BUF:" << buffer << endl;
    ShuntingYard sy(buffer, this);
    //print the value of the var
    cout << sy.calculate() << endl;

}

PrintCommand::PrintCommand(DoubleMap *mapPath, map<string, double> *server) : Command(mapPath, server) {}

/**
 * sleep for x seconds
 */
void SleepCommand::execute() {
    string buffer = "";
    for (auto tmp:this->parameters) {
        buffer += tmp;
    }
    ShuntingYard sy(buffer, this);
    // calc num of seconds
    double val = sy.calculate();
    usleep(val);
}

bool SleepCommand::validate(vector<string> s) {
    // todo
    return true;
}

SleepCommand::SleepCommand(DoubleMap *mapPath, map<string, double> *server) : Command(mapPath, server) {}

bool AssingmentCommand::validate(vector<string> s) {
    // todo
    return false;
}

AssingmentCommand::AssingmentCommand(DoubleMap *mapPath, map<string, double> *server) : Command(mapPath,
                                                                                                server) {
}

bool EnterCCommand::validate(vector<string> s) {
    return true;
}

void EnterCCommand::execute() {
    getchar();
}

EnterCCommand::EnterCCommand(DoubleMap *mapPath, map<string, double> *serverMap) : Command(mapPath, serverMap) {}
