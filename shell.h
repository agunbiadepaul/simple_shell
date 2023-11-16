#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* number_conversion() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* 1 when using the system getline() function */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
/* chaining of commands */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *string;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - incorporates fictitious arguments to enter a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string with arguments that was produced by getline
 *@argv: a collection of strings produced by arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the exit()s error code
 *@linecount_flag: if this input line is counted
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the node of history
 *@alias: the node for alias 
 *@env_changed: if the environment was altered
 *@status: the command's return status upon last execution
 *@cmd_buf: address of the cmd_buf pointer, if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: The number of lines in history
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop1.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_pccmd(info_t *);
void fork_pccmd(info_t *);

/* toem_parser1.c */
int is_pccmd(info_t *, char *);
char *dup_pcchars(char *, int, int);
char *find_pcpath(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors1.c */
void _epcputs(char *);
int _epcputchar(char);
int _pcputfd(char c, int fd);
int _pcputsfd(char *str, int fd);

/* toem_string1.c */
int _pcstrlen(char *);
int _pcstrcmp(char *, char *);
char *starts_pcwith(const char *, const char *);
char *_pcstrcat(char *, char *);

/* toem_string11.c */
char *_pcstrcpy(char *, char *);
char *_pcstrdup(const char *);
void _pcputs(char *);
int _pcputchar(char);

/* toem_exits1.c */
char *_pcstrncpy(char *, char *, int);
char *_pcstrncat(char *, char *, int);
char *_pcstrchr(char *, char);

/* toem_tokenizer1.c */
char **pcstrtow(char *, char *);
char **pcstrtow2(char *, char);

/* toem_realloc1.c */
char *_pcmemset(char *, char, unsigned int);
void ffreestrings(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory1.c */
int pcbfree(void **);

/* toem_atoi1.c */
int pcinteractive(info_t *);
int is_pcdelim(char, char *);
int pc_isalpha(int);
int pc_atoi(char *);

/* toem_errors11.c */
int _pcerratoi(char *);
void print_pcerror(info_t *, char *);
int print_dec(int, int);
char *convert_pcnumber(long int, int, int);
void remove_pccomments(char *);

/* toem_builtin1.c */
int _mypcexit(info_t *);
int _mypccd(info_t *);
int _mypchelp(info_t *);

/* toem_builtin11.c */
int _mypchistory(info_t *);
int unset_pcalias(info_t *pcinfo, char *string);
int set_pcalias(info_t *pcinfo, char *string);
int print_pcalias(list_t *node);
int _mypcalias(info_t *);

/*toem_getline1.c */
ssize_t get_pcinput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_pcinfo(info_t *);
void set_pcinfo(info_t *, char **);
void free_pcinfo(info_t *, int);

/* toem_environ1.c */
char *_getenv(info_t *, const char *);
int _mypcenv(info_t *);
int _mypcsetenv(info_t *);
int _mypcunsetenv(info_t *);
int increase_environ_list(info_t *);

/* toem_getenv1.c */
char **get_pcenviron(info_t *);
int _pcunsetenv(info_t *, char *);
int _setpcenv(info_t *, char *, char *);

/* toem_history1.c */
char *get_pchistory_file(info_t *info);
int write_pchistory(info_t *info);
int read_pchistory(info_t *info);
int build_pchistory_list(info_t *info, char *buf, int linecount);
int renumber_pchistory(info_t *info);

/* toem_lists1.c */
list_t *add_pcnode(list_t **, const char *, int);
list_t *add_pcnode_end(list_t **, const char *, int);
size_t print_pclist_str(const list_t *);
int remove_pcnode_at_index(list_t **, unsigned int);
void free_pclist(list_t **);

/* toem_lists11.c */
size_t list_pclen(const list_t *);
char **list_to_pcstrings(list_t *);
size_t print_pclist(const list_t *);
list_t *pcnode_starts_with(list_t *, char *, char);
ssize_t get_pcnode_index(list_t *, list_t *);

/* toem_vars1.c */
int is_pcchain(info_t *, char *, size_t *);
void check_pcchain(info_t *, char *, size_t *, size_t, size_t);
int replace_pcalias(info_t *);
int replace_pcvars(info_t *);
int replace_pcstring(char **, char *);

#endif

