//
// Created by shlomo on 16/12/18.
//

#include "ReadData.h"
#include "Command.h"
#include <iterator>
#include <map>
#include <vector>


/**
 * Create map command
 */
ReadData::ReadData() {
    commandMap.insert(pair<string, Command *>("connect", new ConnectCommand()));
    commandMap.insert(pair<string, Command *>("openDataServer", new OpenServerCommand()));
    commandMap.insert(pair<string, Command *>("var", new DefineVarCommand()));

}


/**
 * make array of words
 * @param file of instructions
 */
void ReadData::lexer(string file) {
    string s = "1";
    ifstream ifs;
    ifs.open(file);
    if (!ifs.is_open()) { return; }

    // read lines from data file
    while (!s.empty()) {
        s = "";
        getline(ifs, s);
        //parse line to words
        std::istringstream iss(s);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());
        //each line in a node
        this->vec.push_back(results);
    }

//    this->vec = results;
    ifs.close();
}

/**
 *
 */
void ReadData::parser() {
    for (vector<string> tmp:this->vec) {
        Command *c = this->commandMap[tmp[0]];
        tmp.erase(tmp.begin());//delete the funcName
        c->execute(tmp);//send parameters
    }
}

/**
 * DTOR
 */
ReadData::~ReadData() {
    for (auto &c : this->commandMap) {
        delete c.second;
    }
}

const std::vector<vector<string>> &ReadData::getVector() const {
    return this->vec;
}
