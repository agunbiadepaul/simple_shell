#include "shell.h"

/**
 * clear_pcinfo - resets info_t struct
 * @pcinfo: address of struct
 */
void clear_pcinfo(info_t *pcinfo)
{
	pcinfo->arg = NULL;
	pcinfo->argv = NULL;
	pcinfo->path = NULL;
	pcinfo->argc = 0;
}

/**
 * set_pcinfo - reset info_t struct
 * @pcinfo: address of struct
 * @av: argument vector
 */
void set_pcinfo(info_t *pcinfo, char **av)
{
	int a = 0;

	pcinfo->fname = av[0];
	if (pcinfo->arg)
	{
		pcinfo->argv = pcstrtow(pcinfo->arg, " \t");
		if (!pcinfo->argv)
		{
			pcinfo->argv = malloc(sizeof(char *) * 2);
			if (pcinfo->argv)
			{
				pcinfo->argv[0] = _pcstrdup(pcinfo->arg);
				pcinfo->argv[1] = NULL;
			}
		}
		for (a = 0; pcinfo->argv && pcinfo->argv[a]; a++)
			;
		pcinfo->argc = a;

		replace_pcalias(pcinfo);
		replace_pcvars(pcinfo);
	}
}

/**
 * free_pcinfo - functions that frees info_t struct fields
 * @pcinfo: address of struct
 * @pcall: true when free
 */
void free_pcinfo(info_t *pcinfo, int pcall)
{
	ffreestrings(pcinfo->argv);
	pcinfo->argv = NULL;
	pcinfo->path = NULL;
	if (pcall)
	{
		if (!pcinfo->cmd_buf)
			free(pcinfo->arg);
		if (pcinfo->env)
			free_pclist(&(pcinfo->env));
		if (pcinfo->history)
			free_pclist(&(pcinfo->history));
		if (pcinfo->alias)
			free_pclist(&(pcinfo->alias));
		ffreestrings(pcinfo->environ);
		pcinfo->environ = NULL;
		pcbfree((void **)pcinfo->cmd_buf);
		if (pcinfo->readfd > 2)
			close(pcinfo->readfd);
		_pcputchar(BUF_FLUSH);
	}
}

