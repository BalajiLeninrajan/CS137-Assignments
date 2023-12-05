#include <math.h>

// returns the area of a trapezium
double trapeziumarea(double ay, double by, double dx)
{
	return 0.5 * (ay + by) * dx;
}

// calculates the integral by using the trapezoid rule
double integral(double (*f)(double), double a, double b, int n)
{
	double res = 0; // result of integral

	double delta = (b - a) / n; // dx

	// calculates the areas of all trapeziums and adds to res
	for (int i = 0; i < n; i++)
	{
		// calls f(x) with differnt intervals [f(n), f(n+1)]
		res += trapeziumarea(f(a + delta * i), f(a + delta * (i + 1)), delta);
	}

	return res;
}

// calculates an acurate integral by repeatedly using the trapezoid rule
double trapezoidal(double (*f)(double), double a, double b, double epsilon, int n)
{
	double res1, res2;
	do
	{
		res1 = integral(f, a, b, n);
		res2 = integral(f, a, b, n + n);
		n += n;							   // doubles n for next interation
	} while (fabs(res1 - res2) > epsilon); // compares difference of res to epsilon
	return res2;
}