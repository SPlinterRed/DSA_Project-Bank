#include <iostream>
#include <string>
#include "include/bankInteract.h"
#include "include/myStruct.h"

using namespace std;

class menus {
public:
    int startMenu();
    int bankMenu();
    int atmMenu();
};
interact bankInteract;

int main(){
    if(bankInteract.isFlashDriveInserted()){
    menus option;
    bankInteract.retrievelocal();
    system("pause");
    bool mainMenuCheck = true;
    do {
        bool menuCheck = true;
        switch(option.startMenu()) {
            case 1: 
                while(menuCheck){
                    switch(option.bankMenu()) {
                        case 1:
                            bankInteract.flashDriveChecker();
                            bankInteract.regAcc();
                            bankInteract.saveLocal();
                            break;
                        case 2:
                            bankInteract.depositLocal();
                            bankInteract.saveLocal();
                            break;
                        case 3:
                            bankInteract.saveLocal();
                            menuCheck = false;
                            break;
                        default: 
                            cout << "No such options"; break;
                    }
                }
                break;
            case 2:
                do {
                    system("cls");
                    cout << "Please insert USB / FLASHDRIVE";
                    for (int i = 0; i < 3; ++i) {
                        Sleep(300);
                        cout << ".";
                    }
                } while (!bankInteract.checkFlashDrive());
                while (menuCheck) {
                    switch (option.atmMenu()) {
                        case 1:  
                            bankInteract.display();
                            break;
                        case 2:
                            bankInteract.withdraw();
                            bankInteract.updateOriginalList();
                            break;
                        case 3:
                            bankInteract.deposit();
                            bankInteract.updateOriginalList();
                            break;
                        case 4:
                            bankInteract.fundTransfer();
                            bankInteract.updateOriginalList();
                            break;
                        case 5:
                            bankInteract.changePin();
                            bankInteract.updateOriginalList();
                            break;
                        case 6:
                            bankInteract.saveLocal();
                            menuCheck = false;
                            break;
                        default: 
                            cout << "No such options"; 
                            break;
                    }
                }
                break; 
            case 3: 
                system("cls");
                cout << "Thanks for using the program, Have a Nice day" << endl << endl;
                cout << "Press Enter to Continue";
                mainMenuCheck = false;
                getch();
                break;
            default: 
                cout << "No such options"; break;
        }
    }while(mainMenuCheck);
    return 0;
}
cout<<"PLEASE INSERT FLASHDRIVE";
    return 0;
}
    
    

int menus::startMenu() {
    int  option;
    system("cls");
    cout << "What do you want to do" << endl << endl;
    cout << "1. Interact with the Bank" << endl;
    cout << "2. Interact with ATM Machine" << endl;
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
    cout << "6. Exit and Save" << endl;
    cout << ":> "; cin >> option;
    return option;
}
