#ifndef SIMULATION_H
#define SIMULATION_H

#include "Scheduler.h"
#include "CPU.h"
#include "MMU.h"

class Simulation{
    uint32_t clock=0;
    vector<shared_ptr<Process>>all_processes;
    shared_ptr<Scheduler> scheduler;
    CPU cpu;
    MMU mmu;
    shared_ptr<Process> running_process=nullptr;

public:

    Simulation(uint32_t memSize, uint32_t pgSize);
    void loadScenario(const string& filepath);
    void run();

};

#endif