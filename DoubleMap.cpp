/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#include "DoubleMap.h"

string DoubleMap::getPath(string var) {
    if (this->varToPath.count(var) > 0) {
        return this->varToPath.at(var);
    }
    return "";
}

string DoubleMap::getVar(string path) {
    if (this->pathToVar.count(path) > 0) {
        return this->pathToVar.at(path);
    }
    return "";
}

DoubleMap::DoubleMap() = default;

void DoubleMap::setArg(string var, string path) {
    if (this->pathToVar.count(path) > 0) {
        this->pathToVar[path] = var;
    }
    if (this->varToPath.count(var) > 0) {
        this->varToPath[var] = path;
    }
}

void DoubleMap::addArg(string var, string path) {
    this->pathToVar.insert(pair<string, string>(path, var));
    this->varToPath.insert(pair<string, string>(var, path));
}
