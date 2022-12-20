#include "main.h"
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
		{
			perror("strdup");
			exit(1);
		}
		i = 0;
		token = strtok(line_copy, TOKEN_DELIMITERS);
		while (token != NULL)
		{
			token_args[i] = token;
			i++;
			token = strtok(NULL, TOKEN_DELIMITERS);
		}
		token_args[i] = NULL;
		if (strcmp(token_args[0], "exit") == 0) /* exit */
		{
			free(line);
			free(line_copy);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(token_args[0], "env") == 0) /* print env vars */
		{
			print_env();
		}
		full_path = search_path(token_args[0]);
		if (full_path != NULL)
		{
			pid = fork(); /* create fork */
			if (pid < 0)
			{
				perror("fork");
				exit(1);
			}
			else if (pid == 0) /* child process */
			{
				if (execve(full_path, token_args, NULL) < 0) /* execute commands */
				{
					perror(av[0]);
					exit(1);
				}
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
