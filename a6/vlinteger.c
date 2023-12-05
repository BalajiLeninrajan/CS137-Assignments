#include "vlinteger.h"
#include <stdlib.h>
#include <stdio.h>

struct linteger *vlintegerCreate(void)
{
	struct linteger *t1 = malloc(sizeof(struct linteger));
	t1->arr = NULL;
	t1->length = 0; // no values in t1.
	return t1;
}

void vlintegerPrint(struct linteger *t1)
{
	printf("length=%d\n", t1->length);
	for (int i = 0; i < t1->length; ++i)
	{
		printf("%d", t1->arr[i]);
	}
	printf("\n");
}

void vlintegerDestroy(struct linteger *t1)
{
	if (t1)
	{
		free(t1->arr); // free the inside array first
		free(t1);	   // then free the structure
	}
}

void vlintegerRead(struct linteger *t1)
{
	int curr;		 // current int
	int leading = 1; // if is first digit (to cull leading zeros)

	// for first digit
	while (leading && scanf("%d", &curr))
	{
		if (curr == 0) // ignores leading zeros
		{
			continue;
		}

		t1->arr = malloc(sizeof(int));
		t1->arr[0] = curr;
		t1->length++;
		leading = 0; // leading is set to false
	}

	// for all other digits
	while (scanf("%d", &curr))
	{
		t1->length++;
		t1->arr = realloc(t1->arr, sizeof(int) * t1->length);
		t1->arr[t1->length - 1] = curr;
	}
}

// appends digit to start of very long integer
void *appendDigit(struct linteger *t1, int digit)
{
	t1->length++;
	t1->arr = realloc(t1->arr, sizeof(int) * t1->length); // resize array

	// shifts digits
	for (int i = t1->length - 1; i > 0; i--)
	{
		t1->arr[i] = t1->arr[i - 1];
	}

	t1->arr[0] = digit; // appends digit
};

// Helper for vlintegerAdd
struct linteger *addSmallerToLarger(struct linteger *smaller, struct linteger *larger)
{
	// Initialize result
	struct linteger *res = vlintegerCreate();

	// for sums greater than 9
	int carry = 0;

	// for proper interation
	int diff = larger->length - smaller->length;

	// adding the numbers
	for (int i = smaller->length - 1; i >= 0; i--)
	{
		int sum = smaller->arr[i] + larger->arr[i + diff] + carry; // both start at right most val
		carry = sum / 10;										   // digits in 10s place
		int digit = sum % 10;									   // digits in 1s place
		appendDigit(res, digit);								   // adds to left of arr
	}

	// for remaining digits in larger int
	for (int i = diff - 1; i >= 0; i--)
	{
		int sum = larger->arr[i] + carry;
		carry = sum / 10;
		int digit = sum % 10;
		appendDigit(res, digit);
	}

	// for remaining carry
	if (carry)
	{
		appendDigit(res, carry);
	}
	return res;
}

struct linteger *vlintegerAdd(struct linteger *t1, struct linteger *t2)
{
	// 2 cases
	if (t2->length >= t1->length)
	{
		return addSmallerToLarger(t1, t2);
	}
	else
	{
		return addSmallerToLarger(t2, t1);
	}
}

// multiplies a vlinteger by a single digit raised to a power of 10
struct linteger *partialMult(struct linteger *t1, int digit, int tenExpo)
{
	// Initialize result
	struct linteger *res = vlintegerCreate();

	// For products greater than 9
	int carry = 0;

	// trailing zeros
	for (int i = 0; i < tenExpo; i++)
	{
		appendDigit(res, 0);
	}

	// calculates product
	for (int i = t1->length - 1; i >= 0; i--)
	{
		int product = t1->arr[i] * digit + carry;
		carry = product / 10;
		int tenRemainder = product % 10;
		appendDigit(res, tenRemainder);
	}

	// remaining carry
	if (carry)
	{
		appendDigit(res, carry);
	}

	return res;
}

struct linteger *vlintegerMult(struct linteger *t1, struct linteger *t2)
{
	// intialize answer
	struct linteger *res = vlintegerCreate();
	res->length = 1;
	res->arr = malloc(sizeof(int));
	res->arr[0] = 0;

	// For powers of 10
	int tenExpo = 0;

	// Multiplies the 2 numbers
	for (int i = t1->length - 1; i >= 0; i--)
	{
		// Product of t2 and a digit from t1
		struct linteger *part = partialMult(t2, t1->arr[i], tenExpo);

		// assign result to partial product and previous product
		struct linteger *tmp = res;
		res = vlintegerAdd(tmp, part);

		// moving to next digit (increase exponent of 10)
		tenExpo++;

		vlintegerDestroy(tmp);
		vlintegerDestroy(part);
	}

	return res;
}