#ifndef ANALYZER_H_
#define ANALYZER_H_

#include <stdint.h>
#include "reader.h"

void getAwaitingData(void);
void analyzeData(void);
void calculateCoreUsage(uint8_t core);

extern uint8_t pBufferCounter;
#endif //ANALYZER_H_