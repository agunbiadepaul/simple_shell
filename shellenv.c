#include "shell.h"

/**
 * _mypcsetenv - Set a fresh environment variable's initial value,
 *               or adjust an existing one.
 * @pcinfo: A structure that holds potential arguments.
 *
 * Return: 0 on success, 1 on failure.
 */
int _mypcsetenv(info_t *pcinfo)
{
	if (pcinfo->argc != 3)
	{
		_epcputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setpcenv(pcinfo, pcinfo->argv[1], pcinfo->argv[2]) == 0)
		return (0);
	return (1);
}

/**
 * _mypcenv - Display the current environment.
 * @pcinfo: A structure that holds potential arguments.
 *
 * Return: Always 0.
 */
int _mypcenv(info_t *pcinfo)
{
	print_pclist_str(pcinfo->env);
	return (0);
}

/**
 * _getenv - Retrieve the value that the environ variable holds.
 * @pcinfo: A structure that holds potential arguments.
 * @pcname: Environ variable name.
 *
 * Return: Value of the environ variable.
 */
char *_getenv(info_t *pcinfo, const char *pcname)
{
	list_t *pcnode = pcinfo->env;
	char *ptr;

	while (pcnode)
	{
		ptr = starts_pcwith(pcnode->string, pcname);
		if (ptr && *ptr)
			return (ptr);
		pcnode = pcnode->next;
	}
	return (NULL);
}

/**
 * _mypcunsetenv - Delete an environment variable.
 * @pcinfo: A structure holding potential arguments.
 *
 * Return: Always 0.
 */
int _mypcunsetenv(info_t *pcinfo)
{
	int a;

	if (pcinfo->argc == 1)
	{
		_epcputs("Too few arguments.\n");
		return (1);
	}
	for (a = 1; a < pcinfo->argc; a++)
		_pcunsetenv(pcinfo, pcinfo->argv[a]);

	return (0);
}

/**
 * increase_environ_list - Increase the env list linked list.
 * @pcinfo: A structure holding potential arguments.
 *
 * Return: Always 0.
 */
int increase_environ_list(info_t *pcinfo)
{
	list_t *pcnode = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_pcnode_end(&pcnode, environ[a], 0);
	pcinfo->env = pcnode;
	return (0);
}

