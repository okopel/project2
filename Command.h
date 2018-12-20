#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Command {
protected:
    //Command *command;
    map<string, double> symbolTable;

    virtual bool validate(vector<string> s) = 0;

public:
    double getFromSymbolTable(string s);

    virtual int execute(vector<string> s) = 0;
};

class OpenServerCommand : public Command {
protected:
    map<string, double>* serverMap;

    bool validate(vector<string> s) override;

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
