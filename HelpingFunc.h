#pragma once
#include <iostream>
#include <iomanip>
using namespace std;
bool CharCheck(string mail, char check) {
    for (int x=0;mail[x]!='\0';x++){
        if (mail[x]==check)
            return 1;
    }
    return 0;
}

int countDigit(char* Arr){
    int count;
    for (count=0;Arr[count]!='\0';count++);
    return count;
}
bool RangeCheck(char* Array,char start,char finish){
    for (int x=0;Array[x]!='\0';x++){
        if (Array[x]>=start && Array[x]<=finish) return 1;
    }
    return 0;
}
bool OnlyNumCheck(char* Arr){
    for (int count=0;Arr[count]!='\0';count++)
        if (Arr[count]<='0' && Arr[count]>='9')
            return 1;
    return 0;
}
bool NumCheck(char* Arr){
    for (int count=0;Arr[count]!='\0';count++)
        if (Arr[count]>='0' && Arr[count]<='9')
            return 1;
    return 0;
}
bool stringCmp(string a, string b){
    if (a==b) return 1;
    return 0;
}
