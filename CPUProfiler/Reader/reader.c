#include <stdio.h>
#include "reader.h"

#define BUFFERLEN 300

unsigned char cpuDataBuffer[BUFFERLEN];
int bufflen = 0;

void readStatCPU(void)
{
    FILE *fp = fopen("/proc/stat", "rb");
    if(fp!=NULL)
    {
        while (bufflen != BUFFERLEN)
        {
            bufflen = fread(cpuDataBuffer, 1, BUFFERLEN, fp);
        }
        fclose(fp);
    }

    for(int i = 0; i<BUFFERLEN; i++)
    {
        printf("%c", cpuDataBuffer[i]);
    }
}