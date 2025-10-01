#ifndef LOGGER_H
#define LOGGER_H


#include<bits/stdc++.h>
using namespace std;


class Logger{
public:
    static void log(const string&comp, const string& msg){
        cout<<"["<<left<<setw(10)<<comp<<"]"<<msg<<endl;
    }
};



#endif