#ifndef BANKINTERACT_H
#define BANKINTERACT_H

#include <iostream>
#include <string>
#include <set>
// #include <filesystem>
#include <windows.h>
#include "myStruct.h"
#include <fstream>
#include "atm.h"
#include "fileHandling.h"
#include "functionTools.h"

class interact : public generalTools {
private:
    accountNode* head;
public:
    interact() : head(nullptr) {}
    accountNode* getHead() { return head; }
    void regAcc(); 
    void deposit();
};

void interact::regAcc() {
    string name, pin;
}

#endif