#include <unistd.h>
#include <sys/types.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid;
	char pid_string[20]; // Assuming the maximum characters for PID won't exceed 20
	int length = 0;

	my_pid = getpid();

	// Convert PID to a string manually
	pid_t temp_pid = my_pid;
	do {
		pid_string[length++] = '0' + (temp_pid % 10);
		temp_pid /= 10;
	} while (temp_pid != 0);
	int i, j;

	// Reverse the pid_string to get the correct PID value
	for (i = 0, j = length - 1; i < j; i++, j--) {
		char temp = pid_string[i];
		pid_string[i] = pid_string[j];
		pid_string[j] = temp;
	}

	pid_string[length] = '\n'; // Add newline character

	// Write the PID string to the standard output (file descriptor 1)
	write(1, pid_string, length + 1); // Adding 1 to include the newline character

	return 0;
}

