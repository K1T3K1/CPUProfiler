#ifndef READER_H_
#define READER_H_
#define CORE_NUMBER 4

#include "analyzer.h"


void readStatCPU(void);
void* readerService(void* ptr __attribute__((unused)));

typedef struct 
{
    double user_procs;
    double nice_procs;
    double system_procs;
    double idle_procs;
    double iowait_procs;
    double irq_procs;
    double softirq_procs;
    double steal_procs;
    double guest_procs;
    double guest_nice_procs;
    char core_name[5];
}SCoreProc;

extern SCoreProc FIFOBuffer[(CORE_NUMBER+1)*8];
extern uint8_t FIFOCounter;
#endif //READER_H_
