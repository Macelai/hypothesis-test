#include "hypothesis.h"
#include <math.h>
#include <boost/math/quadrature/gauss.hpp>

Hypothesis::Hypothesis() = default;

double
Hypothesis::testAverage(double sampleAvg, double sampleStdDev, unsigned long sampleNumElements, double confidencelevel,
                        double avg, H1Comparition comp) {
    using namespace boost::math::quadrature;

    double stdError = sampleStdDev / sqrt(sampleNumElements);
    printf("   # stdError=%f ", stdError);

    double z_obs = (sampleAvg - avg) / stdError;
    printf("# z_obs=%f ", z_obs);

    auto f = [](const double& x) {
        double constant = 1 / sqrt(2 * M_PI);
        double e = exp(pow(x, 2));
        double sqrtE = 1 / sqrt(e);
        return constant * sqrtE;
    };

    double Q = gauss<double, 10000>::integrate(f, -INFINITY, z_obs);

    double alpha = confidencelevel/100;
    double cl = 1 - alpha;

    if (comp == H1Comparition::DIFFERENT) {

        double alpha_half = alpha/2;
        double z_critico = cl + alpha_half;

        if (z_obs > z_critico) {
            printf("\n   # REJEITAR H0 => MEDIA NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", alpha);
        } else {
            printf("\n   # ACEITA H0 => MEDIA NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", alpha);
        }

        return Q;

    } else if (comp == H1Comparition::LESS_THAN) {

        if (-z_obs > -cl ) {
            printf("\n   # REJEITAR H0 => MEDIA NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", alpha);
        } else {
            printf("\n   # ACEITA H0 => MEDIA NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", alpha);
        }

        return -Q;

    } else {

        if (z_obs > cl) {
            printf("\n   # REJEITAR H0 => MEDIA NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", alpha);
        } else {
            printf("\n   # ACEITA H0 => MEDIA NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA", alpha);
        }

        return Q;
    }

}
