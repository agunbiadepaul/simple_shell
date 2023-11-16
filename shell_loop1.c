#include "shell.h"

/**
 * hsh - key shell loop
 * @pcinfo: the struct parameter & return info
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *pcinfo, char **argv)
{
	ssize_t a = 0;
	int builtin_ret = 0;

	while (a != -1 && builtin_ret != -2)
	{
		clear_pcinfo(pcinfo);
		if (pcinteractive(pcinfo))
			_pcputs("$ ");
		_epcputchar(BUF_FLUSH);
		a = get_pcinput(pcinfo);
		if (a != -1)
		{
			set_pcinfo(pcinfo, argv);
			builtin_ret = find_builtin(pcinfo);
			if (builtin_ret == -1)
				find_pccmd(pcinfo);
		}
		else if (pcinteractive(pcinfo))
			_pcputchar('\n');
		free_pcinfo(pcinfo, 0);
	}
	write_pchistory(pcinfo);
	free_pcinfo(pcinfo, 1);
	if (!pcinteractive(pcinfo) && pcinfo->status)
		exit(pcinfo->status);
	if (builtin_ret == -2)
	{
		if (pcinfo->err_num == -1)
			exit(pcinfo->status);
		exit(pcinfo->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - locate the built-in command
 * @pcinfo: the struct parameter & return info
 *
 * Return: -1 if builtin not found, 0 if successfully,
 * 1 if builtin not successful, -2 when builtin signals exits()
 */
int find_builtin(info_t *pcinfo)
{
	int a, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _mypcexit},
		{"env", _mypcenv},
		{"help", _mypchelp},
		{"history", _mypchistory},
		{"setenv", _mypcsetenv},
		{"unsetenv", _mypcunsetenv},
		{"cd", _mypccd},
		{"alias", _mypcalias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_pcstrcmp(pcinfo->argv[0], builtintbl[a].type) == 0)
		{
			pcinfo->line_count++;
			built_in_ret = builtintbl[a].func(pcinfo);
			break;
		}
	return (built_in_ret);
}

/**
 * find_pccmd - locate command in PATH
 * @pcinfo: the struct parameter and return info
 *
 * Return: void
 */
void find_pccmd(info_t *pcinfo)
{
	char *pcpath = NULL;
	int a, k;

	pcinfo->path = pcinfo->argv[0];
	if (pcinfo->linecount_flag == 1)
	{
		pcinfo->line_count++;
		pcinfo->linecount_flag = 0;
	}
	for (a = 0, k = 0; pcinfo->argv[a]; a++)
		if (!is_pcdelim(pcinfo->arg[a], " \t\n"))
			k++;
	if (!k)
		return;

	pcpath = find_pcpath(pcinfo, _getenv(pcinfo, "PATH="), pcinfo->argv[0]);
	if (pcpath)
	{
		pcinfo->path = pcpath;
		fork_pccmd(pcinfo);
	}
	else
	{
		if ((pcinteractive(pcinfo) || _getenv(pcinfo, "PATH=") ||
					pcinfo->argv[0][0] == '/') && is_pccmd(pcinfo, pcinfo->argv[0]))
			fork_pccmd(pcinfo);
		else if (*(pcinfo->arg) != '\n')
		{
			pcinfo->status = 127;
			print_pcerror(pcinfo, "not found\n");
		}
	}
}

/**
 * fork_pccmd - splits an executable thread to run command
 * @pcinfo: the struct parameter & return info
 *
 * Return: nothing
 */
void fork_pccmd(info_t *pcinfo)
{
	pid_t chd_pid;

	chd_pid = fork();
	if (chd_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (chd_pid == 0)
	{
		if (execve(pcinfo->path, pcinfo->argv, get_pcenviron(pcinfo)) == -1)
		{
			free_pcinfo(pcinfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(pcinfo->status));
		if (WIFEXITED(pcinfo->status))
		{
			pcinfo->status = WEXITSTATUS(pcinfo->status);
			if (pcinfo->status == 126)
				print_pcerror(pcinfo, "Permission denied\n");
		}
	}
}

