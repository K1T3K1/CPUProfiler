#include <stdio.h>
#include "reader.h"

SCoreProc CoreData[CORE_NUMBER+1];
SCoreProc FIFOBuffer[(CORE_NUMBER+1)*8];
uint8_t FIFOCounter = 0;

/**
 * @brief reads data from /proc/stat system file
 *        and places it in a SCoreProc CoreData
 *        where each array element equals
 *        one CPU Core and the first element is
 *        all Cores summarized
 */
void readStatCPU(void)
{
    FILE *fp = fopen("/proc/stat", "rb");
    if(fp!=NULL)
    {
        for (int i = 0; i <= CORE_NUMBER; i++)
        {
            fscanf(fp,"%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu\n",
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
        printf("%lu\n", CoreData[0].user_procs);
    }
}

/**
 * @brief transfers data from CoreData array
 *        into a Queue which serves as a
 *        data source for Analyzer module
 */
void readerService(void)
{
    readStatCPU();
    for(int i = 0; i <= CORE_NUMBER+1; i++)
    {
        if (FIFOCounter < (CORE_NUMBER+1)*8)
        {
            FIFOBuffer[FIFOCounter] = CoreData[i];
            FIFOCounter++;
        }
    }
}