#include "shell.h"

/**
 * _pcerratoi - Transform a string to an integer.
 * @string: The string to be converted.
 * Return: 0 if no numbers in string, otherwise if converted
 *       -1 on error.
 */
int _pcerratoi(char *string)
{
	int a = 0;
	unsigned long int result = 0;

	if (*string == '+')
		string++;  /* Should I investigate why this returns 255 for the main?*/
	for (a = 0; string[a] != '\0'; a++)
	{
		if (string[a] >= '0' && string[a] <= '9')
		{
			result *= 10;
			result += (string[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_pcerror - Display an error message.
 * @pcinfo: The parameter & return info struct.
 * @errstr: Error type contained in string.
 * Return: 0 if no numbers, otherwise if converted numbers
 *        -1 on error.
 */
void print_pcerror(info_t *pcinfo, char *errstr)
{
	_epcputs(pcinfo->fname);
	_epcputs(": ");
	print_dec(pcinfo->line_count, STDERR_FILENO);
	_epcputs(": ");
	_epcputs(pcinfo->argv[0]);
	_epcputs(": ");
	_epcputs(errstr);
}

/**
 * print_dec - Prints the decimal (integer) number of (base 10).
 * @pcinput: The input.
 * @fd: The file descriptor.
 *
 * Return: Number of characters printed.
 */
int print_dec(int pcinput, int fd)
{
	int (*__pcputchar)(char) = _pcputchar;
	int a, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__pcputchar = _epcputchar;
	if (pcinput < 0)
	{
		_abs_ = -pcinput;
		__pcputchar('-');
		count++;
	}
	else
		_abs_ = pcinput;
	current = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__pcputchar('0' + current / a);
			count++;
		}
		current %= a;
	}
	__pcputchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_pcnumber - Translator function, an imitation of itoa.
 * @pcnum: Number.
 * @pcbase: Base.
 * @pcflags: Argument flags.
 *
 * Return: String.
 */
char *convert_pcnumber(long int pcnum, int pcbase, int pcflags)
{
	static char *array;
	static char buffer[50];
	char pcsign = 0;
	char *pointer;
	unsigned long n = pcnum;

	if (!(pcflags & CONVERT_UNSIGNED) && pcnum < 0)
	{
		n = -pcnum;
		pcsign = '-';
	}
	array = pcflags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do	{
		*--pointer = array[n % pcbase];
		n /= pcbase;
	} while (n != 0);

	if (pcsign)
		*--pointer = pcsign;
	return (pointer);
}

/**
 * remove_pccomments - Replaces '#' with '\0' from the first instance.
 * @pcbuf: String to revise address.
 *
 * Return: Always 0.
 */
void remove_pccomments(char *pcbuf)
{
	int a;

	for (a = 0; pcbuf[a] != '\0'; a++)
		if (pcbuf[a] == '#' && (!a || pcbuf[a - 1] == ' '))
		{
			pcbuf[a] = '\0';
			break;
		}
}

