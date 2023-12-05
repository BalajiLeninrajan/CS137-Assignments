#include <stdio.h>
#include <stdbool.h>

void arrprint(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        printf("%d ", a[i]);
    }
    printf("%d\n", a[n - 1]);
}

void matrixprint(int n, int m[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("%d\n", m[i][n - 1]);
    }
}

// convert 2D array nxn into 1D array of size nxn
void convert(int n, int mat[n][n], int a[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i * n + j] = mat[i][j];
        }
    }
}

// returns the sum of a row in a matrix
int sumrow(int n, int row, int mat[n][n])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += mat[row][i];
    }
    return sum;
}

// returns sum of a column in a matrix
int sumcol(int n, int col, int mat[n][n])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += mat[i][col];
    }
    return sum;
}

// returns sum of top-left to bottom-right diagonal
int sumdiagi(int n, int mat[n][n])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += mat[i][i];
    }
    return sum;
}

// returns sum of sinister bend diagonal
int sumdiagj(int n, int mat[n][n])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += mat[n - 1 - i][i];
    }
    return sum;
}

// returns true if mat is a magic square matrix.
//  mat is a magic square if the sums of the numbers in each row,
//  each column, and both main diagonals are the same
//  the function also prints the magic constant (the magic sum of each row, column, and diagonal).
//  use "The magic constant is: %d\n"  for printing the magic constant
bool ismagicsquare(int n, int mat[n][n])
{
    if (n == 1) // square matrix of size 1 is always magic sqaure
    {
        printf("The magic constant is: %d\n", mat[0][0]);
        return true;
    }

    // define magic constant
    int magic_constant = sumrow(n, 0, mat);

    // check every row
    // first row checked when defining magic constant
    for (int i = 1; i < n; i++)
    {
        if (sumrow(n, i, mat) != magic_constant)
        {
            return false;
        }
    }

    // check every column
    for (int i = 0; i < n; i++)
    {
        if (sumcol(n, i, mat) != magic_constant)
        {
            return false;
        }
    }

    // check diagonals
    if (sumdiagi(n, mat) != magic_constant)
    {
        return false;
    }
    else if (sumdiagj(n, mat) != magic_constant)
    {
        return false;
    }

    printf("The magic constant is: %d\n", magic_constant);
    return true;
}
