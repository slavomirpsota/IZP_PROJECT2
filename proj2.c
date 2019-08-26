#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double taylor_log(double x, unsigned int n) {

	double vysledok;
	unsigned int pocetClenov = n;
	unsigned int i;
	unsigned int j;
	double powerx;

    if (x > 1)
    {
        vysledok = 0;

        for (i = 1; i <= pocetClenov; i++)
        {
            powerx = (x - 1)/x; /*powerx- nahrada za citatel*/
            for (j = 1; j < i; j++) /*mocnim citatela*/
            {
                powerx *= powerx;
            }
            vysledok += powerx/i; /*delim citatela poctom clenov a priradzujem do vysledku*/
        }

    }

    else {
        vysledok = x - 1;
        for (i = 2; i <= pocetClenov; i++)
        {
            powerx = x - 1;
            for (j = 1; j < i; j++)   /*mocnim citatela na mocninu ktoru potrebujem*/
            {
                powerx *= powerx; 	/*pouzit predchadzajuci clen namiesto nasobenia od nuly*/
            }

            if (i % 2 == 0) /*testujem, ci je clen parny alebo neparny*/
            {
                vysledok -= powerx/i;
            }

            else
            {
                vysledok += powerx/i;
            }
        }
    }
    printf("taylor_log(%f) = %f\n",x,vysledok);
    return vysledok;
}

double cfrac_log(double x, unsigned int n)
{
	unsigned int pocetClenov = n;
	int i = pocetClenov;
    double clen = (x-1)/(x+1);
    double vysledok = 0;
    double koeficient;
    double predCislo;

    for (i = pocetClenov; i > 1; i--)
    {
        koeficient = (double) (i-1)*(i-1); /*koeficient pred premennou*/
        predCislo = (double) i*2-1; /*pocitam cislo pred zlomkom*/
        vysledok = koeficient * clen * clen / (predCislo - vysledok); /*samotny vypocet*/
    }

    vysledok = 2 * clen / (1-koeficient);
    printf("cf_log(%f) = %f\n",x,vysledok);
    return vysledok;
}



unsigned int taylor_iter(double min, double max, double eps) {

    double refMinLog = log(min);
    double refMaxLog = log(max);

    double actualMinLog = taylor_log(min, 1);
    double actualMaxLog = taylor_log(max, 1);

    unsigned int minIteracie = 1;
    unsigned int maxIteracie = 1;

    while (fabs(actualMinLog - refMinLog) > eps)
    {
    	minIteracie++;
        actualMinLog = taylor_log(min, minIteracie);
    }

    while (fabs(actualMaxLog - refMaxLog) > eps)
    {
        maxIteracie++;
        actualMaxLog = taylor_log(max, maxIteracie);
    }

    return minIteracie > maxIteracie ? minIteracie : maxIteracie;
}


unsigned int cfrac_iter(double min, double max, double eps) {

    double reference_min_log = log(min);
    double reference_max_log = log(max);

    double actual_min_log = cfrac_log(min, 1);
    double actual_max_log = cfrac_log(max, 1);

    unsigned int min_iteration = 1;
    unsigned int max_iteration = 1;

    while (fabs(actual_min_log - reference_min_log) > eps)
    {
        min_iteration++;
        actual_min_log = cfrac_log(min, min_iteration);
    }

    while (fabs(actual_max_log - reference_max_log) > eps)
    {
        max_iteration++;
        actual_max_log = cfrac_log(max, max_iteration);
    }

    return min_iteration > max_iteration ? min_iteration : max_iteration;
}



int main(int argc, const char * argv[])
{
 double x, min, max, eps;
 unsigned int n;

    if (argc == 4)
		{
         processLogParameters(argv, &x, &n);
         printf("log(%g) = %.12g\n",x ,log(x));
         printf("cf_log(%g) = %.12g\n",x ,cfrac_log(x, n));
         printf("taylor_log(%g) = %.12g\n",x ,taylor_log(x, n));
		}
	else if (argc == 5)
		{
         processIterParameters(argv, &min, &max, &eps);
         printf("log(%g) = %.12g\n",min ,log(min));
         printf("log(%g) = %.12g\n",max ,log(max));
         unsigned int min_iterations = cfrac_iter(min, max, eps);
         printf("continued fraction iterations = %u\n", min_iterations);
         printf("cf_log(%g) = %.12g\n",min , cfrac_log(min, min_iterations));
         printf("cf_log(%g) = %.12g\n",max , cfrac_log(max, min_iterations));
         min_iterations = taylor_iter(min, max, eps);
         printf("taylor polynomial iterations = %u\n", min_iterations);
         printf("taylor_log(%g) = %.12g\n",min , taylor_log(min, min_iterations));
         printf("taylor_log(%g) = %.12g\n",max , taylor_log(max, min_iterations));
		}
	return 0;
}
