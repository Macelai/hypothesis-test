#include "hypothesis.h"
#include <math.h>
#include <boost/math/quadrature/gauss.hpp> 
	
Hypothesis::Hypothesis(){
		
}

double Hypothesis::testAverage(double sampleAvg, double sampleStdDev, unsigned long sampleNumElements, double confidencelevel, double avg, H1Comparition comp) {
	using namespace boost::math::quadrature;

	auto f = [](const double& t) { return (1.0 / sqrt (2 * M_PI)) * exp(pow(-t,2) / 2); };

	double Q = gauss<double, 100>::integrate(f, 0, 1);

	return Q;
}

