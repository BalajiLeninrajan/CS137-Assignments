#include <stdio.h>
#include <assert.h>

typedef struct Point
{
	int x;
	int y;
} point;

typedef struct Rectangle
{
	point bottomLeft;
	int width;
	int height;
} rectangle;

/*
	Returns smaller of 2 ints
*/
int min(int a, int b)
{
	return a <= b ? a : b;
}

/*
	Returns larger of 2 ints
*/
int max(int b, int a)
{
	return a >= b ? a : b;
}

/*
	Returns the intersection of 2 rectangles
*/
rectangle simple_intersect(rectangle rectanlge_1, rectangle rectanlge_2)
{
	// Checks if there are no intersections
	// returns false_rectangle if there isn't
	if (rectanlge_1.bottomLeft.x + rectanlge_1.width < rectanlge_2.bottomLeft.x ||
		rectanlge_2.bottomLeft.x + rectanlge_2.width < rectanlge_1.bottomLeft.x ||
		rectanlge_1.bottomLeft.y + rectanlge_1.height < rectanlge_2.bottomLeft.y ||
		rectanlge_2.bottomLeft.y + rectanlge_2.height < rectanlge_1.bottomLeft.y)
	{
		rectangle false_rectangle = {{0, 0}, 0, 0};
		return false_rectangle;
	}

	rectangle res;
	res.bottomLeft.x = max(rectanlge_1.bottomLeft.x, rectanlge_2.bottomLeft.x);
	res.bottomLeft.y = max(rectanlge_1.bottomLeft.y, rectanlge_2.bottomLeft.y);
	res.width = min(rectanlge_1.bottomLeft.x + rectanlge_1.width, rectanlge_2.bottomLeft.x + rectanlge_2.width) - res.bottomLeft.x;
	res.height = min(rectanlge_1.bottomLeft.y + rectanlge_1.height, rectanlge_2.bottomLeft.y + rectanlge_2.height) - res.bottomLeft.y;
	return res;
}

int compare_rectangles(rectangle a, rectangle b)
{
	if (a.bottomLeft.x != a.bottomLeft.x)
	{
		return 1;
	}
	else if (a.bottomLeft.y != b.bottomLeft.y)
	{
		return 1;
	}
	else if (a.height != b.height)
	{
		return 1;
	}
	else if (a.width != b.width)
	{
		return 1;
	}
	return 0;
}

/*
	Returns intersection of multiple rectangels
*/
rectangle intersection(rectangle rects[], int n)
{
	rectangle res = simple_intersect(rects[0], rects[1]);
	for (int i = 2; i < n; i++)
	{
		res = simple_intersect(res, rects[i]);
	}
	return res;
}

int main()
{
	rectangle result;
	rectangle r = {{2, 6}, 3, 4};
	rectangle s = {{0, 7}, 7, 1};
	rectangle t = {{3, 5}, 1, 6};
	rectangle u = {{5, 6}, 3, 4};

	// Test 1
	rectangle rects1[2] = {r, s};
	result = intersection(rects1, 2);
	assert(result.bottomLeft.x == 2);
	assert(result.bottomLeft.y == 7);
	assert(result.width == 3);
	assert(result.height == 1);

	// Test 2
	rectangle rects2[3] = {r, s, t};
	result = intersection(rects2, 3);
	assert(result.bottomLeft.x == 3);
	assert(result.bottomLeft.y == 7);
	assert(result.width == 1);
	assert(result.height == 1);

	// Test 3
	rectangle rects3[4] = {r, s, t, u};
	result = intersection(rects3, 4);
	assert(result.bottomLeft.x == 0);
	assert(result.bottomLeft.y == 0);
	assert(result.width == 0);
	assert(result.height == 0);

	return 0;
}