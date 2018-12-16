//
// Created by shlomo on 16/12/18.
//

#ifndef PROJECT_READDATA_H
#define PROJECT_READDATA_H

using namespace std;

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include "Command.h"

class ReadData {

private:
    vector<vector<string>> vec;
    map<string, Command *> commandMap;


public:
    ReadData(const std::vector<string> &vec);

    ReadData();

    ~ReadData();

    void lexer(string file);

    void parser();

    const std::vector<vector<string>> &getVector() const;
};


#endif //PROJECT_READDATA_H
