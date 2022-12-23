#include "main.h"
/**
 * print_error - Used to avoid repeating of code
 * @str: Error to be printed
 * @exit_num: the number used to exit the shell
 * Return: void
 */
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
int main(__attribute__((unused))int ac, char **av, char **env)
{
	char *line = malloc(sizeof(char) * BUFFER_SIZE), *line_copy;
	char *full_path;
	char *token = NULL, *token_args[BUFFER_SIZE];
	pid_t pid;
	char *bb[BUFFER_SIZE];
	int i = 0;
	ssize_t ll;
	size_t n;
	
	if (!(isatty(fileno(stdin))))
	{
		ll = getline(&line, &n,stdin);
	       while (ll >= 0)
	       {
		       bb[i] = line;
		       i++;
		       ll = getline(&line, &n, stdin);
	       }	       
	i--;	
		while(i >= 0)
		{	
			token = strtok(bb[i], " \n");
			token_args[0] = token;
			token_args[1] = NULL;
			pid = fork();
			if (pid == 0)
			{
			execve(token_args[0], token_args, environ);
			}
			else
			{
				wait(NULL);
			}
			i--;
		}
		return (0);
	}
i = 0;
	while (1)
	{
		putchar('$');/* prompt */
		putchar(' ');
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
			{
				perror("fork");
				exit(1);
			}
			else if (pid == 0) /* child process */
			{
				if (execve(full_path, token_args, env) < 0) /* execute commands */
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
