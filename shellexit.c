#include "shell.h"

/**
 * _pcstrncpy - Copies a string.
 * @pcdest: The string to be copied at the destination.
 * @pcsrc: The source string.
 * @num: The number of characters copied.
 * Return: The string integrated.
 */
char *_pcstrncpy(char *pcdest, char *pcsrc, int num)
{
	int a, b;
	char *s = pcdest;

	a = 0;
	while (pcsrc[a] != '\0' && a < num - 1)
	{
		pcdest[a] = pcsrc[a];
		a++;
	}
	if (a < num)
	{
		b = a;
		while (b < num)
		{
			pcdest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 * _pcstrncat - Integrates two strings.
 * @pcdest: The first string.
 * @pcsrc: The second string.
 * @num: The amount of bytes to be maximally used.
 * Return: The string integrated.
 */
char *_pcstrncat(char *pcdest, char *pcsrc, int num)
{
	int a, b;
	char *s = pcdest;

	a = 0;
	b = 0;
	while (pcdest[a] != '\0')
		a++;
	while (pcsrc[b] != '\0' && b < num)
	{
		pcdest[a] = pcsrc[b];
		a++;
		b++;
	}
	if (b < num)
		pcdest[a] = '\0';
	return (s);
}

/**
 * _pcstrchr - Function that finds a character in a string.
 * @string: The parsed string.
 * @ch: The character to find.
 * Return: A pointer to the memory area s.
 */
char *_pcstrchr(char *string, char ch)
{
	do {
		if (*string == ch)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

