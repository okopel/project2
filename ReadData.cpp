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
//    this->mapSymb = new map<string, string>;
    this->serverMap = new map<string, double>;
    this->initServerMap();
    this->pathVarMap = new DoubleMap;
/*    commandMap.insert(pair<string, Command *>("openDataServer", new OpenServerCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("connect", new ConnectCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("var", new DefineVarCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("while", new LoopCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("if", new IfCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("print", new PrintCommand(this->mapSymb, this->serverMap)));
    commandMap.insert(pair<string, Command *>("sleep", new SleepCommand(this->mapSymb, this->serverMap)));*/
}

void ReadData::initServerMap() {
    this->serverMap->insert(pair<string, double>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/altimeter/indicated-altitude-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/altimeter/pressure-alt-ft", 0));
    this->serverMap->insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
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

/**
 * parse the line to exp, operator, expression etc
 * @param line string of line
 * @return vector
 */
vector<string> ReadData::arrangeVector(string line) {
    vector<string> vector;
    string buffer;
    bool isPath = false;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '"') {
            if (!buffer.empty() && !isPath) {
                vector.push_back(buffer);
                buffer = "";
            }
            buffer += line[i];
            isPath = !isPath;
        } else if (isPath) {
            buffer += line[i];
        } else if (line[i] == ',' || line[i] == ' ') {
            if (!buffer.empty()) {
                vector.push_back(buffer);
                buffer = "";
            }
            continue;
        } else if (isalpha(line[i])) {
            buffer += line[i];
        } else if (line[i] == '.' || isdigit(line[i])) {
            buffer += line[i];
        } else if (isOperator(line[i]) || isPar(line[i])) {//+-*/() case so this has to enter alone
            if (!buffer.empty()) {
                vector.push_back(buffer);
                buffer = "";
            }
            buffer += line[i];
            vector.push_back(buffer);
            buffer = "";
        } else if (isBoolOperator(
                line[i])) { // != < > <= >= == case so we check if is lonely operator or double operator(==)
            if (!buffer.empty()) {
                vector.push_back(buffer);
                buffer = "";
            }
            int i2 = i + 1;
            while ((i2 < line.size()) && line[i2] == ' ') {
                i2++;
            }
            if (isBoolOperator(line[i2])) {
                buffer += line[i];
                buffer += line[i2];
                vector.push_back(buffer);
                buffer = "";
                i = i2;
                continue;
            } else {
                buffer += line[i];
                vector.push_back(buffer);
                buffer = "";
                continue;
            }
        }

    }
    if (!buffer.empty()) {
        vector.push_back(buffer);
    }

    //arange ++ or -- or +- or -+ case
    for (int i = 0; i < vector.size() - 1; i++) {
        if ((vector[i] == "-" && vector[i + 1] == "-") || ((vector[i] == "+") && vector[i + 1] == "+")) {
            vector[i] = "+";
            vector.erase(vector.begin() + i + 1);
            i = 0;
        }
        if ((vector[i] == "-" && vector[i + 1] == "+") || (vector[i] == "+" && vector[i + 1] == "-")) {
            vector[i] = "-";

            vector.erase(vector.begin() + i + 1);
            i = 0;
        }
    }
    return vector;
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
        //each line in a node
        if (!s.empty()) {
            this->vec.push_back(this->arrangeVector(s));
        }
    }
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
                continue;
            } else if (tmp.size() == 0) {
                continue;
            }
        }
        Command *c = nullptr;
        if (tmp[0] == "var") {
            c = new DefineVarCommand(this->pathVarMap, this->serverMap);
        } else if (tmp[0] == "print") {
            c = new PrintCommand(this->pathVarMap, this->serverMap);
        } else if (tmp[0] == "if") {
            c = new IfCommand(this->pathVarMap, this->serverMap);
        } else if (tmp[0] == "while") {
            c = new LoopCommand(this->pathVarMap, this->serverMap);
        } else if (tmp[0] == "sleep") {
            c = new SleepCommand(this->pathVarMap, this->serverMap);
        } else if (tmp[0] == "openDataServer") {
            c = new OpenServerCommand(this->pathVarMap, this->serverMap);
        } else if (tmp[0] == "connect") {
            c = new ConnectCommand(this->pathVarMap, this->serverMap);
        } else if (tmp[0] == "enterc" || tmp[0] == "Enterc") {
            c = new EnterCCommand(this->pathVarMap, this->serverMap);
        }
        if (c == nullptr) {
            c = new AssingmentCommand(this->pathVarMap, this->serverMap);
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
            //c->setDad(dad);
            dad = (ConditionParser *) c;
        }
        string check = tmp[tmp.size() - 1];
        if (check == "}" || check[check.size() - 1] == '}') {
            dad = dad->getDad();
        }
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


bool ReadData::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool ReadData::isBoolOperator(char c) {
    return (c == '>' || c == '<' || c == '=' || c == '!');
}

bool ReadData::isPar(char c) {
    return (c == ')' || c == '(' || c == '{' || c == '}');
}

void ReadData::setVec(const vector<vector<string>> &vec) {
    ReadData::vec = vec;
}
