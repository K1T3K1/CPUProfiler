#include "analyzer.h"

SCoreProc localCoreData[(CORE_NUMBER+1)*2];
float calculatedUsage[(CORE_NUMBER+1)];
float usageToPrinterBuffer[(CORE_NUMBER+1)*8];
uint8_t pBufferCounter = 0;

void getAwaitingData(void)
{
        for(int i = 0; i < (CORE_NUMBER+1)*2 ; i++)
        {
            localCoreData[i] = FIFOBuffer[i];
        }
        for(int i = 0; i < (CORE_NUMBER+1)*7;i++)
        {
            FIFOBuffer[i] = FIFOBuffer[i+CORE_NUMBER];
        }
        FIFOCounter -= (CORE_NUMBER+1)*2;
}

void analyzeData(void)
{
    if (FIFOCounter >= (CORE_NUMBER+1)*2)
    {
        getAwaitingData();
        for (int i = 0; i < CORE_NUMBER+1; i++)
        {
            calculateCoreUsage(i);
        }
        for(int i = 0; i <= CORE_NUMBER+1; i++)
        {
            if (FIFOCounter < (CORE_NUMBER+1)*8)
            {
                usageToPrinterBuffer[pBufferCounter] = calculatedUsage[i];
                pBufferCounter++;
            }
        }
    }
}

void calculateCoreUsage(uint8_t core)
{
    float prevIdle, Idle, prevActive, Active, prevTotal, Total, totald, idled;

    prevIdle = localCoreData[core].idle_procs + 
               localCoreData[core].iowait_procs;
    Idle = localCoreData[core+CORE_NUMBER+1].idle_procs + 
           localCoreData[core+CORE_NUMBER+1].iowait_procs;

    prevActive = localCoreData[core].user_procs +
                 localCoreData[core].nice_procs +
                 localCoreData[core].system_procs +
                 localCoreData[core].irq_procs +
                 localCoreData[core].softirq_procs +
                 localCoreData[core].steal_procs;
                 
    Active = localCoreData[core+CORE_NUMBER+1].user_procs +
             localCoreData[core+CORE_NUMBER+1].nice_procs +
             localCoreData[core+CORE_NUMBER+1].system_procs +
             localCoreData[core+CORE_NUMBER+1].irq_procs +
             localCoreData[core+CORE_NUMBER+1].softirq_procs +
             localCoreData[core+CORE_NUMBER+1].steal_procs;
    
    prevTotal = prevIdle + prevActive;
    Total = Idle + Active;

    totald = Total - prevTotal;
    idled = Idle - prevIdle;

    calculatedUsage[core] = (totald - idled)/totald;
}