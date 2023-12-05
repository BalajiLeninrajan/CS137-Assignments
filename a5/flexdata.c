#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

typedef struct FlexData
{
    bool isInt;
    int value_int;
    double value_double;
} FlexData;

/*
    Does intger division if both parameters are integers
    Else does float division and returns the result
*/
FlexData flexDivide(FlexData a, FlexData b)
{
    if (a.isInt && b.isInt)
    {
        return (FlexData){true, a.value_int / b.value_int, 0};
    }
    else if (a.isInt)
    {
        return (FlexData){false, 0, a.value_int / b.value_double};
    }
    else if (b.isInt)
    {
        return (FlexData){false, 0, a.value_double / b.value_int};
    }
    else
    {
        return (FlexData){false, 0, a.value_double / b.value_double};
    }
}

int main(void)
{
    FlexData n1 = {true, 17, 0};
    FlexData n2 = {true, 5, 0};
    FlexData d1 = {false, 0, 14.3};
    FlexData d2 = {false, 0, 2.4};

    FlexData r1 = flexDivide(n1, n2);
    FlexData r2 = flexDivide(d1, d2);
    FlexData r3 = flexDivide(n1, d2);
    assert(r1.isInt);
    assert(!r2.isInt);
    assert(!r3.isInt);
    assert(3 == r1.value_int);
    printf("%lf\n", r2.value_double);
    printf("%lf\n", r3.value_double);

    return 0;
}