#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

/*
    count digits logic takes parameter n
    returing the number of digits in n
    by resursively increasing div
    and taking n mod div
    if n % div == n
        then div has more digits than n
*/
int count_digits_logic(int n, int div)
{
    if (n % div == n)
    {
        return 1;
    }
    return 1 + count_digits_logic(n, div * 10);
}

/*
    count digits acts as a wrapper for
    count digits logic by calling it
    with an initial div of 10
*/
int count_digits(int n)
{
    return count_digits_logic(n, 10);
}

/*
    power take parameters m(matissa) and e(exponent)
    returing m raised to e (m^e)
    by recursively multiplying m e times
*/
int power(int m, int e)
{
    if (e == 0) // x^0 will always be 1
    {
        return 1;
    }
    return m * power(m, e - 1);
}

/*
    nar_sum calculates a narcissitic sum
        check definition of function narcissist for details
    it takes parameters:
        n: the number to take the sum of
        e: the expoment each digit of n is raised to
        digits: the number of digits remaining in n
*/
int nar_sum(int n, int e, int digits)
{
    if (digits == 0)
    {
        return 0;
    }

    int cur = n % 10; // current digit
    return power(cur, e) + nar_sum(n / 10, e, digits - 1);
}

/*
    A number is called a narcissistic number when the sum of each digit raised to the power of the total
    number of digits is equal to the number itself. The function has one parameter n, outputting true if
    n is narcissitic and false if it isn't.
*/
bool narcissist(int n)
{
    int digits = count_digits(n);         // number of digits in n
    int res = nar_sum(n, digits, digits); // narcissitic sum of n
    if (res == n)                         // check if n is narcissitic
    {
        return true;
    }
    return false;
}