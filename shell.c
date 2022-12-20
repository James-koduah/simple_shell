#include "main.h"

void print_error(char *str, int exit_num)
{
	perror(str);
	exit(exit_num);
}
/**
 * main - execute a simple shell
 * @ac: argument count
 * @av: argument vector
 * Return: Always 0.
 */
int main(__attribute__((unused))int ac, char **av)
{
	char *line = malloc(sizeof(char) * BUFFER_SIZE), *line_copy;
	char *full_path;
	char *token = NULL, *token_args[BUFFER_SIZE];
	pid_t pid;
	int i;

	while (1)
	{
		printf("$ "); /* prompt */
		_getline(&line);
		line_copy = strdup(line); /* duplicate input str*/
		if (line_copy == NULL)
			print_error("strdup", 1);
		i = 0;
		token = strtok(line_copy, TOKEN_DELIMITERS);
		while (token != NULL)
		{
			token_args[i] = token;
			i++;
			token = strtok(NULL, TOKEN_DELIMITERS);
		}
		token_args[i] = NULL;
		full_path = search_path(token_args[0]);
		exit_env(token_args[0], line, line_copy);
		if (full_path != NULL)
		{
			pid = fork(); /* create fork */
			if (pid < 0)
				print_error("fork", 1);
			else if (pid == 0) /* child process */
			{
				if (execve(full_path, token_args, environ) < 0) /* execute commands */
					print_error(av[0], 1);
				free(full_path);
			}
			else
			{
				wait(NULL); /* parent process */
				free(line_copy);
			}
		}
		else
			perror("execve");
	}
	free(line);
	return (0);

}
