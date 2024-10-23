#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <iostream>

using namespace std;

struct accountNode {
    string accountName;
    string accountNumber;
    long double balance;
    string accountPin;
    string yearOfBirth;
    string dayofBirth;
    string monthofBirth;
    string contactNumber;
};

struct user{
    accountNode data;
    user* next;
    user(accountNode x):data(x),next(NULL){}
};

#endif