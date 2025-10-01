#ifndef PROCESS_H
#define PROCESS_H

#include<bits/stdc++.h>
using namespace std;

struct PageTableEntry{

    bool pres=false;
    uint32_t frame_num=-1;
    uint32_t last_used_time=0;

};

struct Process{

    uint32_t pid;

    string name;

    uint32_t arrivalTime, burstTime, remainingTime, priority;

    vector<uint32_t> memoryAccesses;

    int currAccessIndex=0;

    enum class State {NEW, READY, RUNNING, TERMINATED};
    State currState=State::NEW;


    // making page table 
    map<uint32_t, PageTableEntry> pageTable; 

    //constructor
    Process(uint32_t p,string n, uint32_t at,uint32_t bt , uint32_t prio){
        this->pid=p;
        this->name=n;
        this->arrivalTime=at;
        this->burstTime=bt;
        this->remainingTime=bt;
        this->priority=prio;
    }

};


#endif