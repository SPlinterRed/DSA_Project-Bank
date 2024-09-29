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

class generalTools;

class interact {
private:
    accountNode* head;
public:
    interact() : generalTools(this), head(nullptr) {}
    accountNode* getHead() { return head; }
    void regAcc(); 
    void deposit();
};

void interact::regAcc() {
    string name, pin, accountNumber;
    cout << "Enter your Full name: "; getline(cin, name);
    do {
        cout << "Enter your pin code (it must be exactly 4 or 6 digits): "; cin >> pin;
        if (pin.length() != 4 && pin.length() != 6) {
            cout << "Invalid PIN! Please enter exactly 4 or 6 digits." << endl;
        }
    } while (pin.length() != 4 && pin.length() != 6);

    do {
        accountNumber = randAccNum(); 
    } while (!uniqueAccountNumber(accountNumber));

    accountNode* newAccount = new accountNode(name, accountNumber, 0, pin);

    if (head == nullptr) {
        head = newAccount;
    } else {
        accountNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newAccount;
    }
    cout << "Account created successfully!";
}

#endif