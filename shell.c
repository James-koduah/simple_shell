#include "main.h"

void interactive(void);
void non_interactive(void);
/**
 * main - simeple shell
 * Return: void
 */
int main(void)
{
	int i;

	i = isatty(fileno(stdin));
	if (i == 0)
		non_interactive();
	else
		interactive();

	return (0);
}
/**
 * interactive - kskks
 * Return: ksksk
 */
void interactive(void)
{
	size_t n = 20;

	char *line_ptr;
	char *token;
	char *token_buf[100];
	int i = 0;
	pid_t pid;
	

	while (1)
	{
	i = 0;	
		printf("$ ");
		getline(&line_ptr, &n, stdin);

		token = strtok(line_ptr, " \n");
		if (token != NULL)
		{
			token_buf[i] = token;
			i++;
			token = strtok(NULL, " \n");
		}
		token_buf[i] = NULL;


		pid = fork();
		if (pid == 0)
		{
			execve(token_buf[0], token_buf, environ);
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
		token_args[0] = token;
		token_args[1] = NULL;
		pid = fork();
		if (pid == 0)
			execve(token_args[0], token_args, environ);
		else
			wait(NULL);
		i--;
	}


}
