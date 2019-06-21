/* References: 
    - Curso de Planejamento Experimental - FEMEC - UFU
    - Curso de estatísitca, 4 ed. 
*/

#include "hypothesis.h"
#include <math.h>
//#include <boost/math/quadrature/gauss.hpp>
#include "../boost_1_66_0/boost/math/quadrature/gauss.hpp"

Hypothesis::Hypothesis() = default;

double Hypothesis::testAverage(double sampleAvg, double sampleStdDev, unsigned long sampleNumElements, 
                                double confidencelevel, double avg, H1Comparition comp) {
    printf("\n--- Test Average ---\n");

    using namespace boost::math::quadrature;

    double stdError = sampleStdDev / sqrt(sampleNumElements);
    printf("# stdError = %f\n", stdError);

    double z_obs = (sampleAvg - avg) / stdError;
    printf("# z_obs = %f\n", z_obs);

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
            printf("    # REJEITAR H0 => MEDIA NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return Q;

    } else if (comp == H1Comparition::LESS_THAN) {

        if (-z_obs > -cl ) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return -Q;

    } else {

        if (z_obs > cl) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return Q;
    }
}

//Nao tenho certeza pela aproximacao a normal
double Hypothesis::testProportion(double sampleProp, unsigned long sampleNumElements, double confidencelevel, 
                                    double prop, H1Comparition comp) {
    printf("\n--- Test Proportion ---\n");

    using namespace boost::math::quadrature;

    double z_cal = (sampleProp-prop)/sqrt((prop*(1-prop))/sampleNumElements);
    printf("# z_cal = %f\n", z_cal);

    auto f = [](const double& x) {
        double constant = 1 / sqrt(2 * M_PI);
        double e = exp(pow(x, 2));
        double sqrtE = 1 / sqrt(e);
        return constant * sqrtE;
    };

    double Q = gauss<double, 10000>::integrate(f, -INFINITY, z_cal);

    double alpha = confidencelevel/100;
    double cl = 1 - alpha;

    if (comp == H1Comparition::DIFFERENT) {

        double alpha_half = alpha/2;
        double z_critico = cl + alpha_half;

        if (z_cal > z_critico) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return Q;

    } else if (comp == H1Comparition::LESS_THAN) {

        if (-z_cal > -cl ) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return -Q;

    } else {

        if (z_cal > cl) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return Q;
    }
}

//Não tenho certeza pela aproximacao a normal
double Hypothesis::testVariance(double sampleVar, unsigned long sampleNumElements, double confidencelevel, 
                                double var, H1Comparition comp) {
    printf("\n--- Test Variance ---\n");

    using namespace boost::math::quadrature;

    double q_cal = ((sampleNumElements-1)*sampleVar)/var;
    printf("# q_cal = %f\n", q_cal);

    auto f = [](const double& x) {
        double constant = 1 / sqrt(2 * M_PI);
        double e = exp(pow(x, 2));
        double sqrtE = 1 / sqrt(e);
        return constant * sqrtE;
    };

    double Q = gauss<double, 10000>::integrate(f, -INFINITY, q_cal);

    double alpha = confidencelevel/100;
    double cl = 1 - alpha;

    if (comp == H1Comparition::DIFFERENT) {

        double alpha_half = alpha/2;
        double z_critico = cl + alpha_half;

        if (q_cal > z_critico) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return Q;

    } else if (comp == H1Comparition::LESS_THAN) {

        if (-q_cal > -cl ) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh MAIOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return -Q;

    } else {

        if (q_cal > cl) {
            printf("    # REJEITAR H0 => MEDIA NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        } else {
            printf("    # ACEITA H0 => MEDIA NAO Eh MENOR IGUAL A %0.4f NIVEL DE SIGNIFICANCIA\n", alpha);
        }

        return Q;
    }
}

