#pragma once
#include <iomanip>
#include <iostream>
#include "HelpingFunc.h"
#include "Time.h"
#include "Feedback.h"
#include "Payment.h"
using namespace std;
class Appointment{
protected:
    char ID[100];
    char Name[100];
    char DCNIC[100];
    char PCNIC[100];
    Time Booking;
    char Type[100];
    char Status[100];
    float charge;
    Feedback Feed;
public:
    bool IDCheck(string id) {
        Appointment Temp;
        ifstream Obj("appointment_data.dat",ios::binary);
        while (Obj.read((char*)&Temp, sizeof(Temp))) {
            if (stringCmp(Temp.getID(),id))
                return 1;
        }
        return 0;
    }
    friend ostream& operator << (ostream& out,  Appointment& obj);
    void Add_Response();
    void Add_feedback();
    void Add(string filename);
    void setname(char* name){
        strcpy(Name,name);
    }
    void setpcnic(char* cnic){
        strcpy(PCNIC,cnic);
    }
    void setID(char* id){
        strcpy(ID,id);
    }
    string getID(){
        return ID;
    }
    void setdcnic(char* cnic){
        strcpy(DCNIC,cnic);
    }
    void setType(char* type){
        strcpy(Type,type);
    }
    void setStatus(char* status){
        strcpy(Status,status);
    }
    float getCharge(){
        return charge;
    }
    void setCharge(float set){
        charge=set;
    }
    Time getTime(){
        return Booking;
    }
    string getname(){
        return Name;
    }
    string getdcnic(){
        return DCNIC;
    }
    string getpcnic(){
        return PCNIC;
    }
    string gettype(){
        return Type;
    }
    string getstatus(){
        return Status;
    }

    void setTime(Time set){
        Booking=set;
    }
};

