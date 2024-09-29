#include <iostream>
#include <string>
// #include <filesystem>
#include <windows.h>
#include "include/atm.h"
#include "include/bankInteract.h"
#include "include/fileHandling.h"
#include "include/myStruct.h"

using namespace std;

class menus {
public:
    int startMenu();
    int bankMenu();
    int atmMenu();
};

int main(){
    menus option;
    interact bankInteract;
    do {
        bool menuCheck = true;
        switch(option.startMenu()) {
            case 1: 
                while(menuCheck){
                    switch(option.bankMenu()) {
                        case 1: 
                            bankInteract.regAcc();
                            break;
                        case 2:
                            bankInteract.deposit();
                            break;
                        case 3:
                            menuCheck = false;
                            break;
                        default: 
                            cout << "No such options"; break;
                    }
                }
                break;
            case 2: 
                break;
            case 3: 
                break;
            default: 
                cout << "No such options"; break;
        }
    } while(true);
    return 0;
}

int menus::startMenu() {
    int  option;
    system("cls");
    cout << "What do you want to do" << endl << endl;
    cout << "1. Interact with the Bank" << endl;
    cout << "2. Withdraw money from the ATM" << endl;
    cout << "3. Exit Program" << endl << endl;
    cout << ">: "; cin >> option;

    return option;
}

int menus::bankMenu() {
    int  option;
    system("cls");
    cout << "What do you want to do" << endl << endl;
    cout << "1. Enroll for a Bank Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Return back to the main menu" << endl << endl;
    cout << ">: "; cin >> option;

    return option;
}

int menus::atmMenu() {
    int option;
    system("cls");
    cout << "What do you want to do" << endl << endl;
    cout << "1. Display Balance" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Deposit" << endl;
    cout << "4. Fund Transfer" << endl;
    cout << "5. Change PIN" << endl;
    cout << "6. Exit" << endl;
    cout << ":> "; cin >> option;
    return option;
}