#include "calc.h"
#include <math.h>

double add(double a, double b)
{
    return a + b;
}

double subtract(double a, double b)
{
    return a - b;
}
double multiply(double a, double b)
{
    return a * b;
}

double divide(double a, double b)
{
    if (b == 0)
        return 0.0 / 0.0;
    else
        return a / b;
}

double modulo(double a, double b)
{
    return fmod(a, b);
}

double power(double a, double b)
{
    return pow(a, b);
}

double squareroot(double a)
{
    if (a < 0)
        return 0.0 / 0.0;
    else
        return sqrt(a);
}

double inverse(double a)
{
    if (a == 0)
        return 0.0 / 0.0;
    return 1 / a;
}