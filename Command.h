#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include <vector>
#include <map>
#include "Client.h"
#include "Expression.h"

using namespace std;

class Command {
protected:
    //Command *command;
    map<string, string> symbolTable;
    map<string, double> *serverMap;
    vector<string> parameters;
    Client *c;

    virtual bool validate(vector<string> s) = 0;

public:
    Command(const vector<string> &parameters);

    Command();

    void setParam(vector<string> parameters);

    double getFromSymbolTable(string s);

    virtual int execute() = 0;
};

class ConnectCommand : public Command {
protected:
    bool validate(vector<string> s) override;

public:

    int execute() override;
};

class DefineVarCommand : public Command {
protected:
    bool validate(vector<string> s) override;

//private:
public:
    void addVar(string s, double val);

    void setVar(string s, double val);

    int execute() override;
};

class ConditionParser : public Command {
private:

    vector<string> rePhrser(vector<string> s);

    int getIndexOfOper(vector<string> s);

    string vectorToString(vector<string> s, int begin, int end);

protected:
    vector<Command *> conditionCommandList;

public:

    void addCommand(Command *c);

    bool checkCondition(vector<string> s);

    virtual int execute() = 0;
};

class LoopCommand : public ConditionParser {
public:
    int execute() override;
};

class IfCommand : public ConditionParser {
public:
    int execute() override;
};

class assingmentCommand : public Command {
private:

public:
    int execute() override;
};

#endif //PROJECT_COMMAND_H
