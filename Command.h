#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include <vector>
#include <map>
#include <thread>
#include "Client.h"
#include "Expression.h"

using namespace std;

class ConditionParser;

class Command {
protected:
    //Command *command;
    map<string, string> symbolTable;
    map<string, double> *serverMap;
    vector<string> parameters;
    Client *c;
    vector<thread *> threadsList;
    ConditionParser *dad;

    virtual bool validate(vector<string> s) = 0;

public:
    bool isDad;

    Command(const vector<string> &parameters);

    Command();

    virtual void setParam(vector<string> parameters);

    double getFromSymbolTable(string s);

    ConditionParser *getDad();

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
    bool isNumber(string s);

    vector<string> rePhrser(vector<string> s);

    int getIndexOfOper(vector<string> s);

    string vectorToString(int begin, int end);

protected:
    vector<Command *> conditionCommandList;

public:
    ConditionParser();

    void setParam(vector<string> parameters) override;

    void addCommand(Command *c);

    bool checkCondition();

    virtual int execute() = 0;
};

class LoopCommand : public ConditionParser {
public:
    int execute() override;

protected:
    bool validate(vector<string> s) override;
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

class PrintCommand : public Command {
protected:
    bool validate(vector<string> s) override;

public:
    int execute() override;
};

class SleepCommand : public Command {
public:
    int execute() override;

protected:
    bool validate(vector<string> s) override;
};

#endif //PROJECT_COMMAND_H
