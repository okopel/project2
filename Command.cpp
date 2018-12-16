//
// Created by shlomo on 16/12/18.
//

#include "Command.h"
#include "Client.cpp"

/*int IfCommand::execute(string s) {
    if condition == true
    for each Command c in commands
    c.execute()
}*/

/**
 *
 * @param s
 * @return 3, move index 3 steps forward
 */
int OpenServerCommand::execute(string s) {
    // open server
    return 3;
}

int ConnectCommand::execute(string s) {
    // open client

    
    return 3;
}

int DefineVarCommand::execute(string s) {
    return Command::execute(s);
}

int LoopCommand::execute(string s) {
    return ConditionParser::execute(s);
}

int ConditionParser::execute(string s) {
    return Command::execute(s);
}

int IfCommand::execute(string s) {
    return ConditionParser::execute(s);
}

int FuncCommand::execute(string s) {
    return Command::execute(s);
}
