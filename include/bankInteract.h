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
    void display();
    void withdraw();
    void changePin();
    void fundTransfer();
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
        accountNode *current = head;
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
    accountNode *currentNode = getHead();
    while (currentNode != nullptr) {
        if (currentNode->accountNumber == accountNumber) {
            return false;
        }
        currentNode = currentNode->next;
    }
    return true;
}

void interact::creationDetails(accountNode* account){
    system("cls");
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

void interact::deposit() {
    string accountIdentifier, accountIdentifierPin;
    system("cls");
    cout << "Enter your Account Name or Number: "; cin.ignore(); getline(cin, accountIdentifier);
    cout << endl << "Enter your Account Pin: "; getline(cin, accountIdentifierPin);
    accountNode *currentNode = head;
    while (currentNode != nullptr) {
        if ((currentNode->accountNumber == accountIdentifier || currentNode->accountName == accountIdentifier) && (currentNode->accountPin == accountIdentifierPin)) {
            double amount;
            cout << "Enter amount to deposit: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount. Please enter a positive value." << endl;
                getch();
                return;
            }

            // Update the balance
            currentNode->balance += amount;
            cout << "Successfully deposited " << amount << " into account " << currentNode->accountNumber << endl;
            cout << "New balance: " << currentNode->balance << endl << endl;
            cout << "Press Enter to continue" << endl;
            getch();
            return;
        }
        currentNode = currentNode->next;
    }
    cout << "Account not found or Incorrect Password. Please check the account name or number." << endl;
    system("pause");
}

void interact::withdraw() {
    string accountIdentifier, accountIdentifierPin;
    system("cls");
    cout << "Enter your Account Name or Number: "; cin.ignore(); getline(cin, accountIdentifier);
    cout << endl << "Enter your Account Pin: "; getline(cin, accountIdentifierPin);

    accountNode *currentNode = head;
    while (currentNode != nullptr) {
        if ((currentNode->accountNumber == accountIdentifier || currentNode->accountName == accountIdentifier) && currentNode->accountPin == accountIdentifierPin) {
            cout << "Maintaining Balance for IBM ATM: 500"<<endl<<endl;
            double amount; 
            cout << "Enter amount to withdraw: "; 
            cin >> amount;

            if (amount > currentNode->balance) {
                cout << "Balance in account is insufficient" <<endl;
                getch();
                return;
            }

            currentNode->balance -= amount;
            cout << "Successfully Withdrawn " << amount << " from account " << currentNode->accountNumber << endl;
            cout << "New balance: " << currentNode->balance << endl << endl;
            cout << "Press Enter to continue" << endl;
            getch();
            return;
        }
        currentNode = currentNode->next;
    }
    cout << "Account not found or Incorrect Password. Please check the account name or number." << endl;
    system("pause");
}

void interact::display() {
    string accountIdentifier, accountIdentifierPin;
    system("cls");
    cout << "Enter your Account Name or Number: "; cin.ignore(); getline(cin, accountIdentifier);
    cout << endl << "Enter your Account Pin: "; getline(cin, accountIdentifierPin);

    accountNode *currentNode = head;
    while (currentNode != nullptr) {
        if ((currentNode->accountNumber == accountIdentifier || currentNode->accountName == accountIdentifier) && currentNode->accountPin == accountIdentifierPin) {
            cout << "Account Name: " << currentNode->accountName << endl;
            cout << "Account Number: " << currentNode->accountNumber << endl;
            cout << "Account Balance: " << currentNode->balance <<endl <<endl;
            cout << "Press Enter to Return to Main Menu" <<endl;
            getch();
            return;
        }
        currentNode = currentNode->next;
    }
    cout << "Account not found or Incorrect Password. Please check the account name or number." << endl;
    system("pause");
}


void interact::changePin() {
    string accountIdentifier, currPin, newPin, newPinConfirm;
    system("cls");
    cout << "Enter your Account Name or Number: "; cin.ignore(); getline(cin, accountIdentifier);

    accountNode *currentNode = head;
    while (currentNode != nullptr) {
        if (currentNode->accountNumber == accountIdentifier || currentNode->accountName == accountIdentifier) {
            cout << "Account Name: " << currentNode->accountName << endl<<endl;

            cout << "Enter Current Pin: ";
            cin >> currPin;

            if (currPin == currentNode->accountPin) {
                cout << "Enter New Pin: ";
                cin >> newPin;

                cout << "Confirm New Pin: ";
                cin >> newPinConfirm; 
                if (newPin == newPinConfirm) {
                    currentNode->accountPin = newPin;
                    cout << "Pin is now changed." <<endl;
                    getch();
                }
                else {
                    cout << "New Pins entered does not match each other" <<endl; 
                    getch();
                    return;
                }
            }
            else {
                cout << "Entered Pin does not match User Pin."<<endl;
                getch();
                return;
            }
        }
        currentNode = currentNode->next;
    }
    cout << "Account not found or Incorrect Password. Please check the account name or number." << endl;
    system("pause");
}

void interact::fundTransfer() {
    string accountIdentifier, accountIdentifierPin, accountIdentifierRecipient;
    char action;
    double recipientAmount;

    system("cls");
    cout << "Enter your Account Name or Number: "; cin.ignore(); getline(cin, accountIdentifier);
    cout << endl << "Enter your Account Pin: "; getline(cin, accountIdentifierPin);

    accountNode *currentNode, *recipientNode;
    currentNode = head;
    recipientNode = head;
    while (currentNode != nullptr) {
        if ((currentNode->accountNumber == accountIdentifier || currentNode->accountName == accountIdentifier) && currentNode->accountPin == accountIdentifierPin) {
            break;
        }
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr) {
        cout << "Account not found or Incorrect Password. Please check the account name or number." << endl;
        getch();
    }

    system("cls");
    cout << "Welcome " << currentNode->accountName << endl<<endl;
    cout << "Enter Recipient Name or Account Number: "; getline(cin, accountIdentifierRecipient);

    while (recipientNode != nullptr) {
        if (recipientNode->accountNumber == accountIdentifierRecipient || recipientNode->accountName == accountIdentifierRecipient) {
            break;
        }
        recipientNode = recipientNode->next;
    }

    if (recipientNode == nullptr) {
        cout << "Account not found or Incorrect Password. Please check the account name or number." << endl;
        getch();
        return;
    }

    cout << "Enter Amount to Transfer to Recipient: " <<recipientNode->accountName<<endl;
    cout << "Amount: "; cin >> recipientAmount;

    if (recipientAmount < 0) {
        cout << "Invalid amount. Please enter a positive value." << endl;
        getch();
        return;
    }

    if (recipientAmount > currentNode->balance) {
        cout << "Insufficient balance. Transaction failed." << endl;
        getch();
        return;
    }

    cout << endl<<"Confirm Fund Transfer to User " <<recipientNode->accountName<<endl;
    cout << "Press Y to proceed and N to cancel: "; cin >> action;
    if (action == 'Y' || action == 'y') {
        cout << "Confirming Fund Transfer to " << recipientNode->accountName<<endl;
        currentNode->balance -= recipientAmount;
        recipientNode->balance += recipientAmount;

        cout << "Fund Transfer Complete" <<endl;
        cout << "Current balance for " << currentNode->accountName<< "is: " << currentNode->balance<<endl;
        cout << "Current balance for " << recipientNode->accountName<< "is: " << recipientNode->balance<<endl;
        cout << "Press Enter to Return to Main Menu" << endl;
        getch();
    } 
    else {
        cout << "Cancelling Fund Transfer" <<endl;
        getch();
    }
}

#endif