#include "hypothesis.h"
#include <math.h>
	
Hypothesis::Hypothesis(){
		
}

double Hypothesis::testAverage(double sampleAvg, double sampleStdDev, unsigned long sampleNumElements, double confidencelevel, double avg, H1Comparition comp) {
		double standardDeviationDistribuition = sampleStdDev / sqrt(sampleNumElements);
		return sampleStdDev; 
}

