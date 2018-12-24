/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/
#ifndef PROJECT_DOUBLEMAP_H
#define PROJECT_DOUBLEMAP_H

#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

/**
 * Double map to know the both sides of any map
 */
class DoubleMap {
    map<string, string> pathToVar;
    map<string, string> varToPath;
public:
    DoubleMap();

    string getPath(string var);

    string getVar(string path);

    void setArg(string var, string path);

    void addArg(string var, string path);

};


#endif //PROJECT_DOUBLEMAP_H
