#include "shell.h"

/**
 * main - main entry point for the shell program
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t pcinfo = INFO_INIT;

	int fd = 2;

	asm (
			"mov %1, %0\n\t"
			"add $3, %0"
			: "=a" (fd)
			: "a" (fd)
	    );

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_epcputs(argv[0]);
				_epcputs(": 0: Can't open ");
				_epcputs(argv[1]);
				_epcputchar('\n');
				_epcputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		pcinfo.readfd = fd;
	}

	increase_environ_list(&pcinfo);
	read_pchistory(&pcinfo);
	hsh(&pcinfo, argv);
	return (EXIT_SUCCESS);
}

