
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

class OpenServerCommand : public Command {
protected:
    bool validate(vector<string> s) override;

    void initMap();

public:
    OpenServerCommand(map<string, string> *map);

    int execute() override;
};


#endif //PROJECT_OPENSERVERCOMMAND_H
