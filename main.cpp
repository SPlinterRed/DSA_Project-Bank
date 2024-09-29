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
    void startMenu();
    void bankMenu();
    void atmMenu();
};

int main() {
    menus option;
    option.startMenu();
}

void menus::startMenu() {
    int  option;
    do {
        system("cls");
        cout << "What do you want to do" << endl << endl;
        cout << "1. Interact with the Bank" << endl;
        cout << "2. Withdraw money from the ATM" << endl;
        cout << "3. Exit Program" << endl << endl;
        cout << ">: "; cin >> option;
    } while (option != 3);
}

void menus::bankMenu() {

}

void menus::atmMenu() {

}