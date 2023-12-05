#include <stdio.h>
#include <math.h>

/*
    get max value in a bucket array
*/
int get_max(int arr[], int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        if (arr[i] != 0)
        {
            return i;
        }
    }
    return -1;
}

/*
    get min value in a bucket array
*/
int get_min(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] != 0)
        {
            return i;
        }
    }
    return -1;
}

/*
    frequency sum of bucket array
    from start index to end index
    the end index is excluded in the sum
*/
int fr_sum(int arr[], int start, int end)
{
    int sum = 0;
    for (int i = start; i < end; i++)
    {
        sum += arr[i];
    }
    return sum;
}

/*
    accumulative sum of bucket array
    from start index to end index
    the end index is excluded in the sum
*/
float acc_sum(int arr[], int start, int end)
{
    float sum = 0;
    for (int i = start; i < end; i++)
    {
        sum += arr[i] * i;
    }
    return sum;
}

/*
    returns the mean of a bucket array
*/
float mean(int arr[], int size, int total)
{
    return acc_sum(arr, 0, size) / total;
}

/*
    returns standard deviation of bucket array
          ____________________
    s = \|Sum(X - x)^2/(n - 1)
    X: each element
    x: mean
    n: number of elements
*/
float std_dv(int arr[], int size, int total)
{
    float sd_sum = 0;                 // sum of (X - x)^2
    float m = mean(arr, size, total); // gets mean
    for (int i = 0; i < size; i++)
    {
        if (arr[i] != 0)
        {
            for (int j = 0; j < arr[i]; j++)
            {
                sd_sum += (i - m) * (i - m);
            }
        }
    }
    return sqrt(sd_sum / (total - 1));
}

int main(void)
{
    int grades[101] = {0}; // grade[i] is the frequency of grade i + 1
    int students = 0;      // number of students

    int usr_in;
    while (scanf("%d", &usr_in))
    {
        grades[usr_in] += 1; // add grade
        students++;
    }

    int grade_max = get_max(grades, 101);
    int grade_min = get_min(grades, 101);

    printf("The maximal grade is: %d\n", grade_max);
    printf("The number of students who received the maximal grade is %d\n", grades[grade_max]);
    printf("The minimal grade is: %d\n", grade_min);
    printf("The number of students who received the minimal grade is %d\n", grades[grade_min]);
    printf("The course mean is: %0.3f\n", mean(grades, 101, students));
    printf("The standard deviation is: %0.3f\n", std_dv(grades, 101, students));
    printf("The number of students who failed the course is: %d\n", fr_sum(grades, 0, 50));

    return 0;
}