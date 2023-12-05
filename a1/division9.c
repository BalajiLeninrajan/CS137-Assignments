#include <stdio.h>

int main(void)
{
    // takes num checks divisibility by 9
    // num < 10000 and prints result

    int num;
    scanf("%d", &num);                           // get user input
    printf("%s\n", num % 9 == 0 ? "yes" : "no"); // checks divisibility and prints result
    return 0;
}
