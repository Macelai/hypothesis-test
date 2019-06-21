#include "hypothesis.h"
#include <stdio.h>

int main() {
    Hypothesis *hypo = new Hypothesis();

    double sampleAvg = 118;
    double sampleStdDev = 20;
    unsigned long sampleNumElements = 20;
    double confidencelevel = 5;
    double avg = 115;

    printf("-> Test Average \n");
    double a = hypo->testAverage(sampleAvg, sampleStdDev, sampleNumElements, confidencelevel, avg,
                                 hypo->H1Comparition::DIFFERENT);
    printf("\n   # p=%f", a);



    return 0;
}


