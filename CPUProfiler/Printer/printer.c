#include "printer.h"
#include "stdio.h"

/**
 * @brief prints newest CPU Usage data to terminal
 */
void *printUsage(void* ptr __attribute__((unused)))
{
    for (int i = 0; i < CORE_NUMBER + 1; i++)
    {
        if (i == 0)
        {
            printf("cpu %f%% \n", usageToPrinterBuffer[i]);
        }
        else
        {
            printf("cpu%d %f%% \n", (i - 1), usageToPrinterBuffer[i]);
        }
    }
    return NULL;
}
