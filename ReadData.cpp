/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/

#include "ReadData.h"
#include "Command.h"
#include <iterator>
#include <map>
#include <vector>

#include "OpenServerCommand.h"

/**
 * Create map command
 */
ReadData::ReadData() {
    this->mapSymb = new map<string, string>;
    this->serverMap = new map<string, double>;
    this->initMap();

    commandMap.insert(pair<string, Command *>("openDataServer", new OpenServerCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("connect", new ConnectCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("var", new DefineVarCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("while", new LoopCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("if", new IfCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("print", new PrintCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("sleep", new SleepCommand(this->mapSymb, this->serverMap)));
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
    ConditionParser *dad = nullptr;
    vector<Command *> commandList;
    for (vector<string> tmp:this->vec) {
        if (tmp.size() <= 1) {
            if (tmp.size() == 1 && tmp[0] == "}") {
                dad = dad->getDad();
            }
            continue;
        }
        Command *c;
        if (tmp[0] == "var") {
            c = new DefineVarCommand(this->mapSymb, this->serverMap);
        } else {
            c = this->commandMap[tmp[0]];
        }
        if (c == nullptr) {
            c = new AssingmentCommand(this->mapSymb, this->serverMap);
        } else {
            tmp.erase(tmp.begin());//delete the funcName
        }
        c->setParam(tmp);//send parameters
        if (dad != nullptr) {
            dad->addCommand(c);
        } else {
            commandList.push_back(c);
        }
        if (c->isDad) {
            c->setDad(dad);
            dad = (ConditionParser *) c;
        }
        string check = tmp[tmp.size() - 1];
        if (check == "}" || check[check.size() - 1] == '}') {
            dad = dad->getDad();
        }
//        c->execute();
    }

    for (Command *tmp:commandList) {
        tmp->execute();
    }


}//end of parser

/**
 * DTOR
 */
ReadData::~ReadData() {
    for (auto &c : this->commandMap) {
        delete c.second;
    }
}

const std::vector<vector<string>> &

ReadData::getVector() const {
    return this->vec;
}

bool ReadData::isVarInMap(string s) {
    return true;//todo checking before assigment
}

void ReadData::initMap() {
    this->serverMap->insert(pair<string, double>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/altimeter/indicated-altitude-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/altimeter/pressure-alt-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/heading-indicator/indicated-heading-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/internal-roll-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/encoder/indicated-altitude-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/encoder/pressure-alt-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/gps/indicated-altitude-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/gps/indicated-ground-speed-kt", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/gps/indicated-vertical-speed", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/heading-indicator/indicated-heading-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/turn-indicator/indicated-turn-rate", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
    this->serverMap->insert(pair<string, double>("/controls/flight/aileron", 0));
    this->serverMap->insert(pair<string, double>("/controls/flight/elevator", 0));
    this->serverMap->insert(pair<string, double>("/controls/flight/rudder", 0));
    this->serverMap->insert(pair<string, double>("/controls/flight/flaps", 0));
    this->serverMap->insert(pair<string, double>("/controls/engines/engine/throttle", 0));

}
