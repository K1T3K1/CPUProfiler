#include "analyzer.h"
#include <stdio.h>
static SCoreProc localCoreData[(CORE_NUMBER + 1) * 2];
static double calculatedUsage[(CORE_NUMBER + 1)];
double usageToPrinterBuffer[(CORE_NUMBER + 1) * 8];
uint8_t pBufferCounter = 0;

/**
 * @brief reads data from queue buffer
 *        and moves data in queue
 * 
 */
void getAwaitingData(void)
{
    for (int i = 0; i < (CORE_NUMBER + 1) * 2; i++)
    {
        localCoreData[i] = FIFOBuffer[i];
    }
    for (int i = 0; i < (CORE_NUMBER + 1) * 8; i++)
    {
        FIFOBuffer[i] = FIFOBuffer[i + CORE_NUMBER + 1];
    }
    FIFOCounter -= (CORE_NUMBER + 1);
}

/**
 * @brief forces data reading from buffer 
 *        and iterates through each read core
 *        activating analyzer module for each individual core
 */
void *analyzeData(void *ptr __attribute__((unused)))
{

    if (FIFOCounter >= (CORE_NUMBER + 1) * 2)
    {
        getAwaitingData();
        for (int i = 0; i < CORE_NUMBER + 1; i++)
        {
            calculateCoreUsage(i);
        }
        for (int i = 0; i <= CORE_NUMBER + 1; i++)
        {
            if (FIFOCounter < (CORE_NUMBER + 1) * 8)
            {
                usageToPrinterBuffer[pBufferCounter] = calculatedUsage[i];
                pBufferCounter++;
            }
        }
    }
    return NULL;
}

/**
 * @brief calculates cpu usage using data read from SCoreProc struct
 * 
 * @param core which core we are calculating data for
 *             0 - cpu (summary)
 *             1 - cpu0 (1st core)
 *             2 - cpu1 (2nd core)
 *             etc
 */
void calculateCoreUsage(int core)
{
    double prevIdle, Idle, prevActive, Active, prevTotal, Total, totald, idled;
    prevIdle = localCoreData[core].idle_procs +
               localCoreData[core].iowait_procs;

    Idle = localCoreData[core + CORE_NUMBER + 1].idle_procs +
           localCoreData[core + CORE_NUMBER + 1].iowait_procs;

    prevActive = localCoreData[core].user_procs +
                 localCoreData[core].nice_procs +
                 localCoreData[core].system_procs +
                 localCoreData[core].irq_procs +
                 localCoreData[core].softirq_procs +
                 localCoreData[core].steal_procs;

    Active = localCoreData[core + CORE_NUMBER + 1].user_procs +
             localCoreData[core + CORE_NUMBER + 1].nice_procs +
             localCoreData[core + CORE_NUMBER + 1].system_procs +
             localCoreData[core + CORE_NUMBER + 1].irq_procs +
             localCoreData[core + CORE_NUMBER + 1].softirq_procs +
             localCoreData[core + CORE_NUMBER + 1].steal_procs;

    prevTotal = prevIdle + prevActive;
    Total = Idle + Active;

    totald = Total - prevTotal;
    idled = Idle - prevIdle;
    calculatedUsage[core] = ((totald - idled) / totald) * 100;
}
