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
		putchar('\n');
		free(*line);
		exit(1);
	}
}

/**
 * exit_env - Used to reduce the number of lines in the main function
 * @str: The command from the shell either (exit) or (env);
 * @line: A buffer from the main function to be freed
 * @line_copy: A buffer from the main function to be freed
 * Return: Nohthing
 */
void exit_env(char *str, char *line, char *line_copy)
{
	if (strcmp(str, "exit") == 0) /* exit */
	{
		free(line);
		free(line_copy);
		exit(EXIT_SUCCESS);
	}
	if (strcmp(str, "env") == 0) /* print env vars */
	{
		print_env();
	}
}
