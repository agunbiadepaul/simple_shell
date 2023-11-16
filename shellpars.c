#include "shell.h"

/**
 * is_pccmd - finds out if a file is a command that can be executed.
 * @pcinfo: the struct info
 * @pcpath: path to the files to be checked
 *
 * Return: 1 if true, 0 if not true
 */
int is_pccmd(info_t *pcinfo, char *pcpath)
{
	struct stat st;

	(void)pcinfo;
	if (!pcpath || stat(pcpath, &st) != 0)
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);

	return (0);
}

/**
 * dup_pcchars - duplicates characters
 * @pathstring: the string of the PATH
 * @pcstart: starting index of the path
 * @pcstop: stopping index of the same path
 *
 * Return: the new buffer pointer
 */
char *dup_pcchars(char *pathstring, int pcstart, int pcstop)
{
	static char buf[1024];
	int k = 0, a = 0;

	for (k = 0, a = pcstart; a < pcstop; a++)
	{
		if (pathstring[a] != ':')
			buf[k++] = pathstring[a];
	}
	buf[k] = 0;
	return (buf);
}

/**
 * find_pcpath - locates this command within the PATH variable.
 * @pcinfo: the struct info
 * @pathstring: the string of the PATH
 * @pccmd: the command to find
 *
 * Return: the full path of the command if found or NULL if not found
 */
char *find_pcpath(info_t *pcinfo, char *pathstring, char *pccmd)
{
	int a = 0, curr_pos = 0;
	char *pcpath;

	if (!pathstring)
		return (NULL);

	if ((_pcstrlen(pccmd) > 2) && starts_pcwith(pccmd, "./"))
	{
		if (is_pccmd(pcinfo, pccmd))
			return (pccmd);
	}

	while (1)
	{
		if (!pathstring[a] || pathstring[a] == ':')
		{
			pcpath = dup_pcchars(pathstring, curr_pos, a);
			if (!*pcpath)
				_pcstrcat(pcpath, pccmd);
			else
			{
				_pcstrcat(pcpath, "/");
				_pcstrcat(pcpath, pccmd);
			}
			if (is_pccmd(pcinfo, pcpath))
				return (pcpath);
			if (!pathstring[a])
				break;
			curr_pos = a + 1;
		}
		a++;
	}
	return (NULL);
}

