#include "Simulation.h"
#include "Logger.h"



Simulation::Simulation(uint32_t memSize, uint32_t pgSize):mmu(memSize, pgSize){}



void Simulation::loadScenario(const string& filepath){
    ifstream file(filepath);
    string line;

    if(!file.is_open()){
        Logger::log("SIMULATOR","ERROR: Could not open scenario file: "+filepath);
        return;
    }


    while(getline(file,line)){
        istringstream iss(line);
        string key;
        iss>>key;

        if(key.empty() || key[0]=='#') 
        continue;

        if(key=="scheduler:"){
            string type;
            iss>>type;
            if(type=="SJF"){
                scheduler=make_unique<SJFScheduler>();
            } 
            else{
                scheduler=make_unique<FIFOScheduler>();
            }
        } 
        else if(key=="page_replacement:"){
            string type;
            iss>>type;
            mmu.setPolicy(type);
        } 
        else if(key=="process:"){
            uint32_t pid,at,bt,prio;
            string name;
            iss>>pid>>name>>at>>bt>>prio;

            auto p=make_shared<Process>(pid,name,at,bt,prio);

            uint32_t addr;
            while(iss>>addr){
                p->memoryAccesses.push_back(addr);
            }

            all_processes.push_back(p);
        }
    }
}



void Simulation::run(){
    Logger::log("SIMULATOR", "Starting simulation...");
    int completed=0;

    while(completed<all_processes.size()){
        cout<<"----------- Clock: "<<clock<<" -----------"<<endl;

        for(auto& p:all_processes){
            if(p->arrivalTime==clock){
                scheduler->addProcess(p);
                Logger::log("OS",p->name+" arrived.");
            }
        }

        if(!running_process){
            running_process=scheduler->getNextProcess();
            if(running_process){
                Logger::log("SCHEDULER","Dispatched "+running_process->name);
            }
        }

        if(running_process){
            cpu.execute(running_process, all_processes,mmu, clock);

            if(running_process->remainingTime==0){
                Logger::log("OS",running_process->name+" terminated.");
                running_process=nullptr;
                completed++;
            }
        } 
        else{
            Logger::log("CPU","Idle.");
        }

        clock++;

        if(clock>200){
            Logger::log("SIMULATOR","Timeout!");
            break;
        }
    }

    Logger::log("SIMULATOR","Simulation finished.");
}
