#include <stdio.h>
#include "reader.h"

#define BUFFERLEN CORE_NUMBER*120

unsigned char cpuDataBuffer[BUFFERLEN];
int bufflen = 0;
SCoreProcs CoreData[CORE_NUMBER+1];

void readStatCPU(void)
{
    FILE *fp = fopen("/proc/stat", "rb");
    if(fp!=NULL)
    {
        for (int i = 0; i <= CORE_NUMBER; i++)
        {
            fscanf(fp,"%s%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu\n",
            CoreData[i].core_name,
            &CoreData[i].user_procs,
            &CoreData[i].nice_procs,
            &CoreData[i].system_procs,
            &CoreData[i].idle_procs,
            &CoreData[i].iowait_procs,
            &CoreData[i].irq_procs,
            &CoreData[i].softirq_procs,
            &CoreData[i].steal_procs,
            &CoreData[i].guest_procs,
            &CoreData[i].guest_nice_procs);
        }
        fclose(fp);
    }
    printf("\n%lu\n", CoreData[4].user_procs);
}