#include <stdio.h>

void printarr(int a[], int len)
{
    for (int i = 0; i < len - 1; i++)
        printf("%d ", a[i]);
    printf("%d\n", a[len - 1]);
}

void doubleselectionsort(int a[], int len)
{
    for (int i = 0; i < len / 2; i++)
    {
        // Find the index of the critical values
        int min = i, max = len - 1 - i;
        for (int j = i; j < len - i; j++)
        {
            if (a[j] < a[min])
            {
                min = j;
            }

            if (a[j] > a[max])
            {
                max = j;
            }
        }

        // swap
        int tmp = a[min];
        a[min] = a[i];
        a[i] = tmp;
        if (i == max)
        {
            max = min;
        }
        tmp = a[max];
        a[max] = a[len - 1 - i];
        a[len - 1 - i] = tmp;

        printarr(a, len);
    }
}

int main(void)
{

    int a[7] = {4, 4, 4, 0, 0, -10, -10};
    doubleselectionsort(a, 7);
    int a2[5] = {6, 11, 2, -4, -1};
    doubleselectionsort(a2, 5);
    int a3[10] = {1, 8, 5, 4, 6, 2, 5, 6, 2, 9};
    doubleselectionsort(a3, 10);
    int a4[6] = {0, 1, 4, 0, 0, -1};
    doubleselectionsort(a4, 6);

    return 0;
}
