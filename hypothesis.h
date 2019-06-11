#ifndef HYPOTHESIS_H
#define HYPOTHESIS_H

class Hypothesis {

public:
	enum H1Comparition {
		DIFFERENT = 1,
		LESS_THAN = 2,
		GREATER_THAN = 3
	};

	Hypothesis();
	double testAverage(double sampleAvg, double sampleStdDev, unsigned long sampleNumElements, double confidencelevel, double avg, H1Comparition comp);
	double testProportion(double sampleProp, unsigned long sampleNumElements, double confidencelevel, double prop, H1Comparition comp);
	double testVariance(double sampleVar, unsigned long sampleNumElements, double confidencelevel, double var, H1Comparition comp);

};

#endif /* HYPOTHESIS_H */
