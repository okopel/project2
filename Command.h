//
// Created by shlomo on 16/12/18.
//

#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include <list>

using namespace std;

class Command {
private:
    list<Command> commands;

public:
    virtual int execute(string s);
};

class OpenServerCommand : public Command{
public:
    int execute(string s) override;
};

class ConnectCommand : public Command{
public:
    int execute(string s) override;
};

class DefineVarCommand : public Command{
public:
    int execute(string s) override;
};

class FuncCommand : public Command{
public:
    int execute(string s) override;
};

class ConditionParser: public Command{
public:
    virtual int execute(string s) override;
};

class LoopCommand: public ConditionParser{
public:
    int execute(string s) override;
};

class IfCommand: public ConditionParser{
public:
    int execute(string s) override;
};

#endif //PROJECT_COMMAND_H
