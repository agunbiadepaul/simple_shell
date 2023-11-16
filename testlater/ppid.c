#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - PPID
 * Return: 0
 */

int main(void)
{
	pid_t myppid;
	myppid = getppid();

	printf("%u\n", myppid);
	return (0);
}
