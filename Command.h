/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/
#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include <vector>
#include <map>
#include <thread>
#include "Expression.h"
#include "DoubleMap.h"
#include "Global.h"

using namespace std;


class ConditionParser;

/**
 * command interface
 * command is a mission to execute
 */
class Command {

protected:
    DoubleMap *pathMap;
    map<string, double> *valMap;
    vector<string> parameters;
//    vector<thread *> threadsList;
    thread *comThread;
    ConditionParser *dad;


protected:
    /**
     * valid func
     * @param s number
     * @return if is number
     */
    bool isNumber(string s);

    /**
     * valid func
     * @param s operator
     * @return if is operator
     */
    bool isOperator(string s);

    /**
     * find index of ','
     * @return index
     */
    int getIndexOfDelimiter();

public:
    virtual ~Command();

    void join();

    /**
     * check if this command is in block
     */
    bool isDad;

    void setDad(ConditionParser *c);

    /**
     * CTOR
     * @param mapPath map: var to its path
     * @param serverMap map: var to its value
     */
    Command(DoubleMap *mapPath, map<string, double> *serverMap);

    /**
     * set command parameters
     * @param parameters
     */
    virtual void setParam(vector<string> parameters);

    /**
     * using map
     * @param s var
     * @return its value
     */
    double getFromSymbolTable(string s);

    /**
     * @return  if this command is in block
     */
    ConditionParser *getDad();

    /**
     * execute the command
     */
    virtual void execute() = 0;
};

/**
 * command: connect as client to simulator
 */
class ConnectCommand : public Command {
    string ip;
    int port;
public:
    ConnectCommand(DoubleMap *mapPath, map<string, double> *serverMap);

    void execute() override;
};

/**
 * Waiter untill the simulator will work
 */
class EnterCCommand : public Command {
public:
    void execute() override;

    EnterCCommand(DoubleMap *mapPath, map<string, double> *serverMap);
};

/**
 * command: define new var
 * bind new var to simulator values by givven path
 * or init var value
 */
class DefineVarCommand : public Command {
public:
    DefineVarCommand(DoubleMap *mapPath, map<string, double> *server);

    void execute() override;
};

/**
 * command: check condition before block (if / while)
 */
class ConditionParser : public Command {
private:

    /**
     * find boolean operator index in condition
     * @param s vector
     * @return index
     */
    int getIndexOfOper(vector<string> s);

    /**
     * cast vector to string, cut vec by 2 indexes
     * @param begin index
     * @param end index
     * @return cutted string
     */
    string vectorToString(int begin, int end);

protected:
    /**
     * vec of all commands in block under condition
     */
    vector<Command *> conditionCommandList;

public:
    /**
     * CTOR
     * @param mapPath map: var name to its path
     * @param serverMap map: var name to its value
     */
    ConditionParser(DoubleMap *mapPath, map<string, double> *serverMap);

    void setParam(vector<string> parameters) override;

    /**
     * add command to vec
     * @param c pointer to command
     */
    void addCommand(Command *c);

    /**
     * calc the condition
     * @return if condition is true
     */
    bool checkCondition();

    virtual void execute() = 0;
};

/**
 * command: while loop of commands
 */
class LoopCommand : public ConditionParser {
public:
    void execute() override;

protected:
public:
    LoopCommand(DoubleMap *mapPath, map<string, double> *server);
};

/**
 * command: if block of commands
 */
class IfCommand : public ConditionParser {
public:
    IfCommand(DoubleMap *mapPath, map<string, double> *server);

    void execute() override;
};

/**
 * command: assigment
 * set value of one var
 * this command connect to simulator and set var
 */
class AssingmentCommand : public Command {
public:
    void execute() override;

    AssingmentCommand(DoubleMap *mapPath, map<string, double> *serverMap);
};

/**
 * command: print to monitor
 */
class PrintCommand : public Command {
public:
    PrintCommand(DoubleMap *mapPath, map<string, double> *server);

    void execute() override;
};

/**
 * commamd: sleep for x seconds
 */
class SleepCommand : public Command {
public:
    void execute() override;

protected:
public:
    SleepCommand(DoubleMap *mapPath, map<string, double> *server);
};

#endif //PROJECT_COMMAND_H
