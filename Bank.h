// Bank.h
#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

struct details {
    std::string name;
    long int balance;
    int pin;
    long long int contact;
    int accountnum;
};

struct users {
    details accounts;
    users *next;
    users(details x) : accounts(x), next(NULL) {}
};

class Bank {
private:
    users *head;
public:
    Bank();
    void regacc(); // Register new users
    void AddAcc(details x);
    int transaction(details x);
    void deactivate(long accountnumber);
    void retrieve();
    void save();
    details retrieveusb();
    bool accverify(int accountnum);
    void ftransfer(users* target, int amount);
    details locate(int accountnumver);
    int randomizer();
    int menu();
    users* locateaddress(int accountnum);
    int changepin(int curr);
    int pincreate(int pin);
    string filecheck(const std::string& filename);
    void saveusb(details x);
    bool isFlashDriveInserted();
};

int depochecker(int depp);

#endif
