#pragma once
#include <iomanip>
#include "Appointment.h"
#include <iostream>
using namespace std;
class Charges{
protected:
    float Hourly_Charge_InPerson;
    float Hourly_Charge_Online;
public:
    int view_charges() const;
    float get_person() const {
        return Hourly_Charge_InPerson;
    }
    float get_Online() const {
        return Hourly_Charge_Online;
    }
    void edit_charges();
    void operator = (const float);

};
class Payment_Gateway{
public:
    virtual int Charge(){
        cout<<"Payment Gateway";
    }
};
class Bank_Transfer:public Payment_Gateway{
protected:
    string Account_Number;
    string User_Expiry;
    string User_CCV;
public:
    virtual int Charge(){
        cout<<"Welcome to Bank Transfer Gateway";
        start:
        cout<<"Please Enter valid Account Number : ";
        cin>>Account_Number;
        if (Account_Number.length()!=17){
            cout<<"Account Number should have 17 Digits\n";
            goto start;
        }
        string temp;
        expMon:
        cout<<"Please Enter Expiry Month : ";
        cin>>temp;
        if (temp.length()!=2) { goto expMon; }
        User_Expiry=temp;
        expYear:
        cout<<"Please Enter Expiry Year : ";
        cin>>temp;
        if (temp.length()!=4) { goto expYear; };
        User_Expiry+=temp;
        CCV:
        cout<<"Please Enter CCV : ";
        cin>>User_CCV;
        if (User_CCV.length()!=3) {cout<<"Must be 3 Digits\n"; goto CCV; };
        cout<<"Connection Successful!\n";
        cout<<"Please Enter amount to deposit as Balance : ";
        int dep;
        cin>>dep;
        return dep;
    }
};
class EasyPaisa:public Payment_Gateway{
protected:
    string User_Number;
public:
    virtual int Charge(){
        cout<<"Welcome to EasyPaisa Gateway\n";
        start:
        cout<<"Please Enter valid Phone number : ";
        cin>>User_Number;
        if (User_Number.length()!=11){
            cout<<"Phone No should have 11 Digits\n";
            goto start;
        }
        cout<<"Connection Successful!\n";
        cout<<"Please Enter amount to deposit as Balance : ";
        int dep;
        cin>>dep;
        return dep;
    }
};
class Union_Pay:public Bank_Transfer{
public:
    virtual int Charge(){
        cout<<"Welcome to Union Pay Gateway";
        start:
        cout<<"Please Enter valid Account Number : ";
        cin>>Account_Number;
        if (Account_Number.length()!=17){
            cout<<"Account Number should have 17 Digits\n";
            goto start;
        }
        string temp;
        expMon:
        cout<<"Please Enter Expiry Month : ";
        cin>>temp;
        if (temp.length()!=2) { goto expMon; }
        User_Expiry=temp;
        expYear:
        cout<<"Please Enter Expiry Year : ";
        cin>>temp;
        if (temp.length()!=4) { goto expYear ;};
        User_Expiry+=temp;
        CCV:
        cout<<"Please Enter CCV : ";
        cin>>User_CCV;
        if (User_CCV.length()!=3) {cout<<"Must be 3 Digits\n"; goto CCV; };
        cout<<"Connection Successful!\n";
        cout<<"Please Enter amount to deposit as Balance : ";
        int dep;
        cin>>dep;
        return dep;
    }
};
class Paypak:public Bank_Transfer{
public:
    virtual int Charge(){
        cout<<"Welcome to Paypak Gateway";
        start:
        cout<<"Please Enter valid Account Number : ";
        cin>>Account_Number;
        if (Account_Number.length()!=17){
            cout<<"Account Number should have 17 Digits\n";
            goto start;
        }
        string temp;
        expMon:
        cout<<"Please Enter Expiry Month : ";
        cin>>temp;
        if (temp.length()!=2) { goto expMon; }
        User_Expiry=temp;
        expYear:
        cout<<"Please Enter Expiry Year : ";
        cin>>temp;
        if (temp.length()!=4) { goto expYear; };
        User_Expiry+=temp;
        CCV:
        cout<<"Please Enter CCV : ";
        cin>>User_CCV;
        if (User_CCV.length()!=3) {cout<<"Must be 3 Digits\n"; goto CCV; };
        cout<<"Connection Successful!\n";
        cout<<"Please Enter amount to deposit as Balance : ";
        int dep;
        cin>>dep;
        return dep;
    }
};

int Charges::view_charges() const {
    cout<<"In Person Appointment : "<<Hourly_Charge_InPerson<<" per hour.\n";
    cout<<"Online Appointment : "<<Hourly_Charge_Online<<" per hour.\n";
}
void Charges::edit_charges() {
    cout<<"Please Enter Charges/Hour in PKR :";
    cin>>Hourly_Charge_InPerson;
    Hourly_Charge_Online=((Hourly_Charge_InPerson/100)*70);
}
void Charges::operator = (const float charge){
    this->Hourly_Charge_InPerson=charge;
    Hourly_Charge_Online=(charge/100)*70;
};
