#ifndef READER_H_
#define READER_H_
#define CORE_NUMBER 4


void readStatCPU(void);

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
}SCoreProcs;

extern SCoreProcs CoreData[CORE_NUMBER+1];

#endif //READER_H_