#pragma once
#include <iomanip>
#include "User.h"
#include "Doctor.h"
#include "Patient.h"
#include "Time.h"
#include "HelpingFunc.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Availability.h"
class Doctor:public User{
protected:
    Appointment App;
    Charges charges;
    Availabilty Availability;
    Time Clock;
    Payment_Gateway Payment;
    char Username[100];
    char Password[100];
    char Email[100];
    char CNIC[100];
    char Hospital[100];
    char Specialization[100];
    char Location[100];
    int Years_of_Experience;
public:
    int menu();
    bool login(string filename);
    bool Register();
    int edit_info();
    void view_P_data(string Patient_CNIC);
    void view_Appointments();
    void Add(string name);
    bool MailCheck(string mail);
    bool UserCheck(string Username);
    bool CNICCheck(string CNIC);
    int reset_password();
    void logout();
    void operator = (const Doctor& obj);

    const char* getHospital()const {
        return Hospital;
    }
    const char* getLocation()const{
        return Location;
    }
    const char* getPass()const {
        return Password;
    }
    Availabilty getAvail() {
        return Availability;
    }
    Availabilty setAvailability(Availabilty AvailabiltyVAl){
        Availability=AvailabiltyVAl;
    }
    const int getYOP()const {
        return Years_of_Experience;
    }
    const char* getSpecialization()const {
        return Specialization;
    }
    Charges const getCharges() const {
        return charges;
    }
    const char* getmail()const {
        return Email;
    }
    const char* getuser()const{
        return Username;
    }
    const char* getcnic()const {
        return CNIC;
    }

};

void Doctor::view_Appointments() {
    Appointment Find;
    int counter=1;
    cout<<"Now displaying your Appointments...\n";
    ifstream search("appointment_data.dat",ios::binary);
    while (search.read((char*)&Find,sizeof(Find))){
        if (stringCmp(Find.getdcnic(),CNIC)) {
            cout << "Appointment # " << counter << endl;
            cout << Find << endl;
            counter++;
        }
    }
    search.close();
    cout<<"Would you like to Cancel any Appointment (1|0)? ";
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
        Patient ref;
        ref.Appointment_refund(Find);
    }
    cout<<"Would you like to leave Response on any Appointment (1|0)? ";
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
        Find.Add_Response();
    }
}


ostream& operator << (ostream& out, const Doctor& obj)
{
    out <<"Name : "<< obj.getuser() << endl;
    out <<"CNIC : "<< obj.getcnic() << endl;
    out <<"EMAIL: "<< obj.getmail() << endl;
    out <<"Pass : "<< obj.getPass() << endl;
    out <<"Years Of Experience : "<<obj.getYOP() << endl;
    out <<"Hospital : "<< obj.getHospital() << endl;
    obj.getCharges().view_charges();
    out <<"Specialization : "<<obj.getSpecialization() << endl;
    out <<"City : "<< obj.getLocation() << endl;

    return out;
}

bool Doctor::MailCheck(string email) {
    Doctor Temp;
    ifstream Obj("doctor_data.dat",ios::binary);
    while (Obj.read((char*)&Temp, sizeof(Temp))) {
        if (!strcmp((const char*)Temp.getmail(),(const char*)&email))
            return 1;
    }
    return 0;
}
bool Doctor::UserCheck(string username) {
    Doctor Temp;
    ifstream Obj("doctor_data.dat",ios::binary);
    while (Obj.read((char*)&Temp, sizeof(Temp))) {
        if (!strcmp((const char*)Temp.getuser(),(const char*)&username))
            return 1;
    }
    return 0;
}

bool Doctor::CNICCheck(string cnic) {
    Doctor Temp;
    ifstream Obj("doctor_data.dat",ios::binary);
    while (Obj.read((char*)&Temp, sizeof(Temp))) {
        if (!strcmp((const char*)Temp.getcnic(),(const char*)&cnic))
            return 1;
    }
    return 0;
}

void Doctor::Add(string fileName)
{
    ofstream obj;
    obj.open(fileName, ios::binary | ios::app);
    obj.write((char*)this, sizeof(*this));
    obj.close();
}


int Doctor::edit_info() {
    fstream update("doctor_data.dat", ios::binary | ios::in | ios::out);
    char temp[100];
    char pass[100];
    Doctor Search;
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
                    }
                }}
            break;
        case 4:
            return 1;
            break;
    }
    edit_info();
    return 1;
}


bool Doctor::Register() {

    bool checker = 0;
    char name[100],pass[100] ,cnic[100], city[100],mail[100], hospital[100], specialization[100];
    class Charges charge;
    class Availabilty Avail;
    int exp;
    UserEnter:
    cout << "Please enter a unique Username : ";
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


    CityEnter:
    int select;
    cout << "Select the name of your city please: \n";
    cout<<"\t1.Islamabad\n\t2.Gujranwala\n\t3.Lahore\n\t4.Faislabad\n\t5.Karachi\nMake Decision: ";
    cin>>select;
    switch (select){
        case 1:
            strcpy(city,"Islamabad");
            break;
        case 2:
            strcpy(city,"Gujranwala");
            break;
        case 3:
            strcpy(city,"Lahore");
            break;
        case 4:
            strcpy(city,"Faislabad");
            break;
        case 5:
            strcpy(city,"Karachi");
            break;
    }
    if (select<1 || select>5) goto CityEnter;

    HospitalEnter:
    cout << "Select the name of your Hospital please: \n";
    cout<<"\t1.Shaukat Khanum Memorial\n\t2.Pakistan Institute of Medical Sciences\n\t3.Combined Medical Hospital\n\t4.Agha Khan University Hospital\n\t5.Shifa International Hospital\nMake Decision: ";
    cin>>select;
    switch (select){
        case 1:
            strcpy(hospital,"Shaukat Khanum Memorial");
            break;
        case 2:
            strcpy(hospital,"Pakistan Institute of Medical Sciences");
            break;
        case 3:
            strcpy(hospital,"Combined Medical Hospital");
            break;
        case 4:
            strcpy(hospital,"Agha Khan University Hospital");
            break;
        case 5:
            strcpy(hospital,"Shifa International Hospital");
            break;
    }
    if (select<1 || select>5) goto HospitalEnter;

    SpecilizationEnter:
    cout << "Select the name of your Specialization please: \n";
    cout<<"\t1.Dermatology\n\t2.Anesthesiology\n\t3.Ophthalmology\n\t4.Pediatrics\n\t5.Psychiatry\nMake Decision: ";
    cin>>select;
    switch (select){
        case 1:
            strcpy(specialization,"Dermatology");
            break;
        case 2:
            strcpy(specialization,"Anesthesiology");
            break;
        case 3:
            strcpy(specialization,"Ophthalmology");
            break;
        case 4:
            strcpy(specialization,"Pediatrics");
            break;
        case 5:
            strcpy(specialization,"Psychiatry");
            break;
    }
    if (select<1 || select>5) goto SpecilizationEnter;

    charge.edit_charges();
    cin.ignore();
    cout << "Please Enter How many years of experience you have please : ";
    cin >> exp;

    Avail.edit_schedule(CNIC);

    Availability=Avail;
    charges = charge;
    Years_of_Experience = exp;
    strcpy(Username, name);
    strcpy(Hospital, hospital);
    strcpy(Password, pass);
    strcpy(Email, mail);
    strcpy(Location, city);
    strcpy(Specialization,specialization);
    strcpy(CNIC, cnic);


    checker = 1;

    Add("doctor_data.dat");
    cout<<*this;
    cout << "Registration Successful!" << endl;

    return checker;
}

void Doctor::operator = (const Doctor& obj)
{
    charges = obj.charges;
    Years_of_Experience = obj.Years_of_Experience;
    strcpy(Username, obj.Username);
    strcpy(Password, obj.Password);
    strcpy(CNIC, obj.CNIC);
    strcpy(Location, obj.Location);
    strcpy(Hospital, obj.Hospital);
    strcpy(Email, obj.Email);
    strcpy(Specialization,obj.Specialization);
}

bool Doctor::login(string fileName="doctor_data.dat")
{
    char user[100], pass[100];
    cout << "Enter your Username or CNIC to Login : ";
    cin>>user;
    cout << "Enter your password : ";
    cin>>pass;
    Doctor fetch;
    ifstream obj(fileName, ios::binary);
    while (obj.read((char*)&fetch, sizeof(fetch)))
    {
        if (stringCmp(fetch.Username, user) || stringCmp(fetch.CNIC, user))
        {
            cout<<"Correct user!\n";
            if (stringCmp(fetch.Password, pass))
            {
                cout<<"Login Successful!\n";
                *this = fetch;
                return 1;
                break;
            }
        }
    }
    obj.close();
    cout<<"Login Failed!\n";
    return 0;
}


void Doctor::logout(){
    char null[100]="\0";
    strcpy(this->Username,null);
    strcpy(this->Password,null);
    strcpy(this->CNIC,null);
    strcpy(this->Email,null);
    strcpy(this->Specialization,null);
    strcpy(this->Location,null);
    strcpy(this->Hospital,null);
    this->Years_of_Experience=0;
    this->charges=0;
    cout<<"Logout Successful!\n";
}




int Doctor::menu() {
    string temp;
    cout<<"Please Select:\n\t1.View Self Info\n\t2.View Patient Info\n\t3.View Scheudle\n\t4.Edit Schedule\n\t5.View Appointments\n\t6.Edit Info\n\t9.Logout\nSelection : ";
    int select;
    cin>>select;
    switch(select){
        case 1:
            cout<<*this<<endl;
            break;
        case 2:
            cout<<"Please Enter Patient CNIC : ";
            cin>>temp;
            this->view_P_data(temp);
            break;
        case 3:
            this->getAvail().view_schedule(CNIC);
            break;
        case 4:
            this->getAvail().edit_schedule(CNIC);
            break;
        case 5:
            this->view_Appointments();
            break;
        case 6:
            this->edit_info();
            break;
        case 9:
            logout();
            return 0;
            break;
    }
    this->menu();
}

int Doctor::reset_password() {
    cout<<"Please Enter your Old Password :";
    char pass[100];
    bool checker;
    cin>>pass;
    Doctor Search;
    fstream update("doctor_data.dat", ios::binary | ios::in | ios::out);
    while(update.read((char*)&Search,sizeof(Search))) {
        if (stringCmp(Search.CNIC,CNIC)) {
            if (stringCmp(Search.Password,pass)){
                cout<<"Password Verified!\n";
                PassEnter:
                checker = 0;
                cout << "Set password please: ";
                cin>>pass;
                if ( !RangeCheck(pass, 58, 64) && !RangeCheck(pass, 33, 47)  && !RangeCheck(pass, 123, 126) && !RangeCheck(pass, 91, 96))
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


void Availabilty::edit_schedule(string Doctor_CNIC) {
    int temp,temp2;
    cout<<"Welcome to Schedule setup Portal!\n";
    input:
    cout<<"Please Enter the Number of Days you are free in a week (1-5): ";
    cin>>temp;
    for (int x=0;x<5;x++){
        Days[x]=0;
    }
    if (temp<1 || temp>5)goto input;
    if (temp!=5)
        for (int x=0;x<temp;x++){
            select:
            cout<<"Please Select Day "<<x+1<<" : \n";
            cout<<"\t1.Monday\n\t2.Tuesday\n\t3.Wednesday\n\t4.Thursday\n\t5.Friday\n Selection : ";
            cin>>temp2;
            if (temp2<1 || temp2>5) {cout<<"Error.. Please Select Valid Day!\n";goto select; }
            if (Days[temp2-1]==1){
                cout<<"Day Already Selected, Please Select a different Day!\n";
                goto select;
            }
            Days[temp2-1]=1;
        }
    if (temp==5){
        for (int x=0;x<5;x++){
            Days[x]=1;
        }
    }
    for (int x=0;x<24;x++){
        Availability_Status[x]=0;
        Book_Status[x]=0;
    }
    cout<<"Please Enter Starting Hour (0-24): ";
    cin>>temp;
    cout<<"Please Enter Finishing Hour (0-24):";
    cin>>temp2;
    Availability_Count=0;
    for (int x=temp-1;x<temp2;x++){
        Availability_Status[x]=1;
        Availability_Count++;
    }
    cout<<"Number of Hours Available each Day : "<<Availability_Count<<endl;


    Doctor Search;
    fstream update("doctor_data.dat",ios::binary | ios::in | ios::out );

    while(update.read((char*)&Search,sizeof(Search))) {
        if (stringCmp(Search.getcnic(),Doctor_CNIC)) {
            Search.setAvailability(*this);
            int a = update.tellg();
            int size = sizeof(Search);
            update.seekp(a - size);
            update.write((char *) &Search, sizeof(Search));
            update.close();
            break;
        }}
    cout<<"Info Updated;";
}


void Availabilty::view_schedule(string Doctor_CNIC){
Doctor doc;
ifstream search("doctor_data.dat",ios::binary);
while (search.read((char*)&doc,sizeof(doc))){
    if (stringCmp(Doctor_CNIC,doc.getcnic())){
        *this=doc.getAvail();
        break;
    }
}
search.close();
    string Week[5]={"Monday","Tuesday","Wednesday","Thursday","Friday"};
    cout<<"Days Available: \n";
    for (int x=0;x<5;x++){
        if (Days[x]==1){
            cout<<Week[x]<<endl;
        }
    }
    cout<<"Hours Available : \n";
    for (int x=0;x<24;x++){
        if (Availability_Status[x]==1){
            cout<<x<<":00\n";
        }
    }
}
