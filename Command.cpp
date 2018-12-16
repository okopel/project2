
#include "Command.h"
#include "Client.cpp"

/*int IfCommand::execute(string s) {
    if condition == true
    for each Command c in commands
    c.execute()
}*/


int OpenServerCommand::execute(vector<string> s) {
    if (s.size() != 2) {
        throw "Error in openServerCommand";
    }

}

bool OpenServerCommand::validate(vector<string> s) {
    return false;//todo
}

int ConnectCommand::execute(vector<string> s) {
    0;
}

int DefineVarCommand::execute(vector<string> s) {
    if (!this->validate(s)) {
        return 0;
    }
    string par = s[0];
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

int LoopCommand::execute(vector<string> s) {
    0;
}

int IfCommand::execute(vector<string> s) {
    0;
}
