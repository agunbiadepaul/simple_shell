#include "shell.h"

/**
 * _pcstrlen - returns string length
 * @string: the string whose length needs to be measured
 *
 * Return: string length in integers
 */
int _pcstrlen(char *string)
{
	int a = 0;

	if (!string)
		return (0);

	while (*string++)
		a++;
	return (a);
}

/**
 * _pcstrcmp - compares two strangs lexicographically.
 * @stg1: the first strang
 * @stg2: the second strang
 *
 * Return: negative if stg1 < stg2, positive if stg1 > stg2, 0 if stg1 == stg2
 */
int _pcstrcmp(char *stg1, char *stg2)
{
	while (*stg1 && *stg2)
	{
		if (*stg1 != *stg2)
			return (*stg1 - *stg2);
		stg1++;
		stg2++;
	}
	if (*stg1 == *stg2)
		return (0);
	else
		return (*stg1 < *stg2 ? -1 : 1);
}

/**
 * starts_pcwith - verifies if the needle begins with a haystack
 * @hayst: string to search
 * @nedle: the substring to find
 *
 * Return: address of the haystack's next character, or NULL
 */
char *starts_pcwith(const char *hayst, const char *nedle)
{
	while (*nedle)
		if (*nedle++ != *hayst++)
			return (NULL);
	return ((char *)hayst);
}

/**
 * _pcstrcat - concatenates two strings together
 * @pcdest: the buffer destination
 * @pcsrc: the buffer source
 *
 * Return: pointer to the buffer destination
 */
char *_pcstrcat(char *pcdest, char *pcsrc)
{
	char *ret = pcdest;

	while (*pcdest)
		pcdest++;
	while (*pcsrc)
		*pcdest++ = *pcsrc++;
	*pcdest = *pcsrc;
	return (ret);
}

