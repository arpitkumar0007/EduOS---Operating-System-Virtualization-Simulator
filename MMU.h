#ifndef MMU_H
#define MMU_H

#include "Process.h"
#include "PageReplacement.h"

class MMU{
    vector<bool>freeFrames;
    const uint32_t pageSize;
    const uint32_t num_frames;
    unique_ptr<PageReplacementPolicy> replacementPolicy;

public:
    MMU(uint32_t memSize, uint32_t pgSize);
    void setPolicy(const string& policyName);
    void translateAddress(shared_ptr<Process> p, vector<shared_ptr<Process>>& all_processes, uint32_t vAddr, uint32_t clock);

};
#endif