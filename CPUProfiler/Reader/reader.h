#ifndef READER_H_
#define READER_H_
#define CORE_NUMBER 4

#include "analyzer.h"


void readStatCPU(void);
void* readerService(void* arg);

typedef struct 
{
    unsigned long user_procs;
    unsigned long nice_procs;
    unsigned long system_procs;
    unsigned long idle_procs;
    unsigned long iowait_procs;
    unsigned long irq_procs;
    unsigned long softirq_procs;
    unsigned long steal_procs;
    unsigned long guest_procs;
    unsigned long guest_nice_procs;
    char core_name[5];
}SCoreProc;

extern SCoreProc FIFOBuffer[(CORE_NUMBER+1)*8];
extern uint8_t FIFOCounter;
#endif //READER_H_
