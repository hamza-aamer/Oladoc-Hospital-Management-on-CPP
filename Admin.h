#pragma once
#include <iomanip>
#include "Appointment.h"
#include "User.h"
#include "Doctor.h"
#include "Oladoc.h"
#include "Appointment.h"
#include "Availability.h"
#include <iostream>
#include <fstream>
#include <string>
class Admin:public User{
private:
    string Username;
    string Password;
public:
    int menu();
    bool login();
    void view_P_data();
    void view_D_data();
    void view_schedule(string Doctor_CNIC);
    void edit_schedule(string Doctor_CNIC);
    void edit_P_info(string Patient_CNIC);
    void edit_D_info(string Doctor_CNIC);
};

void Admin::view_schedule(string Doctor_CNIC) {
    Doctor search;
    ifstream read("doctor_data.dat",ios::binary);
    while(read.read((char*)&search,sizeof(search))){
        if (stringCmp(search.getcnic(),Doctor_CNIC)){
            cout<<"Doctor Found... \n Displaying Schedule : ";
            search.getAvail().view_schedule(search.getcnic());
            break;
        }
    }
    read.close();
}
void Admin::edit_schedule(string Doctor_CNIC) {
    Doctor setup;
    setup.getAvail().edit_schedule(Doctor_CNIC);
}


bool Admin::login(){
        char user[100], pass[100];
        cout << "Enter your Username or CNIC to Login : ";
        cin>>user;
        cout << "Enter your password : ";
        cin>>pass;
        if (stringCmp(user,"Admin"))
        {
            cout<<"Correct user!\n";
            if (stringCmp(pass, "Abc123@"))
            {
                cout<<"Login Successful!\n";
                Username=user;
                Password=pass;
                return 1;
            }
        }
        cout<<"Login Failed!\n";
        return 0;
}

void Admin::edit_P_info(string Patient_CNIC) {
    Patient edit;
    ifstream finding("patient_data.dat",ios::binary);
    while (finding.read((char*)&edit,sizeof(edit))){
    if (stringCmp(edit.getcnic(),Patient_CNIC)){
        edit.edit_info();
        break;
    }
    }
}

void Admin::edit_D_info(string Doctor_CNIC) {
    Doctor edit;
    ifstream finding("doctor_data.dat",ios::binary);
    while (finding.read((char*)&edit,sizeof(edit))){
        if (stringCmp(edit.getcnic(),Doctor_CNIC)){
            edit.edit_info();
            break;
        }
    }
}

void Admin::view_P_data() {
    Patient search;
    int counter=1;
    cout<<"Displaying Patients...\n";
    ifstream read("patient_data.dat",ios::binary);
    while(read.read((char*)&search,sizeof(search))){
        cout<<"Patient # "<<counter<<endl;
        cout<<search;
        cout<<endl<<endl;
        counter++;
    }
    read.close();
}
void Admin::view_D_data() {
    Doctor search;
    int counter=1;
    cout<<"Displaying Doctors...\n";
    ifstream read("doctor_data.dat",ios::binary);
    while(read.read((char*)&search,sizeof(search))){
        cout<<"Doctor # "<<counter<<endl;
        cout<<search;
        cout<<endl<<endl;
        counter++;
    }
    read.close();
}
int Admin::menu(){
    Doctor Doc;
    string temp;
    cin.ignore();
    cout<<"Please Select :\n\t1.Display All Docs\n\t2.Display All Patient\n\t3.View Doctor Schedule\n\t4.Edit Doctor Schedule\n\t5.Edit Patient Info\n\t6.Edit Doctor Info\n\t9.Logout\nSelection : ";
    int select;
    cin>>select;
    switch (select){
        case 1:
            view_D_data();
            break;
        case 2:
            view_P_data();
            break;
        case 3:
            cout<<"Please Enter the Doctor's CNIC : ";
            cin>>temp;
            view_schedule(temp);
            break;
        case 4:
            cout<<"Please Enter the Doctor's CNIC : ";
            cin>>temp;
            edit_schedule(temp);
            break;
        case 5:
            cout<<"Please Enter the Patient's CNIC : ";
            cin>>temp;
            edit_P_info(temp);
            break;
        case 6:
            cout<<"Please Enter the Doctor's CNIC : ";
            cin>>temp;
            edit_D_info(temp);
            break;
        case 9:
            return 1;
            break;
    }
    menu();
}
