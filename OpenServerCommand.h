
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
    int execute() override;
};


#endif //PROJECT_OPENSERVERCOMMAND_H
