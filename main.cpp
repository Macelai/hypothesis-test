#include "hypothesis.h"
#include <stdio.h>

int main() {
	Hypothesis* hypo = new Hypothesis();
	double b = 0;
	double c = 0.5;
	double a = hypo->testAverage(b, c, b, b, b, hypo->H1Comparition::DIFFERENT);
	printf("%f", a);
	return 0;
}
