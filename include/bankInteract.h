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

using namespace std;



class interact {
private:
    user *head;
public:
    interact():head(NULL){};
    user* getHead() { return head; }
    void regAcc();
    void AddAcc(accountNode x); 
    void deposit();
    string randAccNum();
    bool uniqueAccountNumber(const string& accountNumber);
    void creationDetails(user* account);
    void display();
    void withdraw();
    void changePin();
    void fundTransfer();
    
    //bool scandrive();
    //void saveToUSB();
    //bool retrieveFromUSB();
    
    //bool retrieveAccountNumbersFromUSB();
};

/*void interact::debugdisplay(){
    user *p;
    p = head;
    if(head == NULL){
        cout<<"NO LINK LIST FOUND";
        system("pause");
    }
    while (p!=NULL){
        cout<<"acc: "<<p->data.accountName<<endl;
        p=p->next;
        system("pause");
    }
}*/



void interact::regAcc() {
    accountNode x;
        string newname;
        string pin,accountNumber;
        cout<<"INPUT YOUR NAME: "<<endl;
        cin>>newname;
       do {
        cout << "Enter your pin code (it must be exactly 4 or 6 digits): "; cin >> pin;
        if (pin.length() != 4 && pin.length() != 6) {
            cout << "Invalid PIN! Please enter exactly 4 or 6 digits." << endl;
        }
    } while (pin.length() != 4 && pin.length() != 6);
       do {
        accountNumber = randAccNum(); 
    } while (!uniqueAccountNumber(accountNumber));
        x.accountName = newname;
        x.balance = 5000;
        x.accountPin = pin;
        x.accountNumber = accountNumber;
        AddAcc(x);
        cout<<" ACCOUNT SUCCESSFULLY CREATED"<<endl;
        system("pause");
}

    void interact::AddAcc(accountNode x) {    
        user *newNode = new user(x);
        if(head == NULL) {
            head = newNode;
        }else{
            user *p = head;
            while (p->next != NULL) {
                p=p->next;
            }
            p->next=newNode;
        }
      
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
    user *currentNode = getHead();
    while (currentNode != nullptr) {
        if (currentNode->data.accountNumber == accountNumber) {
            return false;
        }
        currentNode = currentNode->next;
    }
    return true;
}

void interact::creationDetails(user* account){
    system("cls");
        cout << "Account Details:" << endl;
        cout << "----------------------------" << endl;
        cout << "Name: " << account->data.accountName << endl;
        cout << "Account Number: " << account->data.accountNumber << endl;
        cout << "Balance: Php " << account->data.balance << endl;
        cout << "PIN: " << account->data.accountPin << endl;  // You might not want to display the PIN for security reasons
        cout << "----------------------------" << endl << endl;
        cout << "Press enter to continue"; 
        getch();
    }

void interact::deposit() {
    string accountIdentifier, accountIdentifierPin;
    system("cls");
    cout << "Enter your Account Name or Number: "; cin.ignore(); getline(cin, accountIdentifier);
    cout << endl << "Enter your Account Pin: "; getline(cin, accountIdentifierPin);
    user *currentNode = head;
    while (currentNode != nullptr) {
        if ((currentNode->data.accountNumber == accountIdentifier || currentNode->data.accountName == accountIdentifier) && (currentNode->data.accountPin == accountIdentifierPin)) {
            double amount;
            cout << "Enter amount to deposit: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount. Please enter a positive value." << endl;
                getch();
                return;
            }

            // Update the balance
            currentNode->data.balance += amount;
            cout << "Successfully deposited " << amount << " into account " << currentNode->data.accountNumber << endl;
            cout << "New balance: " << currentNode->data.balance << endl << endl;
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

    user *currentNode = head;
    while (currentNode != nullptr) {
        if ((currentNode->data.accountNumber == accountIdentifier || currentNode->data.accountName == accountIdentifier) && currentNode->data.accountPin == accountIdentifierPin) {
            cout << "Maintaining Balance for IBM ATM: 500"<<endl<<endl;
            double amount; 
            cout << "Enter amount to withdraw: "; 
            cin >> amount;

            if (amount > currentNode->data.balance) {
                cout << "Balance in account is insufficient" <<endl;
                getch();
                return;
            }

            currentNode->data.balance -= amount;
            cout << "Successfully Withdrawn " << amount << " from account " << currentNode->data.accountNumber << endl;
            cout << "New balance: " << currentNode->data.balance << endl << endl;
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


    user *currentNode = head;
    while (currentNode != nullptr) {
        if ((currentNode->data.accountNumber == accountIdentifier || currentNode->data.accountName == accountIdentifier) && currentNode->data.accountPin == accountIdentifierPin) {
            cout << "Account Name: " << currentNode->data.accountName << endl;
            cout << "Account Number: " << currentNode->data.accountNumber << endl;
            cout << "Account Balance: " << currentNode->data.balance <<endl <<endl;
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

    user *currentNode = head;
    while (currentNode != nullptr) {
        if (currentNode->data.accountNumber == accountIdentifier || currentNode->data.accountName == accountIdentifier) {
            cout << "Account Name: " << currentNode->data.accountName << endl<<endl;

            cout << "Enter Current Pin: ";
            cin >> currPin;

            if (currPin == currentNode->data.accountPin) {
                cout << "Enter New Pin: ";
                cin >> newPin;

                cout << "Confirm New Pin: ";
                cin >> newPinConfirm; 
                if (newPin == newPinConfirm) {
                    currentNode->data.accountPin = newPin;
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

    user *currentNode, *recipientNode;
    currentNode = head;
    recipientNode = head;
    while (currentNode != nullptr) {
        if ((currentNode->data.accountNumber == accountIdentifier || currentNode->data.accountName == accountIdentifier) && currentNode->data.accountPin == accountIdentifierPin) {
            break;
        }
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr) {
        cout << "Account not found or Incorrect Password. Please check the account name or number." << endl;
        getch();
    }

    system("cls");
    cout << "Welcome " << currentNode->data.accountName << endl<<endl;
    cout << "Enter Recipient Name or Account Number: "; getline(cin, accountIdentifierRecipient);

    while (recipientNode != nullptr) {
        if (recipientNode->data.accountNumber == accountIdentifierRecipient || recipientNode->data.accountName == accountIdentifierRecipient) {
            break;
        }
        recipientNode = recipientNode->next;
    }

    if (recipientNode == nullptr) {
        cout << "Account not found or Incorrect Password. Please check the account name or number." << endl;
        getch();
        return;
    }

    cout << "Enter Amount to Transfer to Recipient: " <<recipientNode->data.accountName<<endl;
    cout << "Amount: "; cin >> recipientAmount;

    if (recipientAmount < 0) {
        cout << "Invalid amount. Please enter a positive value." << endl;
        getch();
        return;
    }

    if (recipientAmount > currentNode->data.balance) {
        cout << "Insufficient balance. Transaction failed." << endl;
        getch();
        return;
    }

    cout << endl<<"Confirm Fund Transfer to User " <<recipientNode->data.accountName<<endl;
    cout << "Press Y to proceed and N to cancel: "; cin >> action;
    if (action == 'Y' || action == 'y') {
        cout << "Confirming Fund Transfer to " << recipientNode->data.accountName<<endl;
        currentNode->data.balance -= recipientAmount;
        recipientNode->data.balance += recipientAmount;

        cout << "Fund Transfer Complete" <<endl;
        cout << "Current balance for " << currentNode->data.accountName<< " is: " << currentNode->data.balance<<endl;
        cout << "Current balance for " << recipientNode->data.accountName<< " is: " << recipientNode->data.balance<<endl;
        cout << "Press Enter to Return to Main Menu" << endl;
        getch();
    } 
    else {
        cout << "Fund Transfer Cancelled" <<endl;
        cout << "Press Enter to Return to Main Menu" << endl;
        getch();
    }
}

//-----------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------


#endif