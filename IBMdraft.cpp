#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

struct details{
    string name;
    int balance;
    int pin;
    long contact;
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
    //void displaytransactionmenu(); //temporary since wla pang ui
    //void gui(); ui natin siguro
    void save();
    void retrieve();
   // int encryption();
    // int loginpage();
    bool accverify(int accountnum);
    void ftransfer(details x,details target,int amount);
    details locate(int accountnumver);
    int randomizer();
    int menu();
};

int Bank::menu(){
    int oper;
    cout<<"1.) LOGIN/REGISTER\n";
    cout<<"2.) Exit\n";
    cout<<" SELECT : ";
    cin>>oper;
    return oper;
}

int main()
{
    Bank data;
    data.retrieve();  
    while(1){
    int numero;
    char respo;
    details locator;
    int opera = data.menu();
    system("cls");
    switch(opera)
    {
        case 1: 
            cout<<"Please input your account number: ";
            cin>>numero;
            if(data.accverify(numero)){
                locator = data.locate(numero);
                data.transaction(locator);
                break;
            }
            else{
                cout<<"Account does not exist\n"<<endl;
                cout<<"Do you want to create a new account instead?(Initial Deposit is Min. 5000.)(Y/N): ";
                cin>>respo;
                if(respo == 'Y'||respo=='y'){
                    data.regacc();
                    break;
                }else{
                    cout<<"exited account creation"<<endl;
                    system("pause");
                }break;
            }
        case 2:
            data.save();
            cout<<"Program Exited, please remove flash drive"<<endl;
            system("pause");
            return 0;
    }
}
}


void Bank::regacc(){ 
    details x;
    string newname;int newbalance;int newpin;long newcontact;int newaccountnum;
    cout<<"INPUT YOUR NAME: "<<endl;
    cin>>newname;
    cout<<"Deposit Initial Balance(Min 5000): ";
    cin>>newbalance;
    cout<<"Please input your 4 DIGIT PIN: ";
    cin>>newpin;
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
    return details();

}

int loginpage(){// LOGIN PAGE NIG

}

int Bank::transaction(details x){
    int withdraw;int deposit;int accuser;int transfer;char pin;int newpin;details TargetTransfer;int ope;
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
                TargetTransfer = locate(accuser);// hanapin sa linklisst ung papasahan ng pera kunin details nya
                ftransfer(x,TargetTransfer,transfer); // pasa dito struct ng current user, target user, amount
                system("pause");break;
            case 5:
                cout<<" USERNAME: "<<x.name<<"\n";
                cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                cout<<" CURRENT PIN: \n"<<x.pin<<"\n"<<endl;
                cout<<" CHANGE PIN?(y/n): ";
                cin>>pin;
                if(pin=='Y'||pin=='y'){
                    cout<<"Input new pin: \n";
                    cin>>newpin;
                    x.pin = newpin;
                }
                else{
                    cout<<"You decided not to change your pin."<<endl;system("pause");
                }
                system("pause");break;
            /*case 6:
                cout<<" USERNAME: "<<x.name<<"\n";
                cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                cout<<" Exi
                system("pause");break;
                */
            case 7:
                cout<<"Logging out\n"<<endl;
                system("pause");
                save();
                lock = false;
                return 0;
                break;
            default: cout<<"invalid input";break;
        }
}
}

void Bank::ftransfer(details x,details target,int amount){
    x.balance -= amount;
    target.balance += amount;
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
            myFile<<p->accounts.name<<" "<<p->accounts.accountnum<<" "<<p->accounts.balance<<" "<<p->accounts.contact<<" "<<p->accounts.accountnum<<endl;
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


/*
int main(){
    users grades;
    Rec x;
    grades.retrieve();

    while(true) {
        switch(menu()){
        case 1 :
            system("cls");cout<<"Input Name: "; cin>>x.name;
            cout<<"Input Quiz 1: "; cin>>x.q1;
            cout<<"Input Quiz 2: "; cin>>x.q2;
            cout<<"Input Quiz 3: "; cin>>x.q3;
            grades.add(x);
            grades.save();
            break;
        case 2 :
            system("cls");
            cout <<"Input Name: "; cin>>x.name;
            grades.del(x.name);
            grades.save();
            break;
        case 3 :
            grades.display();
            break;
        case 4 :
            grades.save();
            exit(0);
        default:
            cout<<"Invalid Input.\n";
            system("pause");
        }
    }
}
int main()
{
    Bank data;
    system("cls");
    data.retrieve();
    switch(menu()){
        case 1:
    }   
}
*/