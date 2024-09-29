#ifndef BANKINTERACT_H
#define BANKINTERACT_H

#include <iostream>
// #include <filesystem>
#include <windows.h>
#include "myStruct.h"
#include <fstream>
#include "atm.h"
#include "fileHandling.h"

class interact {
private:
    accountNode* head;
public:
    void regAcc();
    void deposit();
};

#endif