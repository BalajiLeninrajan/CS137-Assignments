#include <assert.h>
#include <stdio.h>

int count_common(int a[], int n1, int b[], int n2)
{
    int i = 0, j = 0;
    int prev = -1;
    int common = 0;

    while (i < n1 && j < n2)
    {
        // couting common elements, prev prevents double counting
        if (a[i] == b[j] && a[i] != prev)
        {
            prev = a[i];
            common++;
            i++;
            j++;
        }
        // since lists are sorted
        // move to next if not common
        else if (a[i] > b[j])
        {
            j++;
        }
        // also moves if val is same as previous
        else
        {
            i++;
        }
    }
    return common;
}

int main(void)
{
    int a1[4] = {1, 1, 1, 1};
    int b1[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    assert(1 == count_common(a1, 4, b1, 8));
    int a2[8] = {1, 3, 3, 4, 5, 8, 9, 100};
    int b2[7] = {4, 4, 8, 15, 20, 40, 100};
    assert(3 == count_common(a2, 8, b2, 7));
    int a3[2] = {7, 3};
    int b3[3] = {1, 4, 2};
    assert(0 == count_common(a3, 2, b3, 3));

    return 0;
}