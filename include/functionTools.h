#ifndef FUNCTIONTOOLS_H
#define FUNCTIONTOOLS_H

#include <iostream>
#include "myStruct.h"
#include "fileHandling.h"
#include "atm.h"
#include "bankInteract.h"
#include <random>
#include <iomanip>
#include <sstream>
#include <unordered_set>

using namespace std;

class generalTools{
private:
    interact bank;
    accountNode* current;
public:
    generalTools() : current(bank.getHead()) {}
    void locate();
    void lock();
    void del();
    void verify();
    string randAccNum();
    bool uniqueAccountNumber(const string& accountNumber);
};

string generalTools :: randAccNum() {
    random_device randNum;
    mt19937 gen(randNum());
    uniform_int_distribution<> distr(0, 999999999);

    int number = distr(randNum);
    ostringstream intToNum;
    intToNum << setw(9) << setfill('0') << number;

    return intToNum.str();
}

bool generalTools::uniqueAccountNumber(const string& accountNumber) {
    
}

#endif