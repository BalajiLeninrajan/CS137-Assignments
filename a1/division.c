#include <stdio.h>

int main(void)
{
    // takes num and denom and does integer divison
    // rounds away from 0 and prints result

    int num, denom;
    scanf("%d %d", &num, &denom); // get user input

    int res = num / denom; // integer division

    if (num % denom != 0)
    {
        if ((res == 0 && num < 0) || (res == 0 && denom < 0) || (res < 0))
        {
            res--; // round negative
        }
        else
        {
            res++; // round positive
        }
    }

    printf("%d\n", res); // print result
    return 0;
}
