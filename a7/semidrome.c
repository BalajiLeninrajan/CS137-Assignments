#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

bool is_semidrome(char *s);
bool is_palimdrome(char *s, int n);
char *get_substring(const char *s, int start, int n);
bool check_semidrome(char *s, int n, int llen);

int main(void)
{
	assert(!is_semidrome("abaaab"));
	assert(is_semidrome("popeye"));
	assert(is_semidrome("racecar"));
	assert(is_semidrome("abaaaba"));
	assert(!is_semidrome("aab"));
	assert(is_semidrome("aaa"));
	assert(is_semidrome("aabbaaa"));
	assert(is_semidrome("aabcbaa"));
	assert(!is_semidrome("a"));
	assert(is_semidrome("aaaa"));
	assert(is_semidrome("aaaabbbtttaataa"));
	assert(is_semidrome("abaaaccdddaaaba"));
	assert(!is_semidrome(""));

	return 0;
}

// returns true is string is palimdrome else false
bool is_palimdrome(char *s, int n)
{
	if (n < 2)
	{
		return false;
	}

	for (int i = 0; i < n / 2; i++)
	{
		if (s[i] != s[n - i - 1])
		{
			return false;
		}
	}
	return true;
}

// returned string must be free'd
char *get_substring(const char *s, int start, int n)
{
	char *res = (char *)malloc(sizeof(char) * n + 1);
	for (int i = 0; i < n; i++)
	{
		res[i] = s[i + start];
	}
	res[n] = '\0';
	return res;
}

// // gets substring and checks if palimdrome
// bool check_palimdrome(char *s, int start, int n)
// {
// 	char *tmp = get_substring(s, start, n);
// 	bool res = is_palimdrome(tmp, n);
// 	free(tmp);
// 	return res;
// }

bool check_semidrome(char *s, int n, int llen)
{
	if (is_palimdrome(s, n))
	{
		return true;
	}

	if (llen + 2 > n)
	{
		return false;
	}

	char *left = get_substring(s, 0, llen);
	char *right = get_substring(s, llen, n - llen);

	bool res = check_semidrome(left, strlen(left), 2) && check_semidrome(right, strlen(right), 2);
	free(left);
	free(right);
	if (!res)
	{
		return check_semidrome(s, n, ++llen);
	}
	return res;
}

bool is_semidrome(char *s)
{
	int n = strlen(s);
	if (n <= 0)
	{
		return false;
	}

	return check_semidrome(s, n, 2);

	// ------------------BROKEN SOLUTION------------------
	// bool res;
	// int sublen = n;
	// int i = 0;
	// for (int i = 0; i < n;)
	// {
	// 	res = check_palimdrome(s, i, sublen);
	// 	if (res)
	// 	{
	// 		i += sublen;
	// 		sublen = n - i + 1;
	// 	}
	// 	if (i == n - 1)
	// 	{
	// 		return false;
	// 	}
	// 	sublen--;
	// 	if (sublen == 0)
	// 	{
	// 		i++;
	// 		sublen = n - i + 1;
	// 	}
	// }

	// if (res)
	// {
	// 	return true;
	// }
	// return false;
}
