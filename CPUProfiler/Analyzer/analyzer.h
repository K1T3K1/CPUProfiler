#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <stdint.h>
#include "reader.h"

void getAwaitingData(void);
void* analyzeData(void* arg);
void calculateCoreUsage(uint8_t core);

extern float usageToPrinterBuffer[(CORE_NUMBER+1)*8];
extern uint8_t pBufferCounter;
#endif //ANALYZER_H_
