#include "hypothesis.h"
#include <stdio.h>

int main() {
	Hypothesis* hypo = new Hypothesis();
	double a = hypo->testAverage(0.81, 0.0031, 41, 10, 0.787, hypo->H1Comparition::DIFFERENT);
	printf(" p: %f", a);
	return 0;
}
