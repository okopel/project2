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
#include "DoubleMap.h"

class ReadData {

private:
    bool isVarInMap(string s);

    bool isOperator(char c);

    bool isBoolOperator(char c);

    bool isPar(char c);


    vector<vector<string>> vec;
    map<string, Command *> commandMap;
    DoubleMap *pathVarMap;
    //map<string, string> *mapSymb;
    map<string, double> *serverMap;

public:
    // ReadData(const std::vector<string> &vec);
    vector<string> arrangeVector(string line);

    void setVec(const vector<vector<string>> &vec);

    ReadData();

    ~ReadData();

    void lexer(string file);

    void parser();

    const std::vector<vector<string>> &getVector() const;
};


#endif //PROJECT_READDATA_H
