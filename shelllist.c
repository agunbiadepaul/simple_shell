#include "shell.h"

/**
 * add_pcnode - complements a pcnode to the start of the list
 * @pchead: address of pointer to head node
 * @string: field of node of string
 * @num: node index used by history
 *
 * Return: scope of list
 */
list_t *add_pcnode(list_t **pchead, const char *string, int num)
{
	list_t *new_pchead;

	if (!pchead)
		return (NULL);
	new_pchead = malloc(sizeof(list_t));
	if (!new_pchead)
		return (NULL);
	_pcmemset((void *)new_pchead, 0, sizeof(list_t));
	new_pchead->num = num;
	if (string)
	{
		new_pchead->string = _pcstrdup(string);
		if (!new_pchead->string)
		{
			free(new_pchead);
			return (NULL);
		}
	}
	new_pchead->next = *pchead;
	*pchead = new_pchead;
	return (new_pchead);
}

/**
 * add_pcnode_end - complements a node to the end of the list
 * @pchead: location of the pointer to head node
 * @string: str field of node
 * @num: index of node by history
 *
 * Return: size of list
 */
list_t *add_pcnode_end(list_t **pchead, const char *string, int num)
{
	list_t *new_pcnode, *pcnode;

	if (!pchead)
		return (NULL);

	pcnode = *pchead;
	new_pcnode = malloc(sizeof(list_t));
	if (!new_pcnode)
		return (NULL);
	_pcmemset((void *)new_pcnode, 0, sizeof(list_t));
	new_pcnode->num = num;
	if (string)
	{
		new_pcnode->string = _pcstrdup(string);
		if (!new_pcnode->string)
		{
			free(new_pcnode);
			return (NULL);
		}
	}
	if (pcnode)
	{
		while (pcnode->next)
			pcnode = pcnode->next;
		pcnode->next = new_pcnode;
	}
	else
		*pchead = new_pcnode;
	return (new_pcnode);
}

/**
 * print_pclist_str - display the string element of a list_t
 * linked list only
 * @h: pole to the node that comes first
 *
 * Return: scope of list
 */
size_t print_pclist_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_pcputs(h->string ? h->string : "(nil)");
		_pcputs("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * remove_pcnod_at_index - deletes given index node
 * @pchead: location of the first node pointer
 * @pcindex: index of node to remove
 *
 * Return: 1 on success, 0 on failure
 */
int remove_pcnode_at_index(list_t **pchead, unsigned int pcindex)
{
	list_t *pcnode, *prev_pcnode;
	unsigned int a = 0;

	if (!pchead || !*pchead)
		return (0);

	if (!pcindex)
	{
		pcnode = *pchead;
		*pchead = (*pchead)->next;
		free(pcnode->string);
		free(pcnode);
		return (1);
	}
	pcnode = *pchead;
	while (pcnode)
	{
		if (a == pcindex)
		{
			prev_pcnode->next = pcnode->next;
			free(pcnode->string);
			free(pcnode);
			return (1);
		}
		a++;
		prev_pcnode = pcnode;
		pcnode = pcnode->next;
	}
	return (0);
}

/**
 * free_pclist - releases all the nodes in the list
 * @head_pointer: location of the pointer to the head node
 *
 * Return: void
 */
void free_pclist(list_t **head_pointer)
{
	list_t *pcnode, *next_pcnode, *pchead;

	if (!head_pointer || !*head_pointer)
		return;
	pchead = *head_pointer;
	pcnode = pchead;
	while (pcnode)
	{
		next_pcnode = pcnode->next;
		free(pcnode->string);
		free(pcnode);
		pcnode = next_pcnode;
	}
	*head_pointer = NULL;
}

