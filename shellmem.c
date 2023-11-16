#include "shell.h"

/**
 * pcbfree - release a pointer and set the address to NULL
 * @pointer: address of the pointer to free
 *
 * Return: If released, 1; if not, 0.
 */
int pcbfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

