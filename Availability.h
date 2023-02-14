#pragma once
#include <iomanip>
#include <iostream>
#include "Payment.h"
#include "Doctor.h"
#include "User.h"
using namespace std;

class Availabilty{
protected:
    bool Days[5];
    bool Availability_Status[24];
    bool Book_Status[24];
    int Availability_Count;
public:
    void view_schedule(string);
    void edit_schedule(string);
};

