/*****************************
 * Project of:
 * Ori Kopel 205533151
 * Shlomo Rabinovich 308432517
 * December 18
 ******************************/
#include <iostream>
#include <thread>
#include "Client.h"


void Client::sendToClient(const string address, double val) {
//        if(!valifation()){throw..}
    string msg = "set " + address + " " + to_string(val) + "\r\n";
    int clientWrite = write(this->socketId, msg.c_str(), msg.length());
    if (clientWrite < 0) {
        throw "Error sending val by client";
    }
    cout << msg << " suuc" << endl;

}



