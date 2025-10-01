#include "Simulation.h"

int main(int argc,char* argv[]){
    string scenario_file="scenarios/fifo_demo.txt";
    if(argc>1){
        scenario_file=argv[1];
    }

    Simulation sim(16384,4096); //16KB RAM, 4KB Pages => Total 4 pages(or frames)

    sim.loadScenario(scenario_file);
    sim.run();

    return 0;
}