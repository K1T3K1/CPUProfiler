#include "analyzer.h"
#include <assert.h>
#include <stdio.h>
#include "reader.h"

static SCoreProc localCoreData[2];
void getOverallUsage(void)
{
    localCoreData[0] = FIFOBuffer[0];
    localCoreData[1] = FIFOBuffer[CORE_NUMBER+1];
}

double calculateCoreUsageTest()
{
    getOverallUsage();
    double prevIdle, Idle, prevActive, Active, prevTotal, Total, totald, idled;
    prevIdle = localCoreData[0].idle_procs + 
               localCoreData[0].iowait_procs;

    Idle = localCoreData[1].idle_procs + 
           localCoreData[1].iowait_procs;

    prevActive = localCoreData[0].user_procs +
                 localCoreData[0].nice_procs +
                 localCoreData[0].system_procs +
                 localCoreData[0].irq_procs +
                 localCoreData[0].softirq_procs +
                 localCoreData[0].steal_procs;
                 
    Active = localCoreData[1].user_procs +
             localCoreData[1].nice_procs +
             localCoreData[1].system_procs +
             localCoreData[1].irq_procs +
             localCoreData[1].softirq_procs +
             localCoreData[1].steal_procs;
    
    prevTotal = prevIdle + prevActive;
    Total = Idle + Active;

    totald = Total - prevTotal;
    idled = Idle - prevIdle;
    return ((totald - idled)/totald)*100;
}

void* analyzerTest(void* arg __attribute__((unused)))
{
    //assert(calculateCoreUsageTest() == usageToPrinterBuffer[0]);
    return NULL;
}
