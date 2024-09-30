    #include <iostream>
    #include <fstream>
    #include <time.h>
    #include <string>
    #include <windows.h>
    //#include <filesystem>
    using namespace std;

        Bank::Bank() : head(NULL) {}

        //main
        int main()
        {
            Bank data;
            //USB SCANNER
                data.retrieve();  
                int pin;char respo;
                details* locator = data->retrieveusb();
                int numero = locator->pin;
                int opera = data.menu();
                system("cls");
                switch(opera){
                    case 1: 
                        if(data.accverify(numero))
                        {
                            cout<<"Input your 4 DIGIT PIN: ";cin>>pin;
                                if(pin == numero){
                                    cout<<"Logged in"<<endl;
                                    system("pause");
                                    data.transaction(data.>etrieveusb());
                                    break;
                                }else{cout<<"Wrong PIN!"<<endl;system("pause");break;}
                        }else{
                                cout<<"No Existing Account\n"<<endl;
                                cout<<"Do you want to create a new account instead?(Initial Deposit is Min. 5000.)(Y/N): ";cin>>respo;
                                if(respo == 'Y'||respo=='y'){
                                    data.regacc();
                                    data.save();
                                    break;
                                }else{cout<<"exited account creation"<<endl;system("pause");break; }
                            break;
                        } 
                    case 2:
                        data.save();
                        cout<<"Program Exited"<<endl;
                        system("pause");
                        return 0;
                        break;
                }
            }

        //Menu Prompt
        int Bank::menu(){
            int oper;
            cout<<"1.) TRANSACTIONS\n";
            cout<<"2.) Exit\n";
            cout<<" SELECT : ";
            cin>>oper;

            return oper;
        }

        //Address Locator
        users* Bank::locateaddress(int accountnumb){
            users *p = head;
            while (p != NULL){
                if (p->accounts.accountnum == accountnumb){
                    return p; 
                }
                p = p->next;  
            }
            return NULL;  
        }


        int depochecker(int depp){
            if(depp < 5000){
                cout<<"INITIAL DEPO SHOULD BE >= 5000: ";
                cin>>depp;
                return depochecker(depp);
            } 
            return depp;
        }


        void Bank::regacc(){ 
            details x;
            string newname;
            long newbalance;
            int newpin;long long int newcontact;int newaccountnum;int depo;
            cout<<"INPUT YOUR NAME: "<<endl;
            cin>>newname;
            cout<<"Deposit Initial Balance(Min 5000): ";
            cin>>depo;
            newbalance = depo;
            if(depo<5000){
                newbalance = depochecker(depo);
            }
            cout<<"Please input your 4 DIGIT PIN: ";
            cin>>newpin;
            newpin == pincreate(newpin);
            cout<<"Please input your contact number: ";
            cin>>newcontact;
            newaccountnum = randomizer();
            cout<<" YOUR ACCOUNT NUMBER IS: "<<newaccountnum<<endl; 
            system("pause");
            system("cls");
            x.name = newname;
            x.balance = newbalance;
            x.pin = newpin;
            x.contact = newcontact;
            x.accountnum = newaccountnum;
            AddAcc(x);
            cout<<" ACCOUNT SUCCESSFULLY CREATED"<<endl;
            system("pause");
            cout<<" Please insert USB to save the account"<<endl;
            cout<<"Do you want to save account in your usb? "<<endl;
            cout<<"(1)YES, (2)NO"<<endl;
            int usbrespo;
            cin>>usbrespo;
            switch(usbrespo){
                case 1:
                    while(!isFlashDriveInserted()){ 
                        cout<< "No flash drive detected, Please insert Flash Drive!" << endl;
                    Sleep(1000);
                    }
                    if(isFlashDriveInserted()){
                    cout << "Flash drive is inserted." << endl;
                    Sleep(1000);saveusb(x);break;
                    }
                
                case 2:
                    cout<<"Program Exited"<<endl;
                    break;
                    return;
                default: cout<<"INVALID INPUT"<<endl;system("pause");break;
            }
        }

        int Bank::randomizer() {
            srand(time(0));
            int randomizednum = rand() % 999999 + 100000;
            while (accverify(randomizednum)) {  
                randomizednum = rand() % 999999 + 100000;
            }
            return randomizednum;
        }


        details Bank::locate(int accountnumver){
            users *p = head;
            while (p != NULL) {
                if (p->accounts.accountnum == accountnumver) {
                    return p->accounts;
                }
                p = p->next;
            }
            return p->accounts;

        }

        int Bank::pincreate(int pin){
            if(pin<1000||pin>9999){
                cout<<"PIN SHOULD BE EXACTLY 4 DIGITS(cannot start with 0): "<<endl;
                cout<<" ENTER NEW PIN AGAIN: ";
                cin>>pin;
                return pincreate(pin);
            }
            return pin;
        }

        int Bank::changepin(int curr){
            int newpin;
            system("cls");
            cout<<"INPUT NEW 4 DIGIT PIN: "<<endl;
            cin>>newpin;
            if(curr==newpin){
                cout<<"NEW PIN MUST NOT BE SAME AS THE OLD PIN"<<endl;
                return (changepin(newpin));
            }
            else if(newpin<1000||newpin>9999){
                cout<<" PIN MUST ONLY BE 4 DIGIT LONG"<<endl;
                return (changepin(newpin));
            }
            return newpin;
        }


        int Bank::transaction(details* x){
            int withdraw;int deposit;int accuser;int transfer;char pin;int newpin;users* TargetTransfer;int ope;users* useracc;
            while(bool lock = true){   
        
            cout<<"1.) Balance Inquiry\n";
            cout<<"2.) Withdraw\n";
            cout<<"3.) Dep  osit\n";
            cout<<"4.) Fund Transfer\n";
            cout<<"5.) Change PIN Code\n";
            cout<<"6.) Other Transactions\n";
            cout<<"7.) Exit\n";
            cout<<" SELECT: "<<endl;
            cin>>ope;
            system("cls");
            
            switch(ope)
                {
                    case 1: 
                        cout<<" USERNAME: "<<x->name<<"\n";
                        cout<<" ACCOUNT NUMBER: "<<x->accountnum<<"\n\n";
                        cout<<" ACCOUNT REMAINING BALANCE: "<<x->balance<<"\n";
                        system("pause");break;
                    case 2:
                        cout<<" USERNAME: "<<x->name<<"\n";
                        cout<<" ACCOUNT NUMBER: "<<x->accountnum<<"\n\n";
                        cout<<" ACCOUNT REMAINING BALANCE: "<<x->balance<<"\n";
                        cout<<" INPUT AMOUNT TO WITHDRAW: ";
                        cin>>withdraw;
                        if(withdraw > x->balance){
                        cout << "INSUFFICIENT FUNDS!" << endl;
                        }else{
                        x->balance -= withdraw;
                        cout << "WITHDRAWAL SUCCESFUL, NEW BALANCE: " << x->balance << endl;
                        }system("pause");break;
                    case 3: 
                        cout<<" USERNAME: "<<x->name<<"\n";
                        cout<<" ACCOUNT NUMBER: "<<x->accountnum<<"\n\n";
                        cout<<" INPUT AMOUNT TO DEPOSIT: "<<x->balance<<"\n";
                        cin>>deposit;
                        x->balance += deposit;
                        cout << "DEPOSIT SUCCEFUL, NEW BALANCE: " << x->balance << endl;
                        system("pause");break;
                    case 4:
                        cout<<" USERNAME: "<<x->name<<"\n";
                        cout<<" ACCOUNT NUMBER: "<<x->accountnum<<"\n\n";
                        cout<<" TRANSFER TO ACCOUNT(ACCOUNT NUMBER): ";
                        cin>>accuser;
                        cout<<" HOW MUCH AMOUNT TO TRANSFER: ";
                        cin>>transfer;
                        if(accverify(accuser)){
                        TargetTransfer=locateaddress(accuser);
                        x->balance-=transfer;                                                
                        ftransfer(TargetTransfer,transfer);
                        cout<<"Successfully Transfered Funds"<<endl;
                        }
                        else{
                        cout<<"Account not found";
                        }
        
                        system("pause");break;
                    case 5:
                        cout<<" USERNAME: "<<x->name<<"\n";
                        cout<<" ACCOUNT NUMBER: "<<x->accountnum<<"\n\n";
                        cout<<" CURRENT PIN: \n"<<x->pin<<"\n"<<endl;
                        cout<<" CHANGE PIN?(y/n): ";
                        cin>>pin;
                        if(pin == 'y'||pin =='Y'){
                            newpin = changepin(x->pin);
                            x->pin = newpin;
                            cout<<"PIN SUCCESSFULLY CHANGED"<<endl;
                        }system("pause");break;
                    /*case 6:
                        cout<<" USERNAME: "<<x.name<<"\n";
                        cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                        cout<<" Exi
                        system("pause");break;
                        */
                    case 7:
                        useracc = locateaddress(x->accountnum);
                        useracc->accounts.accountnum = x->accountnum;
                        useracc->accounts.name = x->name;
                        useracc->accounts.balance = x->balance;
                        useracc->accounts.contact = x->contact;
                        useracc->accounts.pin = x->pin;
                        cout<<"Logging out\n"<<endl;
                        system("pause");
                        save();
                        lock = false;
                        return 0;
                        break;
                }
        }
        }



        void Bank::ftransfer(users* target,int amount){
            target->accounts.balance += amount;
        }


        bool Bank::accverify(int accountnum)
        {
            users *p;
            p = head;
            while(p!=NULL){
                if(p->accounts.accountnum==accountnum){
                    return true;
                }
                    p=p->next;
            }
            return false;
        };

        //neagaa


        void Bank::AddAcc(details x) {    
            users *newNode = new users(x);
            if(head == NULL) {
                head = newNode;
            }else{
                users *p = head;
                while (p->next != NULL) {
                    p=p->next;
                }
                p->next=newNode;
            }
        }


        void Bank::deactivate(long accountnum){
            users *p, *q;
            p = q = head;

            while (p!=NULL && accountnum!=p->accounts.accountnum) {
                q=p;
                p=p->next;
            }

            if (p==NULL) {
                cout<<"User Not Found.\n";
                system("pause");
            }
            else {
                if (p==head) {
                    head = p->next;
                }
                else {
                    q->next = p->next;
                }
                delete(p);
                cout<<"Account Deleted."<<endl;
                system("pause");
            }
        }


      void Bank::save(){
        ofstream myFile("BankAccounts.txt"); // gawin nateng ifstream later
        if (!myFile){
            cout <<"Please insert your ATM Card.\n";
            system("pause");
        }
        else {
            users *p = head;
                myFile<<"account name"<<" "<<"account num"<<" "<<"account balance"<<" "<<"contact number"<<" "<<" pin"<<endl;
            while (p != NULL) {
                myFile<<p->accounts.name<<" "<<p->accounts.accountnum<<" "<<p->accounts.balance<<" "<<p->accounts.contact<<" "<<p->accounts.pin<<endl;
                // file view =  user accountnum balance contact pin
                p = p->next;
            }
        myFile.close();
        }
    }

        
    void Bank::saveusb(details useracc) {
            char driveLetter = 0;
            DWORD drives = GetLogicalDrives();
            
            // Find the USB drive (removable)
            for (char drive = 'A'; drive <= 'Z'; ++drive) {
                if (drives & (1 << (drive - 'A'))) { // Check if drive exists
                    string drivePath = string(1, drive) + ":\\"; // Drive path
                    UINT driveType = GetDriveTypeA(drivePath.c_str());
                    
                    if (driveType == DRIVE_REMOVABLE) { // Check if the drive is removable
                        driveLetter = drive; // Store the drive letter
                        cout << "Removable drive detected at " << drivePath << endl;
                        break;
                    }
                }
            }
            // If no removable drive found
            if (driveLetter == 0) {
                cout << "No removable USB drive detected." << endl;
                return;
            }
            string filename = "MyAccountsUSB.txt";
            // Form the full path to save on the USB drive
            string filePath = string(1, driveLetter) + ":\\" + filename;

            // Open the file in append mode to create or update the file
            ofstream myFile(filePath, ios::app);
            if (!myFile) {
                cout << "Error opening file on USB drive.\n";
                return;
            }

            // Write account details to the file
            myFile << "account name" << " " << "account num" << "pin" << endl;
            myFile << useracc.name << " " << useracc.accountnum<<" "<< useracc.pin << endl;

            myFile.close();
            cout << "Account saved successfully to " << filePath << endl;
        }

    
       details Bank::retrieveusb() {
                char driveLetter = 0;
                DWORD drives = GetLogicalDrives();

                // Find the USB drive (removable)
                for (char drive = 'A'; drive <= 'Z'; ++drive) {
                    if (drives & (1 << (drive - 'A'))) { // Check if drive exists
                        string drivePath = string(1, drive) + ":\\"; // Drive path
                        UINT driveType = GetDriveTypeA(drivePath.c_str());

                        if (driveType == DRIVE_REMOVABLE) { // Check if the drive is removable
                            driveLetter = drive; // Store the drive letter
                            cout << "Removable drive detected at " << drivePath << endl;
                            break;
                        }
                    }
                }

                // If no removable drive found
                if (driveLetter == 0) {
                    cout << "No removable USB drive detected." << endl;
                    return {}; // Return empty details struct if no USB found
                }

                string filename = "MyAccountsUSB.txt";
                string filePath = string(1, driveLetter) + ":\\" + filename;

                ifstream myFile(filePath);
                if (!myFile) {
                    cout << "Error opening file on USB drive: " << filePath << endl;
                    return {}; // Return empty details struct if file could not be opened
                }

                // Read the account data from the file
                details p;
                string header;
                getline(myFile, header); // Read the header line and discard it

                if (myFile >> p.name >> p.accountnum >> p.pin) {
                    myFile.close();
                    cout << "Account found"<<endl;
                    return p;
                } else {
                    cout << "No accounts found in the USB file." << endl;
                    myFile.close();
                    return {}; // Return empty details struct if no accounts were found
                }
            }


    void Bank::retrieve() {
        details p;
        ifstream myFile("BankAccounts.txt");
        if (!myFile) {
            cout << "File Error.\n";
            return; // Early return to avoid proceeding with null file
        } else {
            // Skip the header row
            string header;
            getline(myFile, header); // Read and discard the header line

            while (myFile >> p.name >> p.accountnum >> p.balance >> p.contact >> p.pin) {
                AddAcc(p); // Add account details to the linked list
            }
            myFile.close();
        }
    }
    bool Bank::isFlashDriveInserted() {
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