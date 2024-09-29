#ifndef ATM_H
#define ATM_H

#include "myStruct.h"
#include "fileHandling.h"
#include "bankInteract.h"
#include "functionTools.h"
#include <iostream>

using namespace std;

class atmFunctions : public interact {
public:
    void withdraw();
};

#endif