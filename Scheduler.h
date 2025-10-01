#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"


//abstract base class for all the schedulers 
class Scheduler{
public:

    virtual ~Scheduler()=default;

    virtual void addProcess(shared_ptr<Process>p)=0; // shared_ptr is smart pointer that manages memory automatically
    virtual shared_ptr<Process> getNextProcess()=0;

};


// FIFO scheduler
class FIFOScheduler : public Scheduler{
private:
    queue<shared_ptr<Process>>q;

public:
    void addProcess(shared_ptr<Process>  p) override{
        q.push(p);
    }

    shared_ptr<Process> getNextProcess() override{
        if(q.empty()){
            return nullptr;
        }

        auto p=q.front();
        q.pop();

        return p;
    }

};


// sjf scheduler
class SJFScheduler : public Scheduler{
private:
    vector<shared_ptr<Process>> list;

public:
    void addProcess(shared_ptr<Process> p) override{
        list.push_back(p);
    }

    shared_ptr<Process> getNextProcess()  override{
        if(list.empty()){
            return nullptr;
        }

        auto it=min_element(list.begin(),list.end(),[](const auto &a,const auto&b){return a->burstTime<b->burstTime;});

        auto p=*it;

        list.erase(it);

        return p;
    }
};



#endif