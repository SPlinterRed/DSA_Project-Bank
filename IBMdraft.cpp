    #include <iostream>
    #include <fstream>
    #include <time.h>
    #include <string>
    //#include <filesystem>
    using namespace std;


//HELLO


    struct details{
        string name;
        long int balance;
        int pin;
        long long int contact;
        int accountnum;
        //birthdate( isipin muna ung dropdown sa ui )( prompt na natatanong ng month day year tas print plus strings sa save?) (array?)
    };

    struct users{
        details accounts;
        users *next;
        users(details x) : accounts(x), next(NULL) {}
    };
    class Bank{
    private:
        users *head;
    public:
        Bank() : head(NULL) {}
        void regacc();//register new users
        void AddAcc(details x);
        int transaction(details x);
        void deactivate(long accountnumber);
        void save();
        void retrieve();
        bool accverify(int accountnum);
        void ftransfer(users* target, int amount);
        details locate(int accountnumver);
        int randomizer();
        int menu();
        users* locateaddress(int accountnum);
        int changepin(int curr);
        int pincreate(int pin);
        //bool fileExists();

    };
        //void displaytransactionmenu(); 
        //temporary since wla pang ui
        //void gui(); ui natin siguro // int encryption();
        //int loginpage();



    int main()
    {
        Bank data;
        //if(data.fileExists()){
        data.retrieve();  
            int numero;
            int pin;
            char respo;
            details locator;
            int opera = data.menu();
            system("cls");
            switch(opera){
                case 1: 
                    cout<<"Please input your account number: ";
                    cin>>numero;
                    if(data.accverify(numero)){
                        locator = data.locate(numero);
                        cout<<"Input your 4 DIGIT PIN: ";
                        cin>>pin;
                            if(pin == locator.pin){
                                cout<<"Logged in"<<endl;
                                system("pause");
                                data.transaction(locator);
                                break;
                            }else{
                                cout<<"Wrong PIN!"<<endl;
                                system("pause");
                                break;
                            }
                    }else{
                            cout<<"Account does not exist\n"<<endl;
                            cout<<"Do you want to create a new account instead?(Initial Deposit is Min. 5000.)(Y/N): ";
                            cin>>respo;
                            if(respo == 'Y'||respo=='y'){
                                data.regacc();
                                break;
                            }else{
                            cout<<"exited account creation"<<endl;
                            system("pause");
                            break;
                            }
                        break;
                
                case 2:
                    data.save();
                    cout<<"Program Exited, please remove flash drive"<<endl;
                    system("pause");
                    return 0;
                    break;
                }//switch case bracket toh
            //}//while 1 braccket
    }//main bracket
}



    int Bank::menu(){
        int oper;
        cout<<"1.) LOGIN/REGISTER\n";
        cout<<"2.) Exit\n";
        cout<<" SELECT : ";
        cin>>oper;
        return oper;
    }


    users* Bank::locateaddress(int accountnumb) {
        users *p = head;  // Start from the head of the list
        while (p != NULL) {
            if (p->accounts.accountnum == accountnumb) {
                return p;  // Return the pointer to the matching user
            }
            p = p->next;  // Move to the next node
        }
        return NULL;  // Return NULL if no match is found
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


    int Bank::transaction(details x){
        int withdraw;int deposit;int accuser;int transfer;char pin;int newpin;users* TargetTransfer;int ope;users* useracc;
        while(bool lock = true){   
    
        cout<<"1.) Balance Inquiry\n";
        cout<<"2.) Withdraw\n";
        cout<<"3.) Deposit\n";
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
                    cout<<" USERNAME: "<<x.name<<"\n";
                    cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                    cout<<" ACCOUNT REMAINING BALANCE: "<<x.balance<<"\n";
                    system("pause");break;
                case 2:
                    cout<<" USERNAME: "<<x.name<<"\n";
                    cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                    cout<<" ACCOUNT REMAINING BALANCE: "<<x.balance<<"\n";
                    cout<<" INPUT AMOUNT TO WITHDRAW: ";
                    cin>>withdraw;
                    if(withdraw > x.balance){
                    cout << "INSUFFICIENT FUNDS!" << endl;
                    }else{
                    x.balance -= withdraw;
                    cout << "WITHDRAWAL SUCCESFUL, NEW BALANCE: " << x.balance << endl;
                    }system("pause");break;
                case 3: 
                    cout<<" USERNAME: "<<x.name<<"\n";
                    cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                    cout<<" INPUT AMOUNT TO DEPOSIT: "<<x.balance<<"\n";
                    cin>>deposit;
                    x.balance += deposit;
                    cout << "DEPOSIT SUCCEFUL, NEW BALANCE: " << x.balance << endl;
                    system("pause");break;
                case 4:
                    cout<<" USERNAME: "<<x.name<<"\n";
                    cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                    cout<<" TRANSFER TO ACCOUNT(ACCOUNT NUMBER): ";
                    cin>>accuser;
                    cout<<" HOW MUCH AMOUNT TO TRANSFER: ";
                    cin>>transfer;
                    if(accverify(accuser)){
                    TargetTransfer=locateaddress(accuser);
                    x.balance-=transfer;                                                
                    ftransfer(TargetTransfer,transfer);
                    cout<<"Successfully Transfered Funds"<<endl;
                    }
                    else{
                    cout<<"Account not found";
                    }
    // pasa dito struct ng current user, target user, amount// hanapin sa linklisst ung papasahan ng pera kunin details nya
                    system("pause");break;
                case 5:
                    cout<<" USERNAME: "<<x.name<<"\n";
                    cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                    cout<<" CURRENT PIN: \n"<<x.pin<<"\n"<<endl;
                    cout<<" CHANGE PIN?(y/n): ";
                    cin>>pin;
                    if(pin == 'y'||pin =='Y'){
                        newpin = changepin(x.pin);
                        x.pin = newpin;
                        cout<<"PIN SUCCESSFULLY CHANGED"<<endl;
                    }system("pause");break;
                /*case 6:
                    cout<<" USERNAME: "<<x.name<<"\n";
                    cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                    cout<<" Exi
                    system("pause");break;
                    */
                case 7:
                    useracc = locateaddress(x.accountnum);
                    useracc->accounts.accountnum = x.accountnum;
                    useracc->accounts.name = x.name;
                    useracc->accounts.balance = x.balance;
                    useracc->accounts.contact = x.contact;
                    useracc->accounts.pin = x.pin;
                    cout<<"Logging out\n"<<endl;
                    system("pause");
                    lock = false;
                    return 0;
                    break;
                default: cout<<"invalid input";break;
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

    /*bool Bank::fileExists() {
        ifstream file("BankAccounts.txt"); // Try to open the file
        return file.good(); // Check if the file stream is in a good state
    }*/

