#include <iostream>
#include <fstream>
using namespace std;

struct details{
    string name;
    double balance;
    int pin;
    //birthdate( isipin muna ung dropdown sa ui )( prompt na natatanong ng month day year tas print plus strings sa save?) (array?)
    long contact;
    long accountnum;
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
    void Register(details x);
    void transaction(details x);
    void deactivate(long accountnumber);
    //void displaytransactionmenu(); //temporary since wla pang ui
    //void gui(); ui natin siguro
    void save();
    void retrieve();
   // int encryption();
    int loginpage();
    bool accverify(long accountnum);
    void ftransfer(details x,details target,int amount);
    details locate(string name);
};

void main()
{
    int oper;
    cout<<"1.) LOGIN\n";
    cout<<"2.) REGISTER\n";
    cout<<" SELECT : ";
    cin>>oper;
}

int loginpage(){
    cout<<"1.) LOGIN\n";
    cout<<"2.) REGISTER\n"
}

void Bank::transaction(details x){
 while(bool lock = true){   
    int ope;
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
int withdraw;int deposit;string accuser;int transfer;char pin;int newpin;details TargetTransfer;
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
                cin>>withdraw;cout<<"withdrawn: "<<withdraw<<endl;
                system("pause");break;
            case 3: 
                cout<<" USERNAME: "<<x.name<<"\n";
                cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                cout<<" INPUT AMOUNT TO DEPOSIT: "<<x.balance<<"\n";
                cin>>deposit;cout<<"deposited: "<<deposit<<endl;
                system("pause");break;
            case 4:
                cout<<" USERNAME: "<<x.name<<"\n";
                cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                cout<<" TRANSFER TO ACCOUNT: ";
                cin>>accuser;
                cout<<" HOW MUCH AMOUNT TO TRANSFER: ";
                cin>>transfer;
                TargetTransfer = locate(accuser);// hanapin sa linklisst ung papasahan ng pera kunin details nya
                ftransfer(x,TargetTransfer,transfer); // pasa dito struct ng current user, target user, amount
                system("pause");break;
            case 5:
                cout<<" USERNAME: "<<x.name<<"\n";
                cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                cout<<" CURRENT PIN: ****\n";
                cout<<" CHANGE PIN?(y/n): ";
                cin>>pin;
                if(pin=='Y'||pin=='y'){
                    cout<<"Input new pin: \n";
                    cin>>newpin;
                }
                else{
                    cout<<"You decided not to change your pin."<<endl;system("pause");
                }
                break;
                system("pause");break;
            /*case 6:
                cout<<" USERNAME: "<<x.name<<"\n";
                cout<<" ACCOUNT NUMBER: "<<x.accountnum<<"\n\n";
                cout<<" Exi
                system("pause");break;
                */
            case 7:
                cout<<"Logging out"<<endl;
                system("pause");
                lock = false;
                break;
        }
}
}

void Bank::ftransfer(details x,details target,int amount){
    x.balance = x.balance - amount;
    target.balance = target.balance + amount;
}


bool Bank::accverify(long accountnum)
{
    users *p;
    p = head;
    while(p!=NULL){
        if(p->accounts.accountnum==accountnum){
            return true;
        }
        else
        {
            p=p->next;
        }
    }
    return false;
};


int menu() {
    int op;
    system("cls");
    cout<<"Menu\n";
    cout<<"1.) LOGIN\n";
    cout<<"2.) OPEN A NEW BANK ACCOUNT\n";
    cout<<"3.) Exit\n";
    cout<<"Select: ";
    cin>>op;
    return op;
};

//boo.


void Bank::Register(details x){    
    users *p, *q, *newNode;
    p = q = head;
    newNode = new users(x);

    while (p!=NULL) {
        q = p;
        p = p->next;
        }

    if (p == head) {
        head = newNode;
    }
    else {
        q->next = new users(x);
        newNode->next = p;
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

/*void users::display(){
    Node *p;
    p = head;
    float ave;
    int i = 1;

    system("cls");
    cout << "Student Record\n";
    cout << "   \tStudent\tQuiz 1\tQuiz 2\tQuiz 3\tAverage\tRemarks\n";
    while (p!=NULL) {
    ave = (p->data.q1 + p->data.q2 + p->data.q3) / 3.0;
    cout <<i++<<".)"<<"\t"<<p->data.name<<"\t"<<p->data.q1<<"\t"<<p->data.q2<<"\t"<<p->data.q3<<"\t"<<ave<<"\t"<<(ave>=75.0? "PASSED":"FAILED")<<"\n";
    p = p->next;
    }
    system("pause");
}*/


void Bank::save(){
    ofstream myFile("BankAccounts.txt"); // gawin nateng ifstream later
    if (!myFile){
        cout <<"Please insert your ATM Card.\n";
        system("pause");
    }
    else {
        users *p = head;
        while (p != NULL) {
            myFile<<p->accounts.name<<" "<<p->accounts.accountnum<<" "<<p->accounts.balance<<" "<<p->accounts.contact<<" "<<p->accounts.accountnum<<endl;
            // file view =  user accountnum balance contact pin
            p = p->next;
        }
     myFile.close();
     }
}

void Bank::retrieve(){
    details p;
    ifstream myFile("BankAccounts.txt");
    if (!myFile){
        cout <<"File Error.\n";
        system("pause");
    }
    else {
        while (myFile >>p.name>>p.accountnum>>p.balance>>p.contact>>p.pin){
            myFile.ignore();
            Register(p);
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