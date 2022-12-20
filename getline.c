#include "main.h"

/**
 * _getline - take user input from command line
 * @line: A pointer from the main function that would
 *	store the result of getline;
 * Return: void
 */
void _getline(char **line)
{
	size_t n;
	ssize_t char_read;

	char_read = getline(line, &n, stdin);
	if (char_read == -1)
	{
		printf("\n");
		free(*line);
		exit(1);
	}
}
