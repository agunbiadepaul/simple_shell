#include "shell.h"

/**
 * _pcmemset - inserts a single byte into RAM
 * @p: the memory area's pointer
 * @byte: the bit to insert into *p
 * @n: the number of bytes that must be filled
 * Return: (p) a reference to the memory location p
 */
char *_pcmemset(char *p, char byte, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		p[a] = byte;
	return (p);
}

/**
 * ffreestrings - releases a group of strings
 * @ss: string of strings
 */
void ffreestrings(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * _realloc - reallocates memory block
 * @pointer: pointer to the last allocated block
 * @old_size: byte scope of the last block
 * @new_size: Size of the new block in bytes
 * Return: pointer the blocks.
 */
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!pointer)
		return (malloc(new_size));
	if (!new_size)
		return (free(pointer), NULL);
	if (new_size == old_size)
		return (pointer);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)pointer)[old_size];
	free(pointer);
	return (p);
}

