#include <stdio.h>
// #include <assert.h>

int ternarylastsearch(int L[], int len, int target)
{
	int beginning = 0, end = len - 1, prev = -1;

	while (beginning <= end)
	{
		// Note int m = (hi +lo)/2 is equivalent to m = lo + (hi - lo) / 2
		// but may overflow.
		int mid1 = beginning + (end - beginning) / 3;
		int mid2 = end - (end - beginning) / 3;

		printf("Examining indices %d and %d\n", mid1, mid2);

		if (L[mid2] == target)
		{
			if (mid2 > prev)
			{
				prev = mid2;
			}
			beginning = mid2 + 1;
		}
		else if (L[mid1] == target)
		{
			if (mid1 > prev)
			{
				prev = mid1;
			}
			beginning = mid1 + 1;
			end = mid2 - 1;
		}
		else if (target > L[mid2])
		{
			beginning = mid2 + 1;
		}
		else if (target < L[mid1])
		{
			end = mid1 - 1;
		}
		else
		{
			beginning = mid1 + 1;
			end = mid2 - 1;
		}
	}
	return prev;
}

// int main(void)
// {

// 	int a[10] = {1, 2, 3, 4, 5, 6, 6, 6, 9, 100};
// 	assert(7 == ternarylastsearch(a, 10, 6));
// 	printf("\n");
// 	int a2[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
// 	assert(-1 == ternarylastsearch(a2, 10, 100));
// 	printf("\n");
// 	assert(-1 == ternarylastsearch(a2, 10, 11));
// 	printf("\n");
// 	assert(0 == ternarylastsearch(a2, 10, 2));
// 	printf("\n");
// 	int a3[12] = {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6};
// 	assert(11 == ternarylastsearch(a3, 12, 6));
// 	printf("\n");
// 	int a4[2] = {0, 1};
// 	assert(1 == ternarylastsearch(a4, 2, 1));

// 	return 0;
// }
