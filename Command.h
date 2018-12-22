#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include <vector>
#include <map>
#include "Client.h"
#include "ServerSock.h"
#include <thread>
#include "Expression.h"
#include "ComExp.h"
#include "ShuntingYard.h"
#include "Client.h"

using namespace std;

class Command {
protected:
    //Command *command;
    map<string, string> symbolTable;
    map<string, double> *serverMap;
    Client *c;

    virtual bool validate(vector<string> s) = 0;

public:
    double getFromSymbolTable(string s);

    virtual int execute(vector<string> s) = 0;
};

class OpenServerCommand : public Command {
protected:
    bool validate(vector<string> s) override;

    void initMap();

public:
    int execute(vector<string> s) override;
};

class ConnectCommand : public Command {
protected:
    bool validate(vector<string> s) override;

public:
    int execute(vector<string> s) override;
};

class DefineVarCommand : public Command {
protected:
    bool validate(vector<string> s) override;

//private:
public:
    void addVar(string s, double val);

    void setVar(string s, double val);

    int execute(vector<string> s) override;
};

class FuncCommand : public Command {
public:
    int execute(vector<string> s) override;
};

class ConditionParser : public Command {
protected:
    vector<Command *> conditionCommandList;
public:
    void addCommand(Command *c);

    virtual int execute(vector<string> s) = 0;
};

class LoopCommand : public ConditionParser {
public:
    int execute(vector<string> s) override;
};

class IfCommand : public ConditionParser {
public:
    int execute(vector<string> s) override;
};

class assingmentCommand : public Command {
private:

public:
    int execute(vector<string> s) override;
};

#endif //PROJECT_COMMAND_H
