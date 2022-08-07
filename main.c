#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "unistd.h"
#include "pthread.h"
#include <stdlib.h>
#include "analyzerTests.h"

int main()
{
    pthread_t TReader, TAnalyzer, TPrinter, TAnalyzerTest, TMoveFIFO;
    while (1)
    {
        pthread_create(&TReader, NULL, readerService, NULL);
        pthread_join(TReader, NULL);
        sleep(1);
        pthread_create(&TReader, NULL, readerService, NULL);
        pthread_join(TReader, NULL);
        pthread_create(&TAnalyzer, NULL, analyzeData, NULL);
        pthread_join(TAnalyzer, NULL);
        pthread_create(&TPrinter, NULL, printUsage, NULL);
        pthread_join(TPrinter, NULL);
        sleep(3);
        system("@cls||clear");
    }
}
