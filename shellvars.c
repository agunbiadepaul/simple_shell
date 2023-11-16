#include "shell.h"

/**
 * is_pcchain - verify if the buffer's current character is a chain delimiter.
 * @pcinfo: the struct parameter
 * @buf: the char buffer
 * @p: address for the current job at buf
 *
 * Return: 1 if chain delimiter, 0 if not delimiter
 */
int is_pcchain(info_t *pcinfo, char *buf, size_t *p)
{
	size_t b = *p;

	if (buf[b] == '|' && buf[b + 1] == '|')
	{
		buf[b] = 0;
		b++;
		pcinfo->cmd_buf_type = CMD_OR;
	}
	else if (buf[b] == '&' && buf[b + 1] == '&')
	{
		buf[b] = 0;
		b++;
		pcinfo->cmd_buf_type = CMD_AND;
	}
	else if (buf[b] == ';') /* located the end of this command */
	{
		buf[b] = 0; /* substitute the semicolon with null */
		pcinfo->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = b;
	return (1);
}

/**
 * check_pcchain - checks if, depending on the most recent status,
 * we should keep chaining.
 * @pcinfo: the struct parameter
 * @buf: the buffer’s char
 * @p: location of the new position in buf
 * @a: beginning position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_pcchain(info_t *pcinfo, char *buf, size_t *p, size_t a, size_t len)
{
	size_t b = *p;

	if (pcinfo->cmd_buf_type == CMD_AND)
	{
		if (pcinfo->status)
		{
			buf[a] = 0;
			b = len;
		}
	}
	if (pcinfo->cmd_buf_type == CMD_OR)
	{
		if (!pcinfo->status)
		{
			buf[a] = 0;
			b = len;
		}
	}

	*p = b;
}

/**
 * replace_pcalias - substitutes the tokenized string's alias.
 * @pcinfo: the struct parameter
 *
 * Return: 1 if replaced, 0 if not substituted
 */
int replace_pcalias(info_t *pcinfo)
{
	int a;
	list_t *pcnode;
	char *p;

	for (a = 0; a < 10; a++)
	{
		pcnode = pcnode_starts_with(pcinfo->alias, pcinfo->argv[0], '=');
		if (!pcnode)
			return (0);
		free(pcinfo->argv[0]);
		p = _pcstrchr(pcnode->string, '=');
		if (!p)
			return (0);
		p = _pcstrdup(p + 1);
		if (!p)
			return (0);
		pcinfo->argv[0] = p;
	}
	return (1);
}

/**
 * replace_pcvars - swaps out variables in the tokenized text
 * @pcinfo: the struct parameter
 *
 * Return: 1 if replaced, 0 if not swapped out
 */
int replace_pcvars(info_t *pcinfo)
{
	int a = 0;
	list_t *pcnode;

	for (a = 0; pcinfo->argv[a]; a++)
	{
		if (pcinfo->argv[a][0] != '$' || !pcinfo->argv[a][1])
			continue;

		if (!_pcstrcmp(pcinfo->argv[a], "$?"))
		{
			replace_pcstring(&(pcinfo->argv[a]),
					_pcstrdup(convert_pcnumber(pcinfo->status, 10, 0)));
			continue;
		}
		if (!_pcstrcmp(pcinfo->argv[a], "$$"))
		{
			replace_pcstring(&(pcinfo->argv[a]),
					_pcstrdup(convert_pcnumber(getpid(), 10, 0)));
			continue;
		}
		pcnode = pcnode_starts_with(pcinfo->env, &pcinfo->argv[a][1], '=');
		if (pcnode)
		{
			replace_pcstring(&(pcinfo->argv[a]),
					_pcstrdup(_pcstrchr(pcnode->string, '=') + 1));
			continue;
		}
		replace_pcstring(&pcinfo->argv[a], _pcstrdup(""));
	}
	return (0);
}

/**
 * replace_pcstring - swaps string
 * @old: location of the old string
 * @new: location of the new string
 *
 * Return: 1 if replaced, 0 if otherwise
 */
int replace_pcstring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

