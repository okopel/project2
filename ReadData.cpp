//
// Created by shlomo on 16/12/18.
//

#include "ReadData.h"
#include "Command.h"
#include <iterator>
#include <map>


ReadData::ReadData(const vector<string> &vec) : vec(vec) {}

/**
 * Create map command
 */
ReadData::ReadData() {
    commandMap.insert(pair<string, Command*>("connect", new ConnectCommand()));
    commandMap.insert(pair<string, Command*>("openServer", new ConnectCommand()));
    commandMap.insert(pair<string, Command*>("var", new DefineVarCommand()));
}

const vector <string> &ReadData::getVector() const {
    return vec;
}

/**
 * make array of words
 * @param file of instructions
 */
void ReadData::lexer(string file){
    string s = "1";
    ifstream ifs;
    string buffer;
    ifs.open(file);
    if (!ifs.is_open()) { return; }

    // read lines from data file
    while (!s.empty()){
        s = "";
        getline(ifs, s);
        buffer += s;
        buffer+= " ";
    }
    // put each word in one node
    std::istringstream iss(buffer);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    this->vec = results;
    ifs.close();
}

void ReadData::parser(){
    int index = 0;

    Command* c = commandMap.at(this->vec.at(index));
    // execute all commands
    while(c != nullptr) {
        index += (*c).execute(this->vec.at(index));
    }
}

/**
 * DTOR
 */
ReadData::~ReadData(){
    for (auto &c : this->commandMap){
        delete c.second;
    }
}
