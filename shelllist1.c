#include "shell.h"

/**
 * list_pclen - calculate the length of the linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t list_pclen(const list_t *h)
{
	size_t len = 0;

	while (h)
	{
		h = h->next;
		len++;
	}
	return (len);
}

/**
 * list_to_pcstrings - convert the linked list to an array of strings
 * @pchead: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_pcstrings(list_t *pchead)
{
	list_t *pcnode = pchead;
	size_t i = list_pclen(pchead), j;
	char **strings;
	char *string;

	if (!pchead || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; pcnode; pcnode = pcnode->next, i++)
	{
		string = malloc(_pcstrlen(pcnode->string) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		string = _pcstrcpy(string, pcnode->string);
		strings[i] = string;
	}
	strings[i] = NULL;
	return (strings);
}

/**
 * print_pclist - display all elements of the list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_pclist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_pcputs(convert_pcnumber(h->num, 10, 0));
		_pcputchar(':');
		_pcputchar(' ');
		_pcputs(h->string ? h->string : "(nil)");
		_pcputs("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * pcnode_starts_with - find a node whose string has the given prefix
 * @pcnode: pointer to the list head
 * @pcprefix: prefix to match
 * @c: the character that follows the prefix to match
 *
 * Return: node that matches or NULL
 */
list_t *pcnode_starts_with(list_t *pcnode, char *pcprefix, char c)
{
	char *p = NULL;

	while (pcnode)
	{
		p = starts_pcwith(pcnode->string, pcprefix);
		if (p && ((c == -1) || (*p == c)))
			return (pcnode);
		pcnode = pcnode->next;
	}
	return (NULL);
}

/**
 * get_pcnode_index - retrieve the index of a node
 * @pchead: head pointer
 * @pcnode: node pointer
 *
 * Return: node index or -1
 */
ssize_t get_pcnode_index(list_t *pchead, list_t *pcnode)
{
	size_t index = 0;

	while (pchead)
	{
		if (pchead == pcnode)
			return (index);
		pchead = pchead->next;
		index++;
	}
	return (-1);
}

