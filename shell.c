#include "main.h"


int non_interactive(void);
int main(void)
{
	int i;

	i = isatty(fileno(stdin));
	if (i == 0)
		non_interactive();

	return (0);
}


int non_interactive(void)
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
	return (0);

}	
