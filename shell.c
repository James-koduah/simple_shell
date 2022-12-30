#include "main.h"

void interactive(ssize_t b);
void non_interactive(void);
/**
 * main - simeple shell
 * Return: void
 */
int main(void)
{
	int i;
	ssize_t b;

	i = 1;
	b = 9;
	i = isatty(fileno(stdin));
	if (i == 0)
		non_interactive();
	else
		interactive(b);

	return (0);
}
/**
 * interactive - kskks
 * @b: ksksk
 * Return: ksksk
 */
void interactive(ssize_t b)
{
	size_t n;

	char *line_ptr;
	char *token;
	char *token_buf[100];
	int i;
	pid_t pid;

	n = 20;
	line_ptr = NULL;
	i = 0;
	token = NULL;
	pid = 1;

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
		{
			wait(NULL);
		}

	}


}
/**
 * non_interactive - for non_ interactive exe
 * Return: nothing
 */
void non_interactive(void)
{
	ssize_t char_read;
	size_t n;
	char *line, *token;
	pid_t pid;
	char *buf[100], *token_args[100];
	int i, j;

	i = 0;
	j = 0;
	line = NULL;
	n = 10;
	char_read = 1;
	char_read = getline(&line, &n, stdin);
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
		while (token != NULL)
		{
			token_args[j] = token;
			j++;
			token = strtok(NULL, " \n");
		}
		token_args[j] = NULL;
		pid = fork();
		if (pid == 0)
			execve(token_args[0], token_args, environ);
		else
			wait(NULL);
		i--;
	}
	free(line);


}
