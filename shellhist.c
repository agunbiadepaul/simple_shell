#include "shell.h"

/**
 * get_pchistory_file - function that retrieves the history file
 * @pcinfo: struct of parameter
 *
 * Return: the allocated string contained in the history file
 */

char *get_pchistory_file(info_t *pcinfo)
{
	char *pcbuf, *pcdir;

	pcdir = _getenv(pcinfo, "HOME=");
	if (!pcdir)
		return (NULL);
	pcbuf = malloc(sizeof(char) * (_pcstrlen(pcdir) + _pcstrlen(HIST_FILE) + 2));
	if (!pcbuf)
		return (NULL);
	pcbuf[0] = 0;
	_pcstrcpy(pcbuf, pcdir);
	_pcstrcat(pcbuf, "/");
	_pcstrcat(pcbuf, HIST_FILE);
	return (pcbuf);
}

/**
 * write_pchistory - appends to a file that exists or creates a new file
 * @pcinfo: the struct parameteri
 *
 * Return: 1 on success, else -1
 */
int write_pchistory(info_t *pcinfo)
{
	ssize_t fd;
	char *pcfilename = get_pchistory_file(pcinfo);
	list_t *pcnode = NULL;

	if (!pcfilename)
		return (-1);

	fd = open(pcfilename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(pcfilename);
	if (fd == -1)
		return (-1);
	for (pcnode = pcinfo->history; pcnode; pcnode = pcnode->next)
	{
		_pcputsfd(pcnode->string, fd);
		_pcputfd('\n', fd);
	}
	_pcputfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_pchistory - function that reads the history from a file
 * @pcinfo: the struct parameter
 *
 * Return: history count on success, 0 otherwise
 */
int read_pchistory(info_t *pcinfo)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, readlen, fsize = 0;
	struct stat st;
	char *pcbuf = NULL, *pcfilename = get_pchistory_file(pcinfo);

	if (!pcfilename)
		return (0);

	fd = open(pcfilename, O_RDONLY);
	free(pcfilename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	pcbuf = malloc(sizeof(char) * (fsize + 1));
	if (!pcbuf)
		return (0);
	readlen = read(fd, pcbuf, fsize);
	pcbuf[fsize] = 0;
	if (readlen <= 0)
		return (free(pcbuf), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (pcbuf[a] == '\n')
		{
			pcbuf[a] = 0;
			build_pchistory_list(pcinfo, pcbuf + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		build_pchistory_list(pcinfo, pcbuf + last, linecount++);
	free(pcbuf);
	pcinfo->histcount = linecount;
	while (pcinfo->histcount-- >= HIST_MAX)
		remove_pcnode_at_index(&(pcinfo->history), 0);
	renumber_pchistory(pcinfo);
	return (pcinfo->histcount);
}

/**
 * build_pchistory_list - includes entry to the linked list history
 * @pcinfo: A structure that holds potential arguments. Used to keep a
 * constant function prototype
 * @pcbuf: the buffer
 * @linecount: the linecount, histcount history
 *
 * Return: success 0
 */
int build_pchistory_list(info_t *pcinfo, char *pcbuf, int linecount)
{
	list_t *pcnode = NULL;

	if (pcinfo->history)
		pcnode = pcinfo->history;
	add_pcnode_end(&pcnode, pcbuf, linecount);

	if (!pcinfo->history)
		pcinfo->history = pcnode;
	return (0);
}

/**
 * renumber_pchistory - renumbers the history-linked list
 * following modifications.
 * @pcinfo: A structure that holds potential arguments. Used to keep a
 *        constant function prototype
 *
 * Return: the new histcount
 */
int renumber_pchistory(info_t *pcinfo)
{
	list_t *pcnode = pcinfo->history;
	int a = 0;

	while (pcnode)
	{
		pcnode->num = a++;
		pcnode = pcnode->next;
	}
	return (pcinfo->histcount = a);
}

