#ifndef BANKINTERACT_H
#define BANKINTERACT_H

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <chrono>
// #include <filesystem>
#include "myStruct.h"
#include "atm.h"
#include "fileHandling.h"
#include "functionTools.h"

class interact {
private:
    accountNode* head;
public:
    accountNode* getHead() { return head; }
    void regAcc(); 
    void deposit();
    string randAccNum();
    bool uniqueAccountNumber(const string& accountNumber);
    void creationDetails(accountNode* account);
};

void interact::regAcc() {
    string name, pin, accountNumber;
    cout << "Enter your Full name: "; cin.ignore(); getline(cin, name);
    do {
        cout << "Enter your pin code (it must be exactly 4 or 6 digits): "; cin >> pin;
        if (pin.length() != 4 && pin.length() != 6) {
            cout << "Invalid PIN! Please enter exactly 4 or 6 digits." << endl;
        }
    } while (pin.length() != 4 && pin.length() != 6);

    do {
        accountNumber = randAccNum(); 
    } while (!uniqueAccountNumber(accountNumber));

    accountNode* newAccount = new accountNode(name, accountNumber, 5000, pin);

    if (head == nullptr) {
        head = newAccount;
    } else {
        accountNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newAccount;
    }
    cout << "Account created successfully!" << endl;
    creationDetails(newAccount);
}

string interact::randAccNum() {
    static mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<> distr(0, 999999999);

    int number = distr(gen);
    ostringstream intToNum;
    intToNum << setw(9) << setfill('0') << number;

    return intToNum.str();
}

bool interact::uniqueAccountNumber(const string& accountNumber) {
    accountNode* currentNode = getHead();
    while (currentNode != nullptr) {
        if (currentNode->accountNumber == accountNumber) {
            return false;
        }
        currentNode = currentNode->next;
    }
    return true;
}

void interact::creationDetails(accountNode* account) {
    if (account != nullptr) {
        cout << "Account Details:" << endl;
        cout << "----------------------------" << endl;
        cout << "Name: " << account->accountName << endl;
        cout << "Account Number: " << account->accountNumber << endl;
        cout << "Balance: Php " << account->balance << endl;
        cout << "PIN: " << account->accountPin << endl;  // You might not want to display the PIN for security reasons
        cout << "----------------------------" << endl << endl;
        cout << "Press enter to continue"; 
        getch();

    } else {
        cout << "Error: Account information is invalid.\n";
    }
}
#endif