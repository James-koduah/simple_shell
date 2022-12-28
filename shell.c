#include "main.h"

void interactive(ssize_t b);
void non_interactive(void);
/**
 * main - simeple shell
 * Return: void
 */
int main(void)
{
	int i = 1;
	ssize_t b = 9;

	i = isatty(fileno(stdin));
	if (i == 0)
		non_interactive();
	else
		interactive(b);

	return (0);
}
/**
 * interactive - kskks
 * Return: ksksk
 */
void interactive(ssize_t b)
{
	size_t n = 20;

	char *line_ptr = malloc(sizeof(char *) * 3);
	char *token;
	char *token_buf[100];
	int i = 0;
	pid_t pid;
	

	while (1)
	{
		i = 0;	
		putchar('$');
		putchar(' ');
		b = getline(&line_ptr, &n, stdin);
		if (b == -1)
		{
			free(line_ptr);
			putchar('\n');
			exit(3);
		}
		token = strtok(line_ptr, " \n");
		if (token != NULL)
		{
			token_buf[i] = token;
			i++;
			token = strtok(NULL, " \n");
		}
		token_buf[i] = NULL;


		pid = fork();
		if (pid == -1)
		{
			free(line_ptr);
			exit(99);
		}
		if (pid == 0)
		{
			if (execve(token_buf[0], token_buf, environ) == -1)
			{
				perror("./hsh");
				free(line_ptr);
				exit(99);
			}
		}
		else
			wait(NULL);

	}


}
/**
 * non_interactive - for non_ interactive exe
 * Return: nothing
 */
void non_interactive(void)
{
	ssize_t char_read = 1;
	size_t n;
	char *line, *token;
	pid_t pid;
	char *buf[100], *token_args[100];
	int i = 0;


	char_read = getline(&line, &n, stdin);
	if (char_read == -1)
	{
		free(line);
		putchar('\n');
		exit(55);
	}
	while (char_read >= 0)
	{
		buf[i] = line;
		i++;
		char_read = getline(&line, &n, stdin);
	}


	i--;
	while (i >= 0)
	{
		token = strtok(buf[i], " \n");
		if (token == NULL)
		{
			free(line);
			exit(99);
		}
		token_args[0] = token;
		token_args[1] = NULL;
		pid = fork();
		if (pid == -1)
		{
			free(line);
			exit(99);
		}
		if (pid == 0)
			execve(token_args[0], token_args, environ);
		else
			wait(NULL);
		i--;
	}


}
