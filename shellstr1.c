#include "shell.h"

/**
 * _pcstrcpy - copies the string
 * @pcdest: the destination of the string
 * @pcsrc: the source of the string
 *
 * Return: destination pointer
 */
char *_pcstrcpy(char *pcdest, char *pcsrc)
{
	int a = 0;

	if (pcdest == pcsrc || pcsrc == NULL)
		return (pcdest);

	while (pcsrc[a])
	{
		pcdest[a] = pcsrc[a];
		a++;
	}
	pcdest[a] = '\0';
	return (pcdest);
}

/**
 * _pcstrdup - string duplicator
 * @string: the string to be duplicated
 *
 * Return: duplicated string pointer
 */
char *_pcstrdup(const char *string)
{
	int length = 0;
	char *ret;

	if (string == NULL)
		return (NULL);

	while (*string++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
	{
		perror("Error allocating memory");
		return (NULL);
	}

	for (length++; length--;)
		ret[length] = *--string;

	return (ret);
}

/**
 * _pcputs - displays an inserted string
 * @string: the printed string
 *
 * Return: Nothing
 */
void _pcputs(char *string)
{
	if (string == NULL)
		return;
	{
		while (*string != '\0')
		{
			_pcputchar(*string);
			string++;
		}
	}
}

/**
 * _pcputchar - writes "ch" to the standard output
 * @ch: The character to print
 *
 * Return: On success 1.
 * When something goes wrong, -1 is returned and errno is properly set.
 */
int _pcputchar(char ch)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (ch != BUF_FLUSH)
		buf[a++] = ch;

	return (1);
}

