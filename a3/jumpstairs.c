#include <stdio.h>
#include <assert.h>

/*
    jump_stair_v1 takes left number of stairs and calculates the number of ways
    a person can climb them by taking steps of size 1 or 2
*/
int jump_stair_v1(int left)
{
    if (left <= 1)
    {
        return 1;
    }
    return jump_stair_v1(left - 1) + jump_stair_v1(left - 2); // Fibonacci sequence satisfies
}

/*
    jump_stair_v2_logic takes left number of stairs and calculates the number of ways
    a person can climb them by taking steps of size 1 or 2, 3 times in a row
    exluding the ending steps. Expect for when there are 2 steps left.
*/
int jump_stair_v2_logic(int left)
{
    if (left <= 3 && left != 2)
    {
        return 1;
    }
    return jump_stair_v2_logic(left - 3) + jump_stair_v2_logic(left - 6); // Similar idea to Fibonacci
}

// Fibonacci sequence
int fib(int left)
{
    if (left == 0)
    {
        return 0;
    }
    else if (left == 1)
    {
        return 1;
    }
    return fib(left - 1) + fib(left - 2);
}

/*
    Wrapper function for jump_stair_v2_logic
    Calls jump_stair_v2_logic and culls the
    extras created by ending on a 2 step
*/
int jump_stair_v2(int left)
{
    if (left % 3 == 2)
    {
        /*
            i.e left = 5
            1, 1, 1, 1, 1 - No problem
            1, 1, 1, 2 - sh*t hits the fan
            Because final 2 has 2 cases:
            1, 1 and 2
            I count both and get a duplicate
            1, 1, 1, (1, 1) == 1, 1, 1, 1, 1
        */
        return jump_stair_v2_logic(left) - fib(left / 3); // removes duplicate 2 case
    }
    else
    {
        return jump_stair_v2_logic(left);
    }
}

/*
    jump_stair_v3 takes left number of stairs and calculates the number of ways
    a person can climb them by taking steps of size 2 or 3, 3 times in a row
    including the ending steps.
*/
int jump_stair_v3(int left)
{
    if (left % 3 != 0 || left < 6) // There are no solutions for these values
    {
        return 0;
    }
    else if (left == 9) // 3 jumps of size 3
    {
        return 1;
    }
    else if (left == 6) // 3 jumps of size 2
    {
        return 1;
    }
    return jump_stair_v3(left - 9) + jump_stair_v3(left - 6);
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 30; i++)
    {
        printf("-%d-\n", i);
        printf("%d\n", jump_stair_v1(i));
        printf("%d\n", jump_stair_v2(i));
        printf("%d\n", jump_stair_v3(i));
    }

    return 0;
}
