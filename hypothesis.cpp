#include "hypothesis.h"
#include <math.h>
#include <boost/math/quadrature/gauss.hpp>
#include <boost/math/distributions/chi_squared.hpp>
using namespace std;

Hypothesis::Hypothesis() = default;

double Hypothesis::testAverage(double sampleAvg, double sampleStdDev, unsigned long sampleNumElements,
                               double confidencelevel, double avg, H1Comparition comp) {
    using namespace boost::math::quadrature;

    double stdError = sampleStdDev / sqrt(sampleNumElements);

    double z_calc = (sampleAvg - avg) / stdError;

    auto f = [](const double &x) {
        double constant = 1 / sqrt(2 * M_PI);
        double e = exp(pow(x, 2));
        double sqrtE = 1 / sqrt(e);
        return constant * sqrtE;
    };

    double Q = gauss<double, 10000>::integrate(f, -INFINITY, z_calc);

    double alpha = confidencelevel / 100;

    testHypothesisNull(comp, alpha, Q);
    return Q;

}

double Hypothesis::testProportion(double sampleProp, unsigned long sampleNumElements, double confidencelevel,
                                  double prop, H1Comparition comp) {
    using namespace boost::math::quadrature;

    double z_cal = ((sampleProp - prop) / sqrt((prop * (1 - prop)) / sampleNumElements));

    auto f = [](const double &x) {
        double constant = 1 / sqrt(2 * M_PI);
        double e = exp(pow(x, 2));
        double sqrtE = 1 / sqrt(e);
        return constant * sqrtE;
    };

    double Q = gauss<double, 10000>::integrate(f, -INFINITY, z_cal);

    double alpha = confidencelevel / 100;

    testHypothesisNull(comp, alpha, Q);
    return Q;
}

double Hypothesis::testVariance(double sampleVar, unsigned long sampleNumElements, double confidencelevel,
                                double var, H1Comparition comp) {
    using namespace boost::math::quadrature;

    int df = (int)sampleNumElements - 1;
    double chi_cal = (df * sampleVar) / var;
    //printf("chi_cal %f\n", chi_cal);

    double chi = ChiSquare(chi_cal, df);
    //printf("chi %f\n", chi);

    double alpha = confidencelevel / 100;

    double value_calc = 1 - chi;
    //printf("value_calc %f", value_calc);

    testHypothesisNull(comp, alpha, value_calc);
    return chi;
}

void Hypothesis::testHypothesisNull(H1Comparition comp, double alpha, double value_calc){

    double value_critical = 1 - alpha;

    if (comp == H1Comparition::DIFFERENT) {

        double value_inf = alpha / 2;
        double value_sup = value_critical + value_inf;

        if (value_calc > value_sup or value_calc < value_inf) {
            printf("\n   # REJECT H0 => NOT EQUAL WITH %0.4f OF CONFIDENCE LEVEL\n\n", alpha);
        } else {
            printf("\n   # ACCEPT H0 => EQUAL WITH %0.4f OF CONFIDENCE LEVEL\n\n", alpha);
        }

    } else if (comp == H1Comparition::LESS_THAN) {

        if (value_calc < alpha) {
            printf("\n   # REJECT H0 => LESS THAN WITH %0.4f OF CONFIDENCE LEVEL\n\n", alpha);
        } else {
            printf("\n   # ACCEPT H0 => NOT LESS THAN WITH %0.4f OF CONFIDENCE LEVEL\n\n", alpha);
        }

    } else {

        if (value_calc > value_critical) {
            printf("\n   # REJECT H0 => GREATER THAN WITH %0.4f OF CONFIDENCE LEVEL\n\n", alpha);
        } else {
            printf("\n   # ACCEPT H0 => NOT GREATER THAN WITH %0.4f OF CONFIDENCE LEVEL\n\n", alpha);
        }

    }
}

double Hypothesis::ChiSquare(double x, int df) {
    // Reference: https://jamesmccaffrey.wordpress.com/2010/11/01/programmatically-computing-chi-square-critical-values
    // x = a computed chi-square value
    // df = degrees of freedom
    using namespace boost::math::quadrature;

    if (x <= 0.0 || df < 1) {
        printf("parameter x must be positive and parameter df must be 1 or greater");
    };

    double a = 0; // 299 variable names
    double y = 0;
    double s = 0;
    double z = 0;
    double e = 0;
    double c;

    bool even; // is df even?

    a = 0.5 * x;
    if (df % 2 == 0) even = true; else even = false;

    if (df > 1) y = Exp(-a); // ACM update remark (4)

    auto f = [](const double &x) {
        double constant = 1 / sqrt(2 * M_PI);
        double ex = exp(pow(x, 2));
        double sqrtE = 1 / sqrt(ex);
        return constant * sqrtE;
    };

    if (even) s = y; else s = 2.0 * gauss<double, 10000>::integrate(f, -INFINITY, -sqrt(x));

    if (df > 2)
    {
        x = 0.5 * (df - 1.0);
        if (even) z = 1.0; else z = 0.5;
        if (a > 40.0) // ACM remark (5)
        {
            if (even) e = 0.0; else e = 0.5723649429247000870717135; // log(sqrt(pi))
            c = log(a); // log base e
            while (z <= x)
            {
                e = log(z) + e;
                s = s + Exp(c * z - a - e); // ACM update remark (6)
                z = z + 1.0;
            }
            return s;
        } // a > 40.0
        else
        {
            if (even) e = 1.0; else e = 0.5641895835477562869480795 / sqrt(a); // (1 / sqrt(pi))
            c = 0.0;
            while (z <= x)
            {
                e = e * (a / z); // ACM update remark (7)
                c = c + e;
                z = z + 1.0;
            }
            return c * y + s;
        }
    }
    else
    {
        return s;
    }
}

double Hypothesis::Exp(double x) { // ACM update remark (3)
    if (x < -40.0) // 40.0 is a magic number. ACM update remark (8)
        return 0.0;
    else
        return exp(x);
}
