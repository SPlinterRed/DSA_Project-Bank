#ifndef BANKINTERACT_H
#define BANKINTERACT_H

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "myStruct.h"

using namespace std;

class interact {
private:
    user *head;
    user *usbacc;
public:
    interact():head(NULL), usbacc(NULL){};
    user* getHead() { return head; }
    void regAcc(); 
    void AddAcc(accountNode x); 
    void deposit();
    void depositLocal();
    string randAccNum();
    bool uniqueAccountNumber(const string& accountNumber);
    void creationDetails(accountNode x);
    void display();
    void withdraw();
    void changePin();
    void fundTransfer();
    bool accverify(string& accountnum, accountNode& accountDetails);
    void saveLocal();
    void retrievelocal();
    bool checkFlashDrive();
    void saveUSB(const accountNode& account);
    bool flashDriveChecker();
    void updateOriginalList();
    string getpincode();
    string encrypt(string pin);
    string decrypt(string pin);
    bool isFlashDriveInserted();
};

void interact::regAcc() {
    accountNode x;
    string newname;
    string pin,accountNumber, contactnum;
    string year, date, month;
    long yearInt, monthInt, dateInt;
    cout<<"INPUT YOUR NAME: "; cin.ignore(); getline(cin, newname);
    do {
        pin = getpincode();
        cout << endl;
        if (pin.length() != 4 && pin.length() != 6) {
            cout << "Invalid PIN! Please enter exactly 4 or 6 digits." << endl;
       }
    } while (pin.length() != 4 && pin.length() != 6);

    do {
        accountNumber = randAccNum(); 
    } while (!uniqueAccountNumber(accountNumber));

    do {
        cout << "Enter your year of Birth: "; cin >> year;
        yearInt = stol(year);
        if (yearInt <= 0 || yearInt >= 2025) {
            cout << "Enter a year with the current era."<<endl;
        }
    } while (yearInt <= 0 || yearInt >= 2025);

    do {
        cout << "Enter Month of Birth (in number format Ex. January = 1): "; cin >> month;
        monthInt = stol(month);
        if (monthInt <= 0 || monthInt >= 13) {
            cout << "Enter a valid month (1-12)."<<endl;
        }
    } while (monthInt <= 0 || monthInt >= 13);

    switch(monthInt) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            do {
                cout << "Enter day of Birth(1-31): "; cin >> date;
                dateInt = stol(date);
                if (dateInt <= 0 || dateInt >= 32) {
                    cout << "Month entered only has 1-31 days."<<endl;
                }
            } while (dateInt <= 0 || dateInt >= 32);
            break;
        case 2:
            do {
                cout << "Enter day of Birth(1-29): "; cin >> date;
                dateInt = stol(date);
                if (dateInt <= 0 || dateInt >= 32) {
                    cout << "Month entered only has 1-28/29 days."<<endl;
                }
            } while (dateInt <= 0 || dateInt >= 30);
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            do {
                cout << "Enter day of Birth(1-30): "; cin >> date;
                dateInt = stoi(date);
                if (dateInt <= 0 || dateInt >= 32) {
                    cout << "Month entered only has 1-30 days."<<endl;
                }
            } while (dateInt <= 0 || dateInt >= 31);
            break;
    }

    do {
        cout << "Enter your Contact Number(11 Digits): "; cin >> contactnum;
        if (contactnum.length() != 11) {
            cout << "Invalid Contact Number! Enter 11 Digits." << endl;
       }
    } while (contactnum.length() != 11);

    x.accountName = newname;
    x.balance = 5000;
    x.accountPin = pin;
    x.accountNumber = accountNumber;
    x.dayofBirth = date;
    x.monthofBirth = month;
    x.yearOfBirth = year;
    x.contactNumber = contactnum;

    AddAcc(x);
    creationDetails(x);
    saveUSB(x);
    cout<<" ACCOUNT SUCCESSFULLY CREATED"<<endl;
    system("pause");
}

void interact::AddAcc(accountNode x) {    
    user *newNode = new user(x);
    if(head == NULL) {
        head = newNode;
    } else {
        user *p = head;
        while (p->next != NULL) {
            p=p->next;
        }
        p->next=newNode;
    }
}

string interact::randAccNum() {
    srand(std::time(0));
    int number = std::rand() % 100000;

    ostringstream intToNum;
    intToNum << setw(5) << setfill('0') << number;

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

void interact::creationDetails(accountNode x){
    system("cls");
    string encryptpass = encrypt(x.accountPin);
    cout << "Account Details:" << endl;
    cout << "----------------------------" << endl;
    cout << "Name: " << x.accountName << endl;
    cout << "Account Number: " << x.accountNumber << endl;
    cout << "Birthday: " << x.monthofBirth << " / " << x.dayofBirth << " / " << x.yearOfBirth << endl;
    cout << "Contact Number: " << x.contactNumber << endl;
    cout << "Balance: Php " << x.balance << endl;
    cout << "PIN: " << encryptpass << endl;
    cout << "----------------------------" << endl << endl;
    cout << "Press enter to continue"; 
    getch();
}

void interact::depositLocal() {
    system("cls");
    
    string accountnum;
    cout << "Enter your account number: ";
    cin >> accountnum;

    user *currentNode = head;
    while (currentNode != nullptr) {
        if (currentNode->data.accountNumber == accountnum) {
            break;
        }
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr) {
        cout << "Account not found." << endl;
        getch();
        return;
    }

    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Please enter a positive value." << endl;
        getch();
        return;
    }

    currentNode->data.balance += amount;
    cout << "Successfully deposited " << amount << " into account " << currentNode->data.accountNumber << endl;
    cout << "New balance: " << currentNode->data.balance << endl << endl;
    cout << "Press Enter to continue" << endl;
    getch();
}

void interact::deposit() {
    system("cls");
    user *currentNode = usbacc;
    
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Please enter a positive value." << endl;
        getch();
        return;
    }

    currentNode->data.balance += amount;
    cout << "Successfully deposited " << amount << " into account " << currentNode->data.accountNumber << endl;
    cout << "New balance: " << currentNode->data.balance << endl << endl;
    cout << "Press Enter to continue" << endl;
    getch();
    return;
    
    system("pause");
}

void interact::withdraw() {
    system("cls");

    user *currentNode = usbacc;
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
    system("pause");
}

void interact::display() {
    system("cls");

    user *currentNode = usbacc;
    while (currentNode != nullptr) {
            cout << "Account Name: " << currentNode->data.accountName << endl;
            cout << "Account Number: " << currentNode->data.accountNumber << endl;
            cout << "Account Balance: " << currentNode->data.balance <<endl <<endl;
            cout << "Press Enter to Return to Main Menu" <<endl;
            getch();
            return;
    }
    cout << "Account not found or Incorrect Password. Please check the account name or number." << endl;
    system("pause");
}

void interact::changePin() {
    string currPin,newPin,newPinConfirm;
    system("cls");

    user *currentNode = usbacc;
   
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
    system("pause");
}

void interact::fundTransfer() {
    string accountIdentifierRecipient;
    char action;
    double recipientAmount;

    system("cls");

    user *currentNode = usbacc, *recipientNode = head;

    system("cls");
    cout << "Enter Recipient Name or Account Number: "; cin>> accountIdentifierRecipient;

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

void interact::saveLocal() {
    ofstream myFile("BankAccounts.txt");
    if (!myFile) {
        cout << "File Error" << endl;
        return;
    }

    user* p = head;
    while (p != NULL) {
        string encryptpass = encrypt(p->data.accountPin);
        myFile << "Name: " << p->data.accountName << endl
               << "AccountNumber: " << p->data.accountNumber << endl
               << "Balance: " << p->data.balance << endl
               << "accountPin: " << encryptpass << endl
               << "Birthday: " << p->data.monthofBirth << " / "
               << p->data.dayofBirth << " / "
               << p->data.yearOfBirth << endl
               << "Contact Number: " << p->data.contactNumber << endl 
               << "----------------------------------------" << endl;

        p = p->next;
    }
    
    myFile.close();
    cout << "Data saved T_T" << endl;
}

void interact::retrievelocal() {
    ifstream myFile("BankAccounts.txt");
    if (!myFile) {
        cout << "File Error." << endl;
        return;
    }

    string line;
    accountNode p;
    string header;

    while (getline(myFile, line)) {
        if (line.empty()) continue;

        if (line.find("Name: ") == 0) {
            p.accountName = line.substr(6);
        } else if (line.find("AccountNumber: ") == 0) {
            p.accountNumber = line.substr(15);
        } else if (line.find("Balance: ") == 0) {
            p.balance = stod(line.substr(9));
        } else if (line.find("accountPin: ") == 0) {
            p.accountPin = line.substr(12);
            p.accountPin = decrypt(p.accountPin);
        } else if (line.find("Birthday: ") == 0) {
            string birthday = line.substr(10);
            size_t firstSlash = birthday.find('/');
            size_t secondSlash = birthday.find('/', firstSlash + 1);

            if (firstSlash != string::npos && secondSlash != string::npos) {
                p.monthofBirth = birthday.substr(0, firstSlash);
                p.dayofBirth = birthday.substr(firstSlash + 2, secondSlash - firstSlash - 2);
                p.yearOfBirth = birthday.substr(secondSlash + 2);
            }
        } else if (line.find("ContactNumber: ") == 0) {
            p.contactNumber = line.substr(10);
        }

        if (line == "----------------------------------------") {
            AddAcc(p);
        }
    }
    
    myFile.close();
    cout << "Data retrieved successfully!" << endl;
}

bool interact::accverify(string& accountnum, accountNode& accountDetails) {
    user* x = head;
    string numpin;
    char ch;
    
    while (x != NULL) {
        if (x->data.accountNumber == accountnum) {
            accountDetails = x->data;
            cout << "PLEASE INPUT PIN: ";
            while ((ch = getch()) != '\r') {
                if (ch >= '0' && ch <= '9') {
                    numpin += ch;
                    cout << "*";
                }
                else if (ch == '\b') {
                    if (!numpin.empty()) {
                        cout << "\b \b";
                        numpin.pop_back();
                    }
                 }
            }
            int attempts = 3;
            while (x->data.accountPin != numpin && attempts > 0) {
                cout << "Incorrect Pin. Attempts left: " << --attempts << endl;
                if (attempts == 0) {
                    cout << "Too many incorrect attempts.\n";
                    return false; 
                }
                cout << "Please input correct pin: ";
                while ((ch = getch()) != '\r') {
                    if (ch >= '0' && ch <= '9') {
                        numpin += ch;
                        cout << "*";
                    }
                    else if (ch == '\b') {
                        if (!numpin.empty()) {
                            cout << "\b \b";
                            numpin.pop_back();
                        }
                    }
                }
            }
            return true;
        }
        x = x->next;
    }
    return false;
}

void interact::saveUSB(const accountNode& account) {
    DWORD drives = GetLogicalDrives();

    for (char drive = 'A'; drive <= 'Z'; ++drive) {
        if (drives & (1 << (drive - 'A'))) {
            string drivePath = string(1, drive) + ":\\"; 
            UINT driveType = GetDriveTypeA(drivePath.c_str());

            if (driveType == DRIVE_REMOVABLE) {
                string filePath = drivePath + "BankAccounts.txt";

                ofstream myFile(filePath);

                if (!myFile) {
                    cout << "File Error on " << filePath << endl;
                    return;
                }

                myFile << "AccountNumber" << endl << account.accountNumber << endl;

                myFile.close();
                cout << "Data saved to USB at " << filePath << " successfully!" << endl;
                return;
            }
        }
    }
    cout << "No removable drive detected, data not saved." << endl;
}

bool interact::flashDriveChecker() {
    DWORD drives = GetLogicalDrives();

    for (char drive = 'A'; drive <= 'Z'; ++drive) {
        if (drives & (1 << (drive - 'A'))) {
            string drivePath = string(1, drive) + ":\\";
            UINT driveType = GetDriveTypeA(drivePath.c_str());

            if (driveType == DRIVE_REMOVABLE) {
                string filePath = drivePath + "BankAccounts.txt";

                ifstream myFile(filePath);
                if (myFile) {
                    cout << "Found BankAccounts.txt on drive " << drivePath << endl;
                    myFile.close();
                    return true;
                }
            }
        }
    }
    cout << "No BankAccounts.txt found on any USB drive." << endl;
    return false;
}

bool interact::checkFlashDrive() {
    DWORD drives = GetLogicalDrives();
    string accountNum;
    
    for (char drive = 'A'; drive <= 'Z'; ++drive) {
        if (drives & (1 << (drive - 'A'))) {
            string drivePath = string(1, drive) + ":\\"; 
            UINT driveType = GetDriveTypeA(drivePath.c_str());
            if (driveType == DRIVE_REMOVABLE) {
                string filePath = drivePath + "BankAccounts.txt";
                ifstream myFile(filePath);
                
                if (myFile) {
                    cout << "Found BankAccounts.txt on drive " << drivePath << endl;
                    string line;
                    while (getline(myFile, line)) {
                        if (line == "AccountNumber") {
                            if (getline(myFile, accountNum)) {
                                cout << "Account Number: " << accountNum << endl;
                                break;
                            }
                        }
                    }
                    myFile.close();
                    accountNode accountDetails;
                    if (accverify(accountNum, accountDetails)) {
                        cout << "Account verified successfully. You can now access your account." << endl;
                        usbacc = new user(accountDetails);
                        return true;
                    } else {
                        cout << "Account not found." << endl;
                        return false;
                    }
                }
            }
        }
    }
    
    cout << "No USB drive with BankAccounts.txt found." << endl;
    return false; 
}

void interact::updateOriginalList() {
    user* current = head;

    while (current != nullptr) {
        if (current->data.accountNumber == usbacc->data.accountNumber) {
            current->data = usbacc->data;
            cout << "Original list updated with the account details from usbacc." << endl;
            return;
        }
        current = current->next;
    }

    cout << "Account not found in the original list." << endl;
}

string interact::getpincode() {
    string pin;
    char ch;

    cout << "Enter Pin: ";
    while ((ch = getch()) != '\r') {
        if (ch >= '0' && ch <= '9') {
            pin += ch;
            cout << "*";
        }
        else if (ch == '\b') {
            if (!pin.empty()) {
                cout << "\b \b";
                pin.pop_back();
            }
        }
    }
    return pin;
}

string interact::encrypt(string pin) {
    int i, j;
    j = pin.size();
    for (i = 0; i < j; i++) {
        pin[i] = pin[i] + 100;
    }
    return pin;
}

string interact::decrypt(string pin) {
    int i, j;
    j = pin.size();
    for (i = 0; i<j; i++) {
        pin[i] = pin[i] - 100;
    }
    return pin;
}

bool interact::isFlashDriveInserted() {
	DWORD driveMask = GetLogicalDrives();
	for (char driveLetter = 'A'; driveLetter <= 'Z'; ++driveLetter) {
		if (driveMask & (1 << (driveLetter - 'A'))) {
			string drivePath = string(1, driveLetter) + ":\\";
			UINT driveType = GetDriveTypeA(drivePath.c_str());

			if (driveType == DRIVE_REMOVABLE) {
				return true;
			}
		}
	}
	return false;
}

#endif