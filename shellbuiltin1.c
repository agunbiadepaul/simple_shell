#include "shell.h"

/**
 * _mypchistory - displays the history list, one command per line, preceded
 *                with line numbers, starting at 0.
 * @pcinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0
 */
int _mypchistory(info_t *pcinfo)
{
    print_pclist(pcinfo->history);
    return (0);
}

/**
 * unset_pcalias - unsets an alias
 * @pcinfo: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_pcalias(info_t *pcinfo, char *string)
{
    char *p, c;
    int pcret;

    p = _pcstrchr(string, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    pcret = remove_pcnode_at_index(&(pcinfo->alias),
                                  get_pcnode_index(pcinfo->alias, pcnode_starts_with(pcinfo->alias, string, -1)));
    *p = c;
    return (pcret);
}

/**
 * set_pcalias - sets or unsets an alias
 * @pcinfo: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_pcalias(info_t *pcinfo, char *string)
{
    char *p;

    p = _pcstrchr(string, '=');
    if (!p)
        return (1);
    if (!*++p)
        return unset_pcalias(pcinfo, string);

    unset_pcalias(pcinfo, string);
    return (add_pcnode_end(&(pcinfo->alias), string, 0) == NULL);
}

/**
 * print_pcalias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_pcalias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _pcstrchr(node->string, '=');
        for (a = node->string; a <= p; a++)
            _pcputchar(*a);
        _pcputchar('\'');
        _pcputs(p + 1);
        _pcputs("'\n");
        return (0);
    }
    return (1);
}

/**
 * _mypcalias - mimics the alias builtin (man alias)
 * @pcinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0
 */
int _mypcalias(info_t *pcinfo)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (pcinfo->argc == 1)
    {
        node = pcinfo->alias;
        while (node)
        {
            print_pcalias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; pcinfo->argv[i]; i++)
    {
        p = _pcstrchr(pcinfo->argv[i], '=');
        if (p)
            set_pcalias(pcinfo, pcinfo->argv[i]);
        else
            print_pcalias(pcnode_starts_with(pcinfo->alias, pcinfo->argv[i], '='));
    }

    return (0);
}

