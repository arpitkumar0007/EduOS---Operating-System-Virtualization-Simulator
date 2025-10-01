#include "MMU.h"
#include "Logger.h"


MMU::MMU(uint32_t memSize, uint32_t pgSize) :pageSize(pgSize),num_frames(memSize/pgSize){

    freeFrames.resize(num_frames,true);
    setPolicy("FIFO"); // this is default

}


void MMU::setPolicy(const string& policyName){

    if(policyName=="LRU"){
        replacementPolicy = make_unique<LRUPageReplacement>();
    }
    else{
        replacementPolicy = make_unique<FIFOPageReplacement>();
    }

}


int findFreeFrame(vector<bool>& frames){
    for(int i=0;i<frames.size();i++){
        if(frames[i]){
            return i;
        }
    }

    return -1;
}



void MMU::translateAddress(shared_ptr<Process> p, vector<shared_ptr<Process>>& all_processes,uint32_t vAddr, uint32_t clock){
    uint32_t vpn=vAddr/pageSize;


    if(!p->pageTable.count(vpn) || !p->pageTable[vpn].pres){

        Logger::log("OS","PAGE FAULT for Page "+to_string(vpn)+" in "+p->name);

        int frame=findFreeFrame(freeFrames);

        if(frame==-1){
            uint32_t victim_vpn=replacementPolicy->selectVictim(all_processes,num_frames);

            for(const auto& proc:all_processes){
                if(proc->pageTable.count(victim_vpn) && proc->pageTable[victim_vpn].frame_num!=-1){
                    frame=proc->pageTable[victim_vpn].frame_num;
                    Logger::log("OS","No free frames. Swapping OUT Page "+to_string(victim_vpn)+" from process "+proc->name);
                    break; 
                }
            }
        }

        Logger::log("OS","Swapping IN Page "+to_string(vpn)+" to Frame "+to_string(frame));

        p->pageTable[vpn].pres =true;
        p->pageTable[vpn].frame_num=frame;

        freeFrames[frame]=false;
    }


    p->pageTable[vpn].last_used_time=clock;

    uint32_t phyAddr=p->pageTable[vpn].frame_num * pageSize+(vAddr%pageSize);

    Logger::log("MMU","VAddr "+to_string(vAddr)+" -> PAddr "+to_string(phyAddr));
}
