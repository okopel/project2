/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

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
    bool isVarInMap(string s);

    vector<vector<string>> vec;
    map<string, Command *> commandMap;
    map<string, string> *mapSymb;

public:
    ReadData(const std::vector<string> &vec);

    ReadData();

    ~ReadData();

    void lexer(string file);

    void parser();

    const std::vector<vector<string>> &getVector() const;
};


#endif //PROJECT_READDATA_H
