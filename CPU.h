#ifndef CPU_H
#define CPU_H


#include "Process.h"
#include "MMU.h"
#include "Logger.h"


class CPU{

public:
    void execute(shared_ptr<Process> p, vector<shared_ptr<Process>>& all_processes,MMU& mmu,uint32_t clock){
        if(!p){
            return;
        }

        Logger::log("CPU","Executing "+p->name);
        p->remainingTime--;

        if(p->currAccessIndex < p->memoryAccesses.size()){
            mmu.translateAddress(p,all_processes,p->memoryAccesses[p->currAccessIndex++],clock);
        }
    }
};


#endif