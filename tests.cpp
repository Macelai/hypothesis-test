#include "hypothesis.h"
#include <stdio.h>
#include <math.h>

//All tests were previously calculed by hand.
class Tests {
	public:
	void check_test(double target, double result) {
		if(abs(target-result) < 0.009) {
			printf("-- TEST OK!--\n\n");
		} else {
			printf("-- TEST NOT OK!--\n\n");
		}
	}

	void test_AvgTest1() {

		double expected_value = 0.7486;

		Hypothesis *hypo = new Hypothesis();

		printf("--- Average Test 1 ---\n");

		double sampleAvg = 118;
		double sampleStdDev = 20;
		unsigned long sampleNumElements = 20;
		double confidencelevel = 5;
		double avg = 115;

		printf("- expected result: %f\n", expected_value);
		printf("- comparition: DIFFERENT\n");
		printf("- sample average: %f\n", sampleAvg);
		printf("- sample standard deviation: %f\n", sampleStdDev);
		printf("- sample number of elements: %lu\n", sampleNumElements);
		printf("- confidence level: %f\n", (confidencelevel/100));
		printf("- average: %f\n", avg);

		double a = hypo->testAverage(sampleAvg, sampleStdDev, sampleNumElements, confidencelevel, avg,
									 hypo->H1Comparition::DIFFERENT);

		printf("--- p-value = %f\n", a);

		check_test(expected_value, a);

		delete(hypo);
	}

	void test_AvgTest2() {

		double expected_value = 0.9830;

		Hypothesis *hypo = new Hypothesis();

		printf("--- Average Test 2 ---\n");

		double sampleAvg = 118;
		double sampleStdDev = 20;
		unsigned long sampleNumElements = 200;
		double confidencelevel = 5;
		double avg = 115;

		printf("- expected result: %f\n", expected_value);
		printf("- comparition: DIFFERENT\n");
		printf("- sample average: %f\n", sampleAvg);
		printf("- sample standard deviation: %f\n", sampleStdDev);
		printf("- sample number of elements: %lu\n", sampleNumElements);
		printf("- confidence level: %f\n", (confidencelevel/100));
		printf("- average: %f\n", avg);

		double a = hypo->testAverage(sampleAvg, sampleStdDev, sampleNumElements, confidencelevel, avg,
									 hypo->H1Comparition::DIFFERENT);

		printf("--- p-value = %f\n", a);

		check_test(expected_value, a);

		delete(hypo);
	}

	void test_PropTest1() {

		double expected_value = (1-0.999289);

		Hypothesis *hypo = new Hypothesis();

		printf("--- Proportion Test 1 ---\n");

		double sampleProp = 0.53;
		unsigned long sampleNumElements = 500;
		double confidencelevel = 5;
		double prop = 0.6;

		printf("- expected result: %f\n", expected_value);
		printf("- comparition: LESS_THAN\n");
		printf("- sample average: %f\n", sampleProp);
		printf("- sample number of elements: %lu\n", sampleNumElements);
		printf("- confidence level: %f\n", (confidencelevel/100));
		printf("- average: %f\n", prop);

		double p = hypo->testProportion(sampleProp, sampleNumElements, confidencelevel, prop,
										hypo->H1Comparition::LESS_THAN);

		printf("--- p-value = %f\n", p);

		check_test(expected_value, p);

		delete(hypo);
	}

	void test_PropTest2() {

		double expected_value = (1-0.9222);

		Hypothesis *hypo = new Hypothesis();

		printf("--- Proportion Test 2 ---\n");

		double sampleProp = 0.53;
		unsigned long sampleNumElements = 100;
		double confidencelevel = 5;
		double prop = 0.6;

		printf("- expected result: %f\n", expected_value);
		printf("- comparition: LESS_THAN\n");
		printf("- sample average: %f\n", sampleProp);
		printf("- sample number of elements: %lu\n", sampleNumElements);
		printf("- confidence level: %f\n", (confidencelevel/100));
		printf("- average: %f\n", prop);

		double p = hypo->testProportion(sampleProp, sampleNumElements, confidencelevel, prop,
										hypo->H1Comparition::LESS_THAN);

		printf("--- p-value = %f\n", p);

		check_test(expected_value, p);

		delete(hypo);
	}

	void test_VarTest1() {

		double expected_value = (1-0.6879);

		Hypothesis *hypo = new Hypothesis();

		printf("--- Variance Test 1 ---\n");

		double sampleVar = 28;
		unsigned long sampleNumElements = 25;
		double confidencelevel = 10;
		double var = 25;

		printf("- expected result: %f\n", expected_value);
		printf("- comparition: GREATER_THAN\n");
		printf("- sample variance: %f\n", sampleVar);
		printf("- sample number of elements: %lu\n", sampleNumElements);
		printf("- confidence level: %f\n", (confidencelevel/100));
		printf("- variance: %f\n", var);

		double p = hypo->testVariance(sampleVar, sampleNumElements, confidencelevel, var,
										hypo->H1Comparition::GREATER_THAN);

		printf("--- p-value = %f\n", p);

		check_test(expected_value, p);

		delete(hypo);
	}

	void test_VarTest2() {

		double expected_value = (1-0.9678);

		Hypothesis *hypo = new Hypothesis();

		printf("--- Variance Test 2 ---\n");

		double sampleVar = 28;
		unsigned long sampleNumElements = 500;
		double confidencelevel = 10;
		double var = 25;

		printf("- expected result: %f\n", expected_value);
		printf("- comparition: GREATER_THAN\n");
		printf("- sample variance: %f\n", sampleVar);
		printf("- sample number of elements: %lu\n", sampleNumElements);
		printf("- confidence level: %f\n", (confidencelevel/100));
		printf("- variance: %f\n", var);

		double p = hypo->testVariance(sampleVar, sampleNumElements, confidencelevel, var,
										hypo->H1Comparition::GREATER_THAN);

		printf("--- p-value = %f\n", p);

		check_test(expected_value, p);

		delete(hypo);
	}
	};
