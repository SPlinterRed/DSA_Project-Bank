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
    void bankMenu();
    void atmMenu();
};

int main() {
    menus option;
    do {
        switch(option.startMenu()) {
            case 1:
            case 2:
            case 3:
        }
    } while(true);
    
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

void menus::bankMenu() {

}

void menus::atmMenu() {

}