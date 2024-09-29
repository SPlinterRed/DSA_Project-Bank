#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <iostream>

using namespace std;

struct accountNode {
    string accountName;
    string accountNumber;
    long int balance;
    string accountPin;
    accountNode* next;
    accountNode(string name, string number, long int balance, string pin) : accountName(name), accountNumber(number), balance(balance), accountPin(pin), next(nullptr) {}
};

#endif