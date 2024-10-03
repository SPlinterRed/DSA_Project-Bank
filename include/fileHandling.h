#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <iostream>
// #include <filesystem>
#include <windows.h>
#include "myStruct.h"
#include <fstream>
#include "bankinteract.h"
#include <fstream>

using namespace std;

interact bank;
class filehandle{
    public: 
    bool isFlashDriveInserted();
    bool accverify(string accountnum);
    void saveLocal();
    void retrievelocal();
    bool isFlashDriveInserted();
};

    bool filehandle::isFlashDriveInserted(){
        DWORD drives = GetLogicalDrives();
        
        for (char drive = 'A'; drive <= 'Z'; ++drive) {
            if (drives & (1 << (drive - 'A'))) { // Check if drive exists
                string drivePath = string(1, drive) + ":\\";
                UINT driveType = GetDriveTypeA(drivePath.c_str());
                
                if (driveType == DRIVE_REMOVABLE) { // Check if the drive is removable
                    cout << "Removable drive detected at " << drivePath << endl;
                    return true;
                }
            }
        }
        
        // No removable drives found
        return false;
    }

    void filehandle::saveLocal(){
    ofstream myFile("BankAccounts.txt");
    if(!myFile){
        cout <<"File Error"<< endl;
        return;
    }
    user* p = bank.head;
    myFile <<"AccountName AccountNumber Balance Pin"<< endl;
    while(p != NULL){
        myFile<<p->data.accountName<<" "<<p->data.accountNumber<<" "<<p->data.balance<<" "<<p->data.accountPin<<endl;
        p = p->next;
    }
    myFile.close();
    cout<<"Data saved T_T"<< endl;
}

    void filehandle::retrievelocal(){
        accountNode p;
        ifstream myFile("BankAccounts.txt");
        if (!myFile){
            cout<<"File Error.\n";
            return;
        }
        string header;
        getline(myFile, header);

        while(myFile>>p.accountName>>p.accountNumber>>p.balance>>p.accountPin) {
        //cout <<"Read account " << p.accountName << ", " << p.accountNumber << ", " << p.balance << ", " << p.accountPin << endl; // Debugging line
            bank.AddAcc(p);
        }
        
        myFile.close();
        cout<<"Data retrieved successfully!"<< endl;
    }

bool filehandle::accverify(string accountnum){
    user* x = bank.head;
    while(x!=NULL){
        if(x->data.accountNumber == accountnum){
            return true;
        }
            x = x->next;
    }   
    return false;
}



#endif


