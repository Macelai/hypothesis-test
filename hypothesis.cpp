#include "hypothesis.h"
#include <math.h>
#include <boost/math/quadrature/gauss.hpp> 
	
Hypothesis::Hypothesis(){
		
}

double Hypothesis::testAverage(double sampleAvg, double sampleStdDev, unsigned long sampleNumElements, double confidencelevel, double avg, H1Comparition comp) {
	using namespace boost::math::quadrature;

	double stdError = sampleStdDev / sqrt(sampleNumElements);
	printf(" stdError=%f", stdError);

	double t = (sampleAvg - avg) / stdError;
	printf(" t=%f", t);

	auto f = [](const double& t) {
		double constant = 1 / sqrt(2 * M_PI);
		double e = exp(pow(t, 2));
		double sqrtE = 1 / sqrt(e);
		return constant * sqrtE;
	};

	double Q = gauss<double, 10000>::integrate(f, -1000000, t);
	return Q;
}

