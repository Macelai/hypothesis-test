#include "hypothesis.h"
#include <math.h>
#include <boost/math/quadrature/gauss.hpp>
using namespace std;

Hypothesis::Hypothesis() = default;

double Hypothesis::testAverage(double sampleAvg, double sampleStdDev, unsigned long sampleNumElements,
                               double confidencelevel, double avg, H1Comparition comp) {
    using namespace boost::math::quadrature;

    printf("\n--- Test Average ---\n");

    double stdError = sampleStdDev / sqrt(sampleNumElements);
    printf("   # stdError=%f ", stdError);

    double z_calc = (sampleAvg - avg) / stdError;
    printf("# z_obs=%f ", z_calc);

    auto f = [](const double &x) {
        double constant = 1 / sqrt(2 * M_PI);
        double e = exp(pow(x, 2));
        double sqrtE = 1 / sqrt(e);
        return constant * sqrtE;
    };

    double Q = gauss<double, 10000>::integrate(f, -INFINITY, z_calc);

    double alpha = confidencelevel / 100;

    testHypothesisNull(comp, alpha, Q, H0Test::AVERAGE);
    return Q;

}

double Hypothesis::testProportion(double sampleProp, unsigned long sampleNumElements, double confidencelevel,
                                  double prop, H1Comparition comp) {
    using namespace boost::math::quadrature;

    printf("\n--- Test Proportion ---\n");

    double z_cal = (sampleProp - prop) / sqrt((prop * (1 - prop)) / sampleNumElements);
    printf("   # z_cal = %f\n", z_cal);

    auto f = [](const double &x) {
        double constant = 1 / sqrt(2 * M_PI);
        double e = exp(pow(x, 2));
        double sqrtE = 1 / sqrt(e);
        return constant * sqrtE;
    };

    double Q = gauss<double, 10000>::integrate(f, -INFINITY, z_cal);

    double alpha = confidencelevel / 100;

    testHypothesisNull(comp, alpha, Q, H0Test::PROPORTION);
    return Q;
}

//Não tenho certeza pela aproximacao a normal
double Hypothesis::testVariance(double sampleVar, unsigned long sampleNumElements, double confidencelevel,
                                double var, H1Comparition comp) {
    printf("\n--- Test Variance ---\n");

    using namespace boost::math::quadrature;

    double q_cal = ((sampleNumElements - 1) * sampleVar) / var;
    printf("# q_cal = %f\n", q_cal);

    auto f = [](const double &x) {
        double constant = 1 / sqrt(2 * M_PI);
        double e = exp(pow(x, 2));
        double sqrtE = 1 / sqrt(e);
        return constant * sqrtE;
    };

    double Q = gauss<double, 10000>::integrate(f, -INFINITY, q_cal);

    double alpha = confidencelevel / 100;
    double cl = 1 - alpha;

    if (comp == H1Comparition::DIFFERENT) {

        double alpha_half = alpha / 2;
        double z_critico = cl + alpha_half;

        if (q_cal > z_critico) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return Q;

    } else if (comp == H1Comparition::LESS_THAN) {

        if (-q_cal > -cl) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return Q;

    } else {

        if (q_cal > cl) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return Q;
    }
}

void Hypothesis::testHypothesisNull(H1Comparition comp, double alpha, double z_calc, H0Test test){

    double z_crit = 1 - alpha;
    printf("   # z_crit=%f ", z_crit);

    if (comp == H1Comparition::DIFFERENT) {

        double alpha_half = alpha / 2;
        double z_critico = z_crit + alpha_half;
        printf("# z_critico=%f ", z_critico);

        if (z_calc > z_critico or z_calc < alpha_half) {
            printf("\n   # REJEITAR H0 => %d NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", test, alpha);
        } else {
            printf("\n   # ACEITA H0 => %d NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", test, alpha);
        }

    } else if (comp == H1Comparition::LESS_THAN) {

        if (z_calc < alpha) {
            printf("\n   # REJEITAR H0 => %d NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", test, alpha);
        } else {
            printf("\n   # ACEITA H0 => %d NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", test, alpha);
        }

    } else {

        if (z_calc > z_crit) {
            printf("\n   # REJEITAR H0 => %d NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", test, alpha);
        } else {
            printf("\n   # ACEITA H0 => %d NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", test, alpha);
        }

    }
}