#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

char *merge(char *s1, char *s2);

int main(void)
{
    char s1[] = "The brown jumps the dog";
    char s2[] = "quick fox over lazy";
    char *s = merge(s1, s2);
    assert(!strcmp(s, "The quick brown fox jumps over the lazy dog"));
    free(s);

    char s3[] = "the brown";
    char s4[] = "quick fox is sleeping today";
    s = merge(s3, s4);
    assert(!strcmp(s, "the quick brown fox is sleeping today"));
    free(s);

    char *s5 = "happy to you";
    char *s6 = "birthday";
    s = merge(s5, s6);
    assert(!strcmp(s, "happy birthday to you"));
    free(s);

    char *s7 = "test1 test2";
    char *s8 = "test3";
    s = merge(s7, s8);
    free(s);

    return 0;
}

char *merge(char *s1, char *s2)
{
    char *s3 = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 2));
    int cur3 = 0;
    while (*s1 && *s2)
    {
        while (*s1 != ' ' && *s1)
        {
            s3[cur3] = *s1;
            s1++;
            cur3++;
        }
        s3[cur3] = ' ';
        cur3++;
        if (*s1 == ' ')
        {
            s1++;
        }

        while (*s2 != ' ' && *s2)
        {
            s3[cur3] = *s2;
            s2++;
            cur3++;
        }
        s3[cur3] = ' ';
        cur3++;
        if (*s2 == ' ')
        {
            s2++;
        }
    }

    s3[cur3] = '\0';

    if (*s1)
    {
        strcat(s3, s1);
    }
    if (*s2)
    {
        strcat(s3, s2);
    }
    return s3;
}