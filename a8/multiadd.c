#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

long long int multiadd(long long int a[], int n)
{
    // bucket array
    long long int *buckets = calloc(n + 1, sizeof(long long int));
    for (int i = 0; i < n; i++)
    {
        buckets[a[i]]++;
    }

    long long int *arr = malloc(n * sizeof(long long int));

    // bucket sort
    int curr = 0;
    for (int i = 0; i < n; i++)
    {
        bool flag = true;
        while (flag)
        {
            if (buckets[curr] == 0)
            {
                curr++;
            }
            else
            {
                buckets[curr]--;
                arr[i] = curr;
                flag = false;
            }
        }
    }
    free(buckets);

    bool add = false;
    // Helen's magic loop
    for (int i = 1; i < n; i *= 2)
    {
        for (int j = 0; j < n; j += i * 2)
        {
            if (add)
            {
                arr[j] = arr[j] + arr[j + i];
            }
            else
            {
                arr[j] = arr[j] * arr[j + i];
            }
        }
        add = !add;
    }

    long long int res = arr[0];
    free(arr);
    return res;
}

int main(void)
{
    long long int a[8] = {1, 4, 3, 6, 5, 3, 2, 8};
    assert(748 == multiadd(a, 8));
    long long int b[16] = {0};
    assert(0 == multiadd(b, 16));
    long long int c[16] = {1, 6, 5, 8, 6, 7, 5, 4, 8, 9, 10, 2, 12, 14, 1, 1};
    assert(27498 == multiadd(c, 16));
    long long int d[2] = {1, 0};
    assert(0 == multiadd(d, 2));

    return 0;
}