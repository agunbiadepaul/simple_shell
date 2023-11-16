#include "shell.h"

/**
 * _mypcexit - terminates the shell process
 * @pcinfo: A structure that holds potential arguments.
 * Return: exits with an exit status that is specified.
 *         (0) if pcinfo->argv[0] != "exit"
 */
int _mypcexit(info_t *pcinfo)
{
	int pcexitcheck;

	if (pcinfo->argv[1])  /* If there is an exit argument */
	{
		pcexitcheck = _pcerratoi(pcinfo->argv[1]);
		if (pcexitcheck == -1)
		{
			pcinfo->status = 2;
			print_pcerror(pcinfo, "Illegal number: ");
			_epcputs(pcinfo->argv[1]);
			_epcputchar('\n');
			return (1);
		}
		pcinfo->err_num = _pcerratoi(pcinfo->argv[1]);
		return (-2);
	}
	pcinfo->err_num = -1;
	return (-2);
}

/**
 * _mypccd - alters the current directory in which the process is running.
 * @pcinfo: A structure that holds potential arguments.
 * Return: Always 0
 */
int _mypccd(info_t *pcinfo);
int _mypccd(info_t *pcinfo)
{
	char *s, *pcdir, buffer[1024];
	int pcchdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_pcputs("TODO: >>getcwd failure emsg here<<\n");
	if (!pcinfo->argv[1])
	{
		pcdir = _getenv(pcinfo, "HOME=");
		if (!pcdir)
			pcchdir_ret = /* TODO: what should this be? */
				chdir((pcdir = _getenv(pcinfo, "PWD=")) ? pcdir : "/");
		else
			pcchdir_ret = chdir(pcdir);
	}
	else if (_pcstrcmp(pcinfo->argv[1], "-") == 0)
	{
		if (!_getenv(pcinfo, "OLDPWD="))
		{
			_pcputs(s);
			_pcputchar('\n');
			return (1);
		}
		_pcputs(_getenv(pcinfo, "OLDPWD=")), _pcputchar('\n');
		pcchdir_ret = /* TODO: what should this be? */
			chdir((pcdir = _getenv(pcinfo, "OLDPWD=")) ? pcdir : "/");
	}
	else
		pcchdir_ret = chdir(pcinfo->argv[1]);

	if (pcchdir_ret == -1)
	{
		print_pcerror(pcinfo, "can't cd to ");
		_epcputs(pcinfo->argv[1]), _epcputchar('\n');
	}
	else
	{
		_setpcenv(pcinfo, "OLDPWD", _getenv(pcinfo, "PWD="));
		_setpcenv(pcinfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _mypchelp - displays help information.
 * @pcinfo: A structure that holds potential arguments.
 * Return: 0 When successful
 */
int _mypchelp(info_t *pcinfo)
{
	char **arg_array;

	arg_array = pcinfo->argv;
	_pcputs("help call works. Function not yet implemented \n");
	if (0)
		_pcputs(*arg_array); /* temp att_unused workaround */
	return (0);
}

