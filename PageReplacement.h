#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H


#include "Process.h"


class PageReplacementPolicy{
public:
    virtual ~PageReplacementPolicy()=default;
    virtual uint32_t selectVictim(vector<shared_ptr<Process>>& all_processes,uint32_t num_frames)=0;
};



class FIFOPageReplacement : public PageReplacementPolicy{
private:
    uint32_t frame_pointer=0;
public:
    uint32_t selectVictim(vector<shared_ptr<Process>>& all_processes,uint32_t num_frames) override{

        uint32_t victim_frame=frame_pointer;
        uint32_t victim_page=-1;

        for(auto& p:all_processes){
            for(auto& pair:p->pageTable){
                if(pair.second.pres && pair.second.frame_num==victim_frame){
                    victim_page=pair.first;
                    pair.second.pres=false;
                    goto found_victim;
                }
            }
        }

    found_victim:
        frame_pointer=(frame_pointer+1)%num_frames;
        return victim_page;
    }
};



class LRUPageReplacement: public PageReplacementPolicy{
public:
    uint32_t selectVictim(vector<shared_ptr<Process>>& all_processes,uint32_t num_frames) override{

        uint32_t victim_page=-1;
        shared_ptr<Process> victim_process=nullptr;

        uint32_t min_time=-1;

        for(const auto& p:all_processes){
            for(const auto& pair:p->pageTable){
                if(pair.second.pres){
                    if(victim_page==-1 || pair.second.last_used_time<min_time){
                        min_time=pair.second.last_used_time;
                        victim_page=pair.first;
                        victim_process=p;
                    }
                }
            }
        }

        if(victim_process){
            victim_process->pageTable[victim_page].pres=false;
        }

        return victim_page;
    }
};


#endif