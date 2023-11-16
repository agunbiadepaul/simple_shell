#include "shell.h"

/**
 * get_pcenviron - revert the environ string array copy
 * @pcinfo: A structure that potential arguments. Used to keep a
 *          constant function prototype.
 * Return: Always 0
 */
char **get_pcenviron(info_t *pcinfo)
{
	if (!pcinfo->environ || pcinfo->env_changed)
	{
		pcinfo->environ = list_to_pcstrings(pcinfo->env);
		pcinfo->env_changed = 0;
	}

	return (pcinfo->environ);
}

/**
 * _pcunsetenv - Remove an environment variable
 * @pcinfo: A structure that holds potential arguments. Used to keep a
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @pcvar: the string env var property
 */
int _pcunsetenv(info_t *pcinfo, char *pcvar)
{
	list_t *pcnode = pcinfo->env;
	size_t i = 0;  /* Additional initialization of 'i' */
	char *p;

	if (!pcnode || !pcvar)
		return (0);

	while (pcnode)
	{
		p = starts_pcwith(pcnode->string, pcvar);
		if (p && *p == '=')
		{
			pcinfo->env_changed = remove_pcnode_at_index(&(pcinfo->env), i);
			i = 0;
			pcnode = pcinfo->env;
			continue;
		}
		pcnode = pcnode->next;
		i++;
	}
	return (pcinfo->env_changed);
}

/**
 * _setpcenv - reset a different environment varaiable
 *             or alter a prevailing one
 * @pcinfo: A structure that holds potential arguments. Used to keep a
 *        constant function prototype.
 * @pcvar: the string env var possession
 * @pcvalue: the string env var value
 *  Return: 0 is success
 */
int _setpcenv(info_t *pcinfo, char *pcvar, char *pcvalue)
{
	char *pcbuf = NULL;
	list_t *pcnode;
	char *p;

	if (!pcvar || !pcvalue)
		return (0);

	pcbuf = malloc(_pcstrlen(pcvar) + _pcstrlen(pcvalue) + 2);
	if (!pcbuf)
		return (1);
	_pcstrcpy(pcbuf, pcvar);
	_pcstrcat(pcbuf, "=");
	_pcstrcat(pcbuf, pcvalue);
	pcnode = pcinfo->env;
	while (pcnode)
	{
		p = starts_pcwith(pcnode->string, pcvar);
		if (p && *p == '=')
		{
			free(pcnode->string);
			pcnode->string = pcbuf;
			pcinfo->env_changed = 1;
			return (0);
		}
		pcnode = pcnode->next;
	}
	add_pcnode_end(&(pcinfo->env), pcbuf, 0);
	free(pcbuf);
	pcinfo->env_changed = 1;
	return (0);
}

