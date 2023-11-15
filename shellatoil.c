#include "shell.h"

/**
 * pcinteractive - returns true if shell is in interactive mode
 * @pcinfo: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int pcinteractive(info_t *pcinfo)
{
	return (isatty(STDIN_FILENO) && pcinfo->readfd <= 2);
}

/**
 * is_pcdelim - checks if character is a delimiter
 * @pcc: the char to check
 * @pcdelim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_pcdelim(char pcc, char *pcdelim)
{
	while (*pcdelim)
		if (*pcdelim++ == pcc)
			return (1);
	return (0);
}

/**
 * pc_isalpha - checks for alphabetic character
 * @pcc: The character to input
 * Return: 1 if pcc is alphabetic, 0 otherwise
 */
int pc_isalpha(int pcc)
{
	if ((pcc >= 'a' && pcc <= 'z') || (pcc >= 'A' && pcc <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * pc_atoi - converts a string to an integer
 * @pcs: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int pc_atoi(char *pcs)
{
	int i, sign = 1, flag = 0, output;
	unsigned int pcresult = 0;

	for (i = 0;  pcs[i] != '\0' && flag != 2; i++)
	{
		if (pcs[i] == '-')
			sign *= -1;

		if (pcs[i] >= '0' && pcs[i] <= '9')
		{
			flag = 1;
			pcresult *= 10;
			pcresult += (pcs[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -pcresult;
	else
		output = pcresult;

	return (output);
}

