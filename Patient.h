#pragma once
#include <iomanip>
#include "User.h"
#include "Time.h"
#include "HelpingFunc.h"
#include "Oladoc.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Availability.h"
class Patient:public User{
protected:
    Appointment AppFetch;
    Charges ChargesFetch;
    Availabilty AvailabilityFetch;
    Time Clock;
    Payment_Gateway *Payment;
    char Username[100];
    char Password[100];
    char CNIC[100];
    char Email[100];
    int Balance;
public:
    int menu();
    bool login(string filename);
    bool Register();
    int edit_info();
    void reset_password();
    int search_doctors();
    int add_appointments();
    void view_appointments(string Patient_CNIC);
    int deposit_balance();
    int Appointment_refund(Appointment X);
    bool UserCheck(string username);
    bool CNICCheck(string cnic);
    bool MailCheck(string email);
    void Add(string name);
    void logout();
    void operator = (const Patient& obj);
    bool UserCheckApt(string cnic) {
        Appointment Temp;
        ifstream Obj("appointment_data.dat",ios::binary);
        while (Obj.read((char*)&Temp, sizeof(Temp))) {
            if (stringCmp(Temp.getpcnic(),cnic)){
                Obj.close();
                return 1;}
        }
        return 0;
    }
    const char* getuser()const {
        return Username;
    }
    const char* getcnic()const{
        return CNIC;
    }
    const char* getmail()const {
        return Email;
    }
    const char* getpass()const{
        return Password;
    }
    const int getBalance()const{
        return Balance;
    }
};

bool Patient::UserCheck(string username) {
    Patient Temp;
    ifstream Obj("patient_data.dat",ios::binary);
    while (Obj.read((char*)&Temp, sizeof(Temp))) {
        if (stringCmp(Temp.getuser(),username))
            return 1;
    }
    return 0;
}
bool Patient::CNICCheck(string cnic) {
    Patient Temp;
    ifstream Obj("patient_data.dat",ios::binary);
    while (Obj.read((char*)&Temp, sizeof(Temp))) {
        if (stringCmp(Temp.getcnic(),(const char*)&cnic))
            return 1;
    }
    return 0;
}
ostream& operator << (ostream& out, const Patient& obj)
{
    out <<"Name : "<<obj.getuser() << endl;
    out <<"Email: "<<obj.getmail() << endl;
    out <<"Pass : "<< obj.getpass() << endl;
    out <<"CNIC : "<<obj.getcnic() << endl;
    out <<"Balance : "<< obj.getBalance() << endl;

    return out;
}
bool Patient::MailCheck(string email) {
    Patient Temp;
    ifstream Obj("patient_data.dat",ios::binary);
    while (Obj.read((char*)&Temp, sizeof(Temp))) {
        if (!strcmp(Temp.getmail(),(const char*)&email))
            return 1;
    }
    return 0;
}


void Patient::Add(string fileName)
{
    ofstream obj;
    obj.open(fileName, ios::binary | ios::app);
    obj.write((char*)this, sizeof(*this));
    obj.close();
}
bool Patient::Register()
{
    char name[100], cnic[100], pass[100], mail[100];
    int checker=0;
    UserEnter:
    cout << "Please Enter a unique Username : ";
    cin>>name;
    if (UserCheck(name))
    {
        cout<<"Username is already linked with an account!\n";
        goto UserEnter;
    }

    MailEnter:
    checker = 0;
    cout << "Enter valid email please: ";
    cin>>mail;

    if (!CharCheck(mail,'@'))
    {
        cout << "Email Must have '@'\n";
        checker = 1;
    }
    if (!CharCheck(mail,'.'))
    {
        cout << "Email Must have '.'\n";
        checker = 1;
    }
    if (MailCheck(mail))
    {
        cout << "Email is already linked with an Account!\n";
        checker = 1;
    }
    if (checker==1) goto MailEnter;



    CNICEnter:
    checker = 0;
    cout << "Enter valid cnic please: ";
    cin>>cnic;
    if (OnlyNumCheck(cnic))
    {
        cout << "CNIC can only contain numbers.\n";
        checker = 1;
    }
    if (countDigit(cnic) != 13)
    {
        cout << "CNIC can only have 13 digits.\n";
        checker = 1;
    }
    if (CNICCheck(cnic))
    {
        cout << "CNIC has already been registered.\n";
        checker = 1;
    }
    if (checker==1) goto CNICEnter;


    PassEnter:
    checker = 0;
    cout << "Set password please: ";
    cin>>pass;
    if (!RangeCheck(pass, 33, 47) && !RangeCheck(pass, 58, 64) && !RangeCheck(pass, 91, 96) && !RangeCheck(pass, 123, 126))
    {
        cout << "Error! Password does not have any special characters.\n";
        checker = 1;
    }
    if (countDigit(pass) < 6)
    {
        cout << "Error! Password is under 6 characters.\n";
        checker = 1;
    }
    if (!NumCheck(pass))
    {
        cout << "Error! Password does not have any numbers.\n";
        checker = 1;
    }
    if (!RangeCheck(pass, 'A', 'Z'))
    {
        cout << "Error! Password does not have any Capital Letters\n";
        checker = 1;
    }
    if (!RangeCheck(pass, 'a', 'z'))
    {
        cout << "Error! Password does not have any Small Characters\n";
        checker = 1;
    }
    if (checker==1) goto PassEnter;


    Balance = 3500;
    strcpy(CNIC, cnic);
    strcpy(Username, name);
    strcpy(Email, mail);
    strcpy(Password, pass);

    checker = 1;

    Add("patient_data.dat");
    cout<<*this;
    cout << "REGISTERED SUCCESSFULLY!" << endl;

    return checker;
}

bool Patient::login(string fileName="patient_data.dat")
{
    char user[100], pass[100];
    cout << "Enter your Username or CNIC to Login : ";
    cin>>user;
    cout << "Enter your password : ";
    cin>>pass;
    Patient fetch;
    ifstream obj(fileName, ios::binary);
    while (obj.read((char*)&fetch, sizeof(fetch)))
    {
        if ((stringCmp(fetch.Username, user)) || (stringCmp(fetch.CNIC, user)))
        {
            cout<<"Correct User\n";
            if (stringCmp(fetch.Password, pass))
            {
                cout<<"Login Successful!";
                *this = fetch;
                return 1;
                break;
            }
        }
    }
    obj.close();
    cout<<"Login Failed!";
    return 0;
}

void Patient::operator = (const Patient& obj)
{
    Balance = obj.Balance;
    strcpy(Username, obj.Username);
    strcpy(Password, obj.Password);
    strcpy(Email, obj.Email);
    strcpy(CNIC, obj.CNIC);
}

void Patient::logout(){
    char null[100]="\0";
    strcpy(this->Username,null);
    strcpy(this->Password,null);
    strcpy(this->CNIC,null);
    strcpy(this->Email,null);
    this->Balance=0;
    cout<<"Logout Successful!\n";
}


int Patient::deposit_balance() {
    int dep;
    Patient Search;
    fstream update("patient_data.dat",ios::binary | ios::in | ios::out );

    cout<<"Welcome to Balance Deposit Portal!\n";
    cout<<"Please Select : \n\t1.Bank Transfer\n\t2.Union Pay\n\t3.PayPak\n\t4.EasyPaisa\n\t5.Go Back\nSelection : ";
    int select;
    cin>>select;
    switch(select) {
        case 1:
            Payment=new Bank_Transfer;
            dep=Payment->Charge();
            cout<<"Amount Deposited : "<<dep<<endl;
            Balance+=dep;
            while(update.read((char*)&Search,sizeof(Search))) {
                if (stringCmp(Search.CNIC,CNIC)) {
                    Search.Balance = Balance;
                    int a = update.tellg();
                    int size = sizeof(Search);
                    update.seekp(a - size);
                    update.write((char *) &Search, sizeof(Search));
                    cout<<"Balance Updated!\n";
                    break;
                }}
            break;
        case 2:
            Payment=new Union_Pay;
            dep=Payment->Charge();
            Balance+=dep;
            while(update.read((char*)&Search,sizeof(Search))) {
            if (stringCmp(Search.CNIC,CNIC)) {
                Search.Balance = Balance;
                int a = update.tellg();
                int size = sizeof(Search);
                update.seekp(a - size);
                update.write((char *) &Search, sizeof(Search));
                update.close();
                cout<<"Balance Updated!\n";
                break;
            }}
            break;
            case 3:
                Payment = new Paypak;
            dep=Payment->Charge();
            Balance += dep;
            while(update.read((char*)&Search,sizeof(Search))) {
            if (stringCmp(Search.CNIC,CNIC)) {
                Search.Balance = Balance;
                int a = update.tellg();
                int size = sizeof(Search);
                update.seekp(a - size);
                update.write((char *) &Search, sizeof(Search));
                update.close();
                cout<<"Balance Updated!\n";
                break;
            }}
                break;
                case 4:
                    Payment = new EasyPaisa;
                dep=Payment->Charge();
                Balance += dep;
            while(update.read((char*)&Search,sizeof(Search))) {
            if (stringCmp(Search.CNIC,CNIC)) {
                Search.Balance = Balance;
                int a = update.tellg();
                int size = sizeof(Search);
                update.seekp(a - size);
                update.write((char *) &Search, sizeof(Search));
                update.close();
                cout<<"Balance Updated!\n";
                break;
            }}
            break;
            case 5:
                return 0;
            break;
        }
        return 0;
    }

void Patient::reset_password() {
    cout<<"Please Enter your Old Password :";
    char pass[100];
    bool checker;
    cin>>pass;
    Patient Search;
    fstream update("patient_data.dat", ios::binary | ios::in | ios::out);
    while(update.read((char*)&Search,sizeof(Search))) {
        if (stringCmp(Search.CNIC,CNIC)) {
            if (stringCmp(Search.Password,pass)){
                cout<<"Password Verified!\n";
                PassEnter:
                checker = 0;
                cout << "Set password please: ";
                cin>>pass;
                if (!RangeCheck(pass, 33, 47) && !RangeCheck(pass, 58, 64) && !RangeCheck(pass, 91, 96) && !RangeCheck(pass, 123, 126))
                {
                    cout << "Error! Password does not have any special characters.\n";
                    checker = 1;
                }
                if (countDigit(pass) < 6)
                {
                    cout << "Error! Password is under 6 characters.\n";
                    checker = 1;
                }
                if (!NumCheck(pass))
                {
                    cout << "Error! Password does not have any numbers.\n";
                    checker = 1;
                }
                if (!RangeCheck(pass, 'A', 'Z'))
                {
                    cout << "Error! Password does not have any Capital Letters\n";
                    checker = 1;
                }
                if (!RangeCheck(pass, 'a', 'z'))
                {
                    cout << "Error! Password does not have any Small Characters\n";
                    checker = 1;
                }
                if (checker==1) goto PassEnter;

                strcpy(Search.Password,pass);
                int a = update.tellg();
                int size = sizeof(Search);
                update.seekp(a - size);
                update.write((char *) &Search, sizeof(Search));
                update.close();
                cout<<"Password Updated!\n";
                break;
            }
            else {
                cout<<"Wrong Password, Try Again!\n";
                reset_password();
            }
        }}
    update.close();
}

int Patient::edit_info() {
    fstream update("patient_data.dat", ios::binary | ios::in | ios::out);
    char temp[100];
    char pass[100];
    Patient Search;
    int a;
    int size;
    bool checker;
    cout<<"Welcome to Account Editing Portal!\nPlease select :\n\t1.Change Password\n\t2.Change Username\n\t3.Change Email\n\t4.Go Back\nSelection :";
    int select;
    cin>>select;
    switch(select){
        case 1:
            reset_password();
            break;
        case 2:
            cout<<"Please Enter your Password :";
            cin>>pass;
            while(update.read((char*)&Search,sizeof(Search))) {
                if (stringCmp(Search.CNIC,CNIC)) {
                    if (stringCmp(Search.Password,pass)){
                        cout<<"Password Verified!\n";
                        UserEnter:
                        cout << "Please Enter a unique new Username : ";
                        cin>>temp;
                        if (UserCheck(temp))
                        {
                            cout<<"Username is already linked with an account!\n";
                            goto UserEnter;
                        }
                        strcpy(Search.Username,temp);
                        a = update.tellg();
                        size = sizeof(Search);
                        update.seekp(a - size);
                        update.write((char *) &Search, sizeof(Search));
                        update.close();
                        cout<<"Username Updated!\n";
                        break;
                    }
                    else {
                        cout<<"Wrong Password, Try Again!\n";
                        reset_password();
                    }
                }}
            break;
        case 3:
            cout<<"Please Enter your Password :";
            cin>>pass;
            while(update.read((char*)&Search,sizeof(Search))) {
                if (stringCmp(Search.CNIC,CNIC)) {
                    if (stringCmp(Search.Password,pass)){
                        cout<<"Password Verified!\n";
                        MailEnter:
                        checker = 0;
                        cout << "Enter valid email please: ";
                        cin>>temp;

                        if (!CharCheck(temp,'@'))
                        {
                            cout << "Email Must have '@'\n";
                            checker = 1;
                        }
                        if (!CharCheck(temp,'.'))
                        {
                            cout << "Email Must have '.'\n";
                            checker = 1;
                        }
                        if (MailCheck(temp))
                        {
                            cout << "Email is already linked with an Account!\n";
                            checker = 1;
                        }
                        if (checker==1) goto MailEnter;

                        strcpy(Search.Email,temp);
                        a = update.tellg();
                        size = sizeof(Search);
                        update.seekp(a - size);
                        update.write((char *) &Search, sizeof(Search));
                        update.close();
                        cout<<"Email Updated!\n";
                        break;
                    }
                    else {
                        cout<<"Wrong Password, Try Again!\n";
                        reset_password();
                    }
                }}
            break;
        case 4:
            return 1;
            break;
    }
    return 1;
}
void Appointment::Add_Response(){
    bool Feedback_status;
    char Response[100];
    int Rating;
    Feedback_status=1;
    cout<<"Welcome to Feedback portal!\n";
    cout<<"Please Enter your Response : ";
    cin.ignore();
    cin.getline(Response,100);
    cout<<"Thank you for Leaving your Response!\n";
    this->Feed.setResponse(Response);
    this->Feed.setRstatus(1);
    Appointment search;
    fstream update("appointment_data.dat",ios::binary | ios::in | ios::out);
    while (update.read((char*)&search,sizeof(search))){
        if (stringCmp(search.ID,ID)){
            search.Feed.setResponse(Response);
            search.Feed.setRstatus(1);
            int a = update.tellg();
            int size = sizeof(search);
            update.seekp(a - size);
            update.write((char*)&search, sizeof(search));
            break;
        }
    }

}
void Appointment::Add_feedback(){
    bool Feedback_status;
    char Feedback[100];
    int Rating;
    char Response[100];
    Feedback_status=1;
   cout<<"Welcome to Feedback portal!\n";
    cout<<"Please Enter your Feedback : ";
    cin.ignore();
    cin.getline(Feedback,100);
    Rate:
    cout<<"Please Enter your Rating 1-5 Stars : ";
    cin>>Rating;
    if (Rating<0 && Rating>5) goto Rate;
    cout<<"Thank you for Leaving your Feedback!\n";
    this->Feed.setFeedback(Feedback);
    this->Feed.setRating(Rating);
    this->Feed.setstatus(1);
    Appointment search;
    fstream update("appointment_data.dat",ios::binary | ios::in | ios::out);
    while (update.read((char*)&search,sizeof(search))){
        if (stringCmp(search.ID,ID)){
            search.Feed.setFeedback(Feedback);
            search.Feed.setRating(Rating);
            search.Feed.setstatus(1);
            int a = update.tellg();
            int size = sizeof(search);
            update.seekp(a - size);
            update.write((char*)&search, sizeof(search));
            break;
        }
    }


}
void Patient::view_appointments(string Patient_Cnic) {
Appointment Find;
int counter=1;
cout<<"Now displaying Appointments...\n";
ifstream search("appointment_data.dat",ios::binary);
while (search.read((char*)&Find,sizeof(Find))){
    if (stringCmp(Find.getpcnic(),CNIC)) {
        cout << "Appointment # " << counter << endl;
        cout << Find << endl;
        counter++;
    }
}
search.close();
    cout<<"Would you like to Refund any Appointment (1|0)? ";
bool select;
string select2;
cin>>select;
if (select)
{
    cout<<"Enter Appointment ID # ";
    cin>>select2;
    cout<<"Processing...\n";
    cout<<"Appointment Details : \n";
    ifstream search("appointment_data.dat",ios::binary);
    while (search.read((char*)&Find,sizeof(Find))){
        if (stringCmp(Find.getID(),select2)) {
            cout << "Appointment # " << counter << endl;
            cout << Find << endl;
            counter++;
            break;
        }
    }
    search.close();
    Appointment_refund(Find);
}
    cout<<"Would you like to leave Feedback on any Appointment (1|0)? ";
    string select3;
    cin>>select;
    if (select)
    {
        cout<<"Enter Appointment ID # ";
        cin>>select2;
        cout<<"Processing...\n";
        cout<<"Appointment Details : \n";
        ifstream search("appointment_data.dat",ios::binary);
        while (search.read((char*)&Find,sizeof(Find))){
            if (stringCmp(Find.getID(),select2)) {
                cout << "Appointment # " << counter << endl;
                cout << Find << endl;
                counter++;
                break;
            }
        }
        search.close();
        Find.Add_feedback();
    }
}

    int Patient::menu() {
        cout
                << "Please Select:\n\t1.Book Appointment\n\t2.Check Balance\n\t3.Deposit Balance\n\t4.Search Doctors\n\t5.Edit Info\n\t6.View Appointments\n\t9.Logout\nSelection : ";
        int select;
        cin >> select;
        switch (select) {
            case 1:
                add_appointments();
                break;
            case 2:
                cout << "Your Current Balance is : " << this->getBalance() << endl;
                break;
            case 3:
                deposit_balance();
                break;
            case 4:
                search_doctors();
                break;
            case 5:
                edit_info();
                break;
            case 6:
                view_appointments(CNIC);
                break;
            case 9:
                logout();
                return 0;
                break;
        }
        this->menu();
    }

int Patient::Appointment_refund(Appointment X) {
        Time Check;
        Check.update_time();
        Time Compare;
        Compare=X.getTime();
        if (Check.getDay()!=Compare.getDay()){
            cout<<"Too Late for Refund, Sorry! Cant be Processed..\n";
            return 1;
        }
        if (Check.getDay()==Compare.getDay()){
            cout<<"Refund Processing...\n";
            Balance+=X.getCharge();
            Patient Search;
            fstream update("patient_data.dat",ios::binary | ios::in | ios::out);
            while(update.read((char*)&Search,sizeof(Search))) {
                if (stringCmp(Search.CNIC,CNIC)) {
                    Search.Balance = Balance;
                    int a = update.tellg();
                    int size = sizeof(Search);
                    update.seekp(a - size);
                    update.write((char *) &Search, sizeof(Search));
                    cout<<"Balance Updated!\n";
                    break;
                }}
            update.close();
            Appointment SearchApp;
            update.open("appointment_data.dat",ios::binary | ios::in | ios::out);
            while(update.read((char*)&SearchApp,sizeof(SearchApp))) {
                if (stringCmp(SearchApp.getID(),X.getID())) {
                    SearchApp.setStatus("Refunded");
                    int a = update.tellg();
                    int size = sizeof(SearchApp);
                    update.seekp(a - size);
                    update.write((char *) &SearchApp, sizeof(SearchApp));
                    cout<<"Status Updated!\n";
                    break;
                }}
            update.close();
            cout<<"Refund Processed!\n";
            return 1;
        }
    }

