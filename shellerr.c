#include "shell.h"

/**
 * _epcputs - Display an inserted string.
 * @string: The string to be displayed as output.
 *
 * Return: Zero.
 */
void _epcputs(char *string)
{
	int a = 0;

	if (!string)
		return;
	while (string[a] != '\0')
	{
		_epcputchar(string[a]);
		a++;
	}
}

/**
 * _epcputchar - Display the character cpc to stderr.
 * @cpc: The character to be displayed.
 *
 * Return: On success 1. On error, -1, and errno is set.
 */
int _epcputchar(char cpc)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (cpc == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (cpc != BUF_FLUSH)
		buf[a++] = cpc;
	return (1);
}

/**
 * _pcputfd - Display the character cpc to given fd.
 * @cpc: The character to be displayed.
 * @fd: The file descriptor.
 *
 * Return: On success 1. On error, -1 is returned, and errno is set.
 */
int _pcputfd(char cpc, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (cpc == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (cpc != BUF_FLUSH)
		buf[a++] = cpc;
	return (1);
}

/**
 * _pcputsfd - Display an inserted string.
 * @string: The string to be displayed as output.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int _pcputsfd(char *string, int fd)
{
	int a = 0;

	if (!string)
		return (0);
	while (*string)
	{
		a += _pcputfd(*string++, fd);
	}
	return (a);
}

