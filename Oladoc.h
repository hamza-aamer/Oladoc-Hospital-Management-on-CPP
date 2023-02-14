#pragma once
#include <iomanip>
#include "User.h"
#include "Doctor.h"
#include "Patient.h"
#include "Admin.h"
#include "Time.h"
#include "HelpingFunc.h"
#include <iostream>
class Oladoc{
    Doctor* Doc=new Doctor;
    Patient* Pat=new Patient;
    Admin* Adm=new Admin;
public:
    void menu();
};

void Display_Doc(Doctor search){
    cout<<"\nDisplaying info...\n";
    cout <<"Name : "<< search.getuser() << endl;
    cout <<"CNIC : "<< search.getcnic() << endl;
    cout <<"EMAIL: "<< search.getmail() << endl;
    cout <<"Years Of Experience : "<<search.getYOP() << endl;
    cout <<"Hospital : "<< search.getHospital() << endl;
    search.getCharges().view_charges();
    cout <<"Specialization : "<<search.getSpecialization() << endl;
    cout <<"City : "<< search.getLocation() << endl;
}

ostream& operator << (ostream& out,  Appointment& obj)
{
    out <<"ID   : "<<obj.getID()<<endl;
    out <<"Name : "<< obj.getname() << endl;
    out <<"Patient CNIC : "<< obj.getpcnic() << endl;
    out <<"Doctor CNIC : "<< obj.getdcnic() << endl;
    out <<"Type : "<<obj.gettype() << endl;
    out <<"Status : "<<obj.getstatus() << endl;
    out <<"Time : "<< obj.getTime() << endl;
    if (obj.Feed.getstatus()){
        out<<"Feedback : "<<obj.Feed.getFeedback()<<endl;
        out<<"Rating : ";
        for (int x=0;x<obj.Feed.getRating();x++){
            cout<<'*';
        }
        cout<<endl;
        if (obj.Feed.getRstatus()){
            out<<"Feedback Response : "<<obj.Feed.getResponse()<<endl;
        }
    }
    out <<"Charges : "<<obj.getCharge()<<endl;

    out<<"Now Displaying Doctor Info...\n\n";
    Doctor Find;
    ifstream read("doctor_data.dat",ios::binary);
    while(read.read((char*)&Find,sizeof(Find))){
        if(stringCmp(Find.getcnic(),obj.getdcnic())){
            Display_Doc(Find);
            break;
        }
    }
    return out;
}

void Oladoc::menu() {
    int select,select1;
    cout<<"Please Select :\n\t1.Login\n\t2.Register\n\t3.View Doctors\nYour Selection : ";
    cin>>select;
    switch(select){
        case 1:
            cout<<"Please Select :\n\t1.Doctor\n\t2.Patient\n\t3.Admin\nYour Selection : ";
            cin>>select1;
            switch(select1){
                case 1:
                    if (Doc->login("doctor_data.dat"))
                        Doc->menu();

                    break;
                case 2:
                    if (Pat->login("patient_data.dat"))
                        Pat->menu();
                    break;
                case 3:
                    if (Adm->login())
                        Adm->menu();
                    break;
            }
            break;
        case 2:
            cout<<"Please Select :\n\t1.Doctor\n\t2.Patient\nYour Selection : ";
            cin>>select1;
            switch(select1) {
                case 1:
                    Doc->Register();
                    break;
                case 2:
                    Pat->Register();
                    break;
            }
            break;
        case 3:
            Doctor search;
            int counter=1;
            cout<<"Displaying Doctors...\n";
            ifstream read("doctor_data.dat",ios::binary);
            while(read.read((char*)&search,sizeof(search))){
                cout<<"Doctor # "<<counter<<endl;
                Display_Doc(search);
                cout<<endl<<endl;
                counter++;
            }
            read.close();
            break;
    }

    this->menu();
}




//Sub Functions



void Doctor::view_P_data(string Patient_CNIC){
    Patient search;
    ifstream obj("patient_data.dat",ios::binary);
    while(obj.read((char*)&search,sizeof (search))){
        if (stringCmp(search.getcnic(),Patient_CNIC)){
            cout<<"Patient found !\nDisplaying info...\n";
            cout<<search;
        }
    }
}

//Sub Functions




int Patient::search_doctors() {
    Doctor search;
    string tempo;
    back:
    cout<<"Welcome to Doctor Search Interface!\n";
    cout<<"Please Select : \n\t1.Search by Specialization\n\t2.Search by Location\n\t3.Search by Hospital\n\t4.Search by CNIC\n\t5.Go Back\nSelection : ";
    int select,select1;
    ifstream obj("doctor_data.dat",ios::binary);
    cin>>select;
    switch(select){
        case 1:
        cout<<"\nPlease Select\n\t1.Dermatology\n\t2.Anesthesiology\n\t3.Ophthalmology\n\t4.Pediatrics\n\t5.Psychiatry\n\t6.Go Back\nSelection : ";
        cin>>select1;
        switch(select1){
            case 1:
                while(obj.read((char*)&search,sizeof (search))){
                    if (stringCmp(search.getSpecialization(),"Dermatology")){
                        Display_Doc(search);
                    }}
                break;
            case 2:
                while(obj.read((char*)&search,sizeof (search))){
                    if (stringCmp(search.getSpecialization(),"Anesthesiology")){
                        Display_Doc(search);
                }}
                break;
            case 3:
                while(obj.read((char*)&search,sizeof (search))){
                    if (stringCmp(search.getSpecialization(),"Ophthalmology")){
                        Display_Doc(search);
                }}
                break;
            case 4:
                while(obj.read((char*)&search,sizeof (search))){
                    if (stringCmp(search.getSpecialization(),"Pediatrics")){
                        Display_Doc(search);
                }}
                break;
            case 5:
                while(obj.read((char*)&search,sizeof (search))){
                    if (stringCmp(search.getSpecialization(),"Psychiatry")){
                        Display_Doc(search);
                }}
                break;
            case 6:
                goto back;
        }
            break;
        case 2:
            cout<<"\nPlease Select\n\t1.Islamabad\n\t2.Gujranwala\n\t3.Lahore\n\t4.Faislabad\n\t5.Karachi\n\t6.Go Back\nSelection : ";

            cin>>select1;
            switch(select1){
                case 1:
                    while(obj.read((char*)&search,sizeof (search))){
                        if (stringCmp(search.getLocation(),"Islamabad")){
                            Display_Doc(search);
                        }}
                    break;
                case 2:
                    while(obj.read((char*)&search,sizeof (search))){
                        if (stringCmp(search.getLocation(),"Gujranwala")){
                            Display_Doc(search);
                        }}
                    break;
                case 3:
                    while(obj.read((char*)&search,sizeof (search))){
                        if (stringCmp(search.getLocation(),"Lahore")){
                            Display_Doc(search);
                        }}
                    break;
                case 4:
                    while(obj.read((char*)&search,sizeof (search))){
                        if (stringCmp(search.getLocation(),"Faislabad")){
                            Display_Doc(search);
                        }}
                    break;
                case 5:
                    while(obj.read((char*)&search,sizeof (search))){
                        if (stringCmp(search.getLocation(),"Karachi")){
                            Display_Doc(search);
                        }}
                    break;
                case 6:
                    goto back;
            }
            break;
        case 3:
            cout<<"\nPlease Select\n\t1.Shaukat Khanum Memorial\n\t2.Pakistan Institute of Medical Sciences\n\t3.Combined Medical Hospital\n\t4.Agha Khan University Hospital\n\t5.Shifa International Hospital\n\t6.Go Back\nSelection : ";

            cin>>select1;
            switch(select1){
                case 1:
                    while(obj.read((char*)&search,sizeof (search))){
                        if (stringCmp(search.getHospital(),"Shaukat Khanum Memorial")){
                            Display_Doc(search);
                        }}
                    break;
                case 2:
                    while(obj.read((char*)&search,sizeof (search))){
                        if (stringCmp(search.getHospital(),"Pakistan Institute of Medical Sciences")){
                            Display_Doc(search);
                        }}
                    break;
                case 3:
                    while(obj.read((char*)&search,sizeof (search))){
                        if (stringCmp(search.getHospital(),"Combined Medical Hospital")){
                            Display_Doc(search);
                        }}
                    break;
                case 4:
                    while(obj.read((char*)&search,sizeof (search))){
                        if (stringCmp(search.getHospital(),"Agha Khan University Hospital")){
                            Display_Doc(search);
                        }}
                    break;
                case 5:
                    while(obj.read((char*)&search,sizeof (search))){
                        if (stringCmp(search.getHospital(),"Shifa International Hospital")){
                            Display_Doc(search);
                        }}
                    break;
                case 6:
                    goto back;
            }
            break;
        case 4:
            cout<<"Please Enter Doctor CNIC : ";
            cin>>tempo;
            while(obj.read((char*)&search,sizeof (search))){
                if (stringCmp(search.getcnic(),tempo)){
                    Display_Doc(search);
                    break;
                }}
            cout<<"Would you like to see Schedule (1|0) : ";
            cin>>tempo;
            if (tempo=="1"){
                AvailabilityFetch.view_schedule(search.getcnic());
            }
            break;
        case 5:
            return 0;
            break;
    }
    return 1;
}

void Appointment::Add(string file_name){
    ofstream obj;
    obj.open(file_name, ios::binary | ios::app);
    obj.write((char*)this, sizeof(*this));
    obj.close();
}

int Patient::add_appointments() {
    cout<<"Welcome to Appointment Creation Portal!\n";
    if (UserCheckApt(CNIC)){
        cout<<"An Appointment already Exists!\n";
        return 1;
    }
    char Hospital[100];
    char Location[100];
    char Specialization[100];
    char ID[100];
    Doctor Find;
    int select;
    float charges;
    Clock.update_time();
    AppFetch.setTime(Clock);
    unique:
    cout<<"Enter Appointment ID (Must be Unique) : ";
    cin>>ID;
    if (AppFetch.IDCheck(ID)) {
        cout << "ID Must be Unique!\n";
        goto unique;
    }
    AppFetch.setID(ID);

    cout<<"Please Select:\n\t1.Shaukat Khanum Memorial\n\t2.Pakistan Institute of Medical Sciences\n\t3.Combined Medical Hospital\n\t4.Agha Khan University Hospital\n\t5.Shifa International Hospital\nSelection : ";
    cin>>select;
    switch(select){
        case 1:
            strcpy(Hospital,"Shaukat Khanum Memorial");
            break;
        case 2:
            strcpy(Hospital,"Pakistan Institute of Medical Sciences");
            break;
        case 3:
            strcpy(Hospital,"Combined Medical Hospital");
            break;
        case 4:
            strcpy(Hospital,"Agha Khan University Hospital");
            break;
        case 5:
            strcpy(Hospital,"Shifa International Hospital");
            break;
    }
    cout<<"Please Select:\n\t1.Islamabad\n\t2.Gujranwala\n\t3.Lahore\n\t4.Faislabad\n\t5.Karachi\nSelection: ";
    cin>>select;
    switch (select){
        case 1:
            strcpy(Location,"Islamabad");
            break;
        case 2:
            strcpy(Location,"Gujranwala");
            break;
        case 3:
            strcpy(Location,"Lahore");
            break;
        case 4:
            strcpy(Location,"Faislabad");
            break;
        case 5:
            strcpy(Location,"Karachi");
            break;
    }
    cout<<"Please Select:\n\t1.Dermatology\n\t2.Anesthesiology\n\t3.Ophthalmology\n\t4.Pediatrics\n\t5.Psychiatry\nSelection: ";
    cin>>select;
    switch (select){
        case 1:
            strcpy(Specialization,"Dermatology");
            break;
        case 2:
            strcpy(Specialization,"Anesthesiology");
            break;
        case 3:
            strcpy(Specialization,"Ophthalmology");
            break;
        case 4:
            strcpy(Specialization,"Pediatrics");
            break;
        case 5:
            strcpy(Specialization,"Psychiatry");
            break;
    }
    Doctor search;
    int counter=1;
    cout<<"Displaying Doctors...\n";
    ifstream read("doctor_data.dat",ios::binary);
    while(read.read((char*)&search,sizeof(search))){
        if (stringCmp(search.getHospital(),Hospital)){
            if (stringCmp(search.getLocation(),Location)){
                if (stringCmp(search.getSpecialization(),Specialization)){
                    cout<<"Doctor # "<<counter<<endl;
                    Display_Doc(search);
                    cout<<endl<<endl;
                    counter++;
                }
            }
        }
    }
    read.close();
    char searchCNIC[100];
    counter=0;
    cout<<"Enter Doctor CNIC : ";
        cin>>searchCNIC;
     read.open("doctor_data.dat",ios::binary);
    while(read.read((char*)&search,sizeof(search))){
        if (stringCmp(search.getcnic(),searchCNIC)){
            cout<<"Doctor Found!\n" <<endl;
            Display_Doc(search);
            cout<<endl<<endl;
            counter++;
            break;
        }
    }
    cout<<"Please Select:\n\t1.Online Appointment\n\t2.In-Person Appointment\nSelection : ";
    cin>>select;
    switch(select){
        case 1:
            AppFetch.setType("Online");
            if (Balance>search.getCharges().get_Online()){
                Balance-=search.getCharges().get_Online();
                cout<<search.getCharges().get_Online()<<"Balance Deducted!\n";
                AppFetch.setCharge(search.getCharges().get_Online());
            }
            else {
                cout << "Balance not enough.. Request Failed!\n";
                return 1;
            }
            break;
        case 2:
            AppFetch.setType("In-Person");
            if (Balance>search.getCharges().get_person()){
                Balance-=search.getCharges().get_person();
                cout<<search.getCharges().get_person()<<" Balance Deducted!\n";
                AppFetch.setCharge(search.getCharges().get_person());
            }
            else {
                cout << "Balance not enough.. Request Failed!\n";
                return 1;
            }
            break;
    }
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
    AppFetch.setpcnic(CNIC);
    AppFetch.setdcnic(searchCNIC);
    AppFetch.setname(Username);
    AppFetch.setStatus("Completed");
    AppFetch.Add("appointment_data.dat");
    read.close();
}

