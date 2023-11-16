#include "shell.h"

/**
 * input_pcbuf - buffers chained commands
 * @pcinfo: parameter struct
 * @pcbuf: buffer location
 * @pclen: len var
 *
 * Return: how many bytes read
 */
ssize_t input_pcbuf(info_t *pcinfo, char **pcbuf, size_t *pclen)
{
	ssize_t a = 0;
	size_t len_p = 0;

	if (!*pclen) /* Fill the buffer if there is nothing left in it. */
	{
		/* bfree((void **)pcinfo->cmd_pcbuf);*/
		free(*pcbuf);
		*pcbuf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(pcbuf, &len_p, stdin);
#else
		a = _getline(pcinfo, pcbuf, &len_p);
#endif
		if (a > 0)
		{
			if ((*pcbuf)[a - 1] == '\n')
			{
				(*pcbuf)[a - 1] = '\0'; /* eliminate the last newline */
				a--;
			}
			pcinfo->linecount_flag = 1;
			remove_pccomments(*pcbuf);
			build_pchistory_list(pcinfo, *pcbuf, pcinfo->histcount++);
			/* if (_pcstrchr(*pcbuf, ';')) Do we have a command chain here?*/
			{
				*pclen = a;
				pcinfo->cmd_buf = pcbuf;
			}
		}
	}
	return (a);
}

/**
 * get_pcinput - receives a line less the newline
 * @pcinfo: struct of parameter
 *
 * Return: number of bytes read
 */
ssize_t get_pcinput(info_t *pcinfo)
{
	static char *pcbuf; /* ';' buffer for command chain */
	static size_t m, n, pclen;
	ssize_t a = 0;
	char **buf_p = &(pcinfo->arg), *p;

	_pcputchar(BUF_FLUSH);
	a = input_pcbuf(pcinfo, &pcbuf, &pclen);
	if (a == -1) /* EOF */
		return (-1);
	if (pclen) /* There are still commands in the chain buffer. */
	{
		n = m;           /* put a new iterator in the place of the current buf. */
		p = pcbuf + m;    /* obtain the return pointer */

		check_pcchain(pcinfo, pcbuf, &m, n, pclen);
		while (n < pclen) /* cycle to the semicolon or finish */
		{
			if (is_pcchain(pcinfo, pcbuf, &n))
				break;
			n++;
		}

		m = n + 1; /* keep increasing past nulled ';'' */
		if (m >= pclen) /* hit the buffer's end? */
		{
			m = pclen = 0; /* revert position and length */
			pcinfo->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* return the pointer to the active command position */
		return (_pcstrlen(p));  /* revert the current command length */
	}

	*buf_p = pcbuf; /* otherwise return buffer from _getline() if not a chain */
	return (a);             /* Retrieve the buffer's length using _getline(). */
}

/**
 * read_pcbuf - function that reads a buffer
 * @pcinfo: the struct parameter
 * @pcbuf: buffer
 * @m: size
 *
 * Return: a
 */
ssize_t read_pcbuf(info_t *pcinfo, char *pcbuf, size_t *m)
{
	ssize_t a = 0;

	if (*m)
		return (0);
	a = read(pcinfo->readfd, pcbuf, READ_BUF_SIZE);
	if (a >= 0)
		*m = a;
	return (a);
}

/**
 * _getline - gets the next line of input from STDIN
 * @pcinfo: struct parameter
 * @pointer: address of the buffer's pointer, either NULL or preallocated
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: whatever s is
 */
int _getline(info_t *pcinfo, char **pointer, size_t *length)
{
	static char pcbuf[READ_BUF_SIZE];
	static size_t m, pclen;
	size_t k;
	ssize_t a = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pointer;
	if (p && length)
		s = *length;
	if (m == pclen)
		m = pclen = 0;

	a = read_pcbuf(pcinfo, pcbuf, &pclen);
	if (a == -1 || (a == 0 && pclen == 0))
		return (-1);

	c = _pcstrchr(pcbuf + m, '\n');
	k = c ? 1 + (unsigned int)(c - pcbuf) : pclen;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_pcstrncat(new_p, pcbuf + m, k - m);
	else
		_pcstrncpy(new_p, pcbuf + m, k - m + 1);

	s += k - m;
	m = k;
	p = new_p;

	if (length)
		*length = s;
	*pointer = p;
	return (s);
}

/**
 * sigintHandler - slabs ctrl-C
 * @sig_pcnum: the number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_pcnum)
{
	_pcputs("\n");
	_pcputs("$ ");
	_pcputchar(BUF_FLUSH);
}

