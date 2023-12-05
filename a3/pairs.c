#include <stdio.h>
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
    Prints dupplicated digits of n, ignoring imediately repeated occurances
*/
int pair_logic(int n, int digits, int prev)
{
    if (digits < 0)
    {
        return 0;
    }

    int pos = power(10, digits); // position of digit
    int cur = n / pos;           // current digit

    if (cur != prev) // finds unique digit in n
    {
        printf("%d%d", cur, cur);
    }
    return pair_logic(n - cur * pos, digits - 1, cur); // removes read digit and continues
}

/*
    pair takes a positive integer n and prints the integer where every digit is paired up next to itself.
    pair will not print sequence of more than two of the same digit in a row.
    If a digit appears by itself with no duplicate on either side, digit will be duplicated while printing.
*/
void numberPairs(int n)
{
    int digits = count_digits(n);  // number of digits in n
    pair_logic(n, digits - 1, 10); // calls with 10 because 10 is not a digit
}