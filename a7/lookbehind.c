#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void remove_char(char *s, int n, int index)
{
    for (int i = index; i < n; i++)
    {
        s[i] = s[i + 1];
    }
}

void remove_word(char *s, int index, int wordlen)
{
    for (int i = 0; i < wordlen; i++)
    {
        remove_char(s, strlen(s), index);
    }
}

bool check_sub(char *s, int n, int index, const char *check, int checklen)
{
    for (int i = 0; i < checklen; i++)
    {
        if (s[i + index] != check[i])
        {
            return false;
        }
    }

    return true;
}

bool look_behind_helper(const char *check, const char *s_sub, char *word)
{
    int n = strlen(word);
    int checklen = strlen(check);
    int s_sub_len = strlen(s_sub);
    int lenfind = checklen + s_sub_len;
    char *find = (char *)malloc(sizeof(char) * lenfind + 1);
    find[0] = '\0';
    strcat(find, check);
    strcat(find, s_sub);

    for (int i = 0; i <= n - lenfind; i++)
    {
        if (check_sub(word, n, i, find, lenfind))
        {
            remove_word(word, i + checklen, s_sub_len);
            free(find);
            return true;
        }
    }
    free(find);
    return false;
}

void lookBehind(const char *check, const char *s_sub, char *word)
{
    while (look_behind_helper(check, s_sub, word))
    {
    }
}

int main(void)
{

    char word[] = "foo bar loop hoop";
    lookBehind("l", "oo", word);
    assert(0 == strcmp("foo bar lp hoop", word));
    lookBehind("o", "o", word);
    assert(0 == strcmp("fo bar lp hop", word));

    char word3[] = "CS137137";
    lookBehind("CS", "137", word3);
    assert(0 == strcmp("CS", word3));
    char word3b[] = "CS137 137";
    lookBehind("CS", "137", word3b);
    assert(0 == strcmp("CS 137", word3b));

    char word4[] = "111111";
    lookBehind("1", "1", word4);
    assert(0 == strcmp("1", word4));

    char word5[] = "wow";
    lookBehind("", "w", word5);
    assert(0 == strcmp("o", word5));

    char word6[] = "w";
    lookBehind("", "w", word5);
    assert(0 == strcmp("o", word5));

    return 0;
}
