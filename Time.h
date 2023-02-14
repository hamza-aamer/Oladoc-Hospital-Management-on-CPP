#pragma once
#include <iomanip>
#include "Appointment.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Time{
protected:
    int Day;
    int Month;
    int Year;
    int Hours;
public:
    void update_time();
    friend ostream& operator << (ostream& out, const Time& obj);

    int getDay(){
        return Day;
    }
    int getMonth(){
        return Month;
    }
    int getYear(){
        return Year;
    }
    int getHours(){
        return Hours;
    }
};

void Time::update_time() {
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    cout << (int)(now->tm_year + 1900) << '-'
         << (int)(now->tm_mon + 1) << '-'
         <<  (int)now->tm_mday
         << "\n";
    Year=(int)(now->tm_year + 1900);
    Month=(int)(now->tm_mon + 1);
    if (Month==1){
        Day=0;
    }           //31 Jump
    if (Month==2){
        Day=31;
    }           //28 Jump
    if (Month==3){
        Day=59;
    }           //31 Jump
    if (Month==4){
        Day=90;
    }           //30 Jump
    if (Month==5){
        Day=120;
    }           //31 Jump
    if (Month==6){
        Day=151;
    }           //30 Jump
    if (Month==7){
        Day=181;
    }           //31 Jump
    if (Month==8){
        Day=212;
    }           //31 Jump
    if (Month==9){
        Day=243;
    }           //30 Jump
    if (Month==10){
        Day=273;
    }           //31 Jump
    if (Month==11){
        Day=304;
    }           //30 Jump
    if (Month==12){
        Day=334;
    }
    Day+=(int)now->tm_mday;
    Hours=(int)(now->tm_hour);
    cout<<"Date,Time Updated!";
}
ostream& operator << (ostream& out, const Time& obj)
{
    out <<"Year : "<< obj.Year << endl;
    out <<"Month: "<<obj.Month<<endl;
    out<< "Day  : "<<obj.Day<<endl;
    out<< "Hour : "<<obj.Hours<<endl;
    return out;
}
