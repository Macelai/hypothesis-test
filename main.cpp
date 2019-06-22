#include "hypothesis.h"
#include <stdio.h>

int main() {

    Hypothesis *hypo = new Hypothesis();

    double sampleAvg = 120;
    double sampleStdDev = 20;
    unsigned long sampleNumElements = 20;
    double confidencelevel = 5;
    double avg = 115;

    double a = hypo->testAverage(sampleAvg, sampleStdDev, sampleNumElements, confidencelevel, avg,
                                 hypo->H1Comparition::DIFFERENT);
    printf("    # p=%f\n", a);

    double prop = hypo->testProportion(0.53, 50, 5, 0.6, hypo->H1Comparition::DIFFERENT);
    printf("    # p = %f\n", prop);

    double var = hypo->testVariance(18.3, 25, 10, 25, hypo->H1Comparition::LESS_THAN);
    printf("    # p = %f\n", var);

    return 0;
}
