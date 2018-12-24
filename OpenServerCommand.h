
/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#ifndef PROJECT_OPENSERVERCOMMAND_H
#define PROJECT_OPENSERVERCOMMAND_H

#include "Command.h"
#include <stdio.h>
#include <string>

/**
 * Command: open server
 */
class OpenServerCommand : public Command {
protected:
    bool validate(vector<string> s) override;

public:

    OpenServerCommand(DoubleMap *mapPath, map<string, double> *serverMap);

    void execute() override;
};


#endif //PROJECT_OPENSERVERCOMMAND_H
