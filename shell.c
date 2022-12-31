#include "main.h"

void interactive(ssize_t b);
void non_interactive(void);
/**
 * main - simeple shell
 * Return: void
 */
int main(void)
{
	int connected_terminal;
	ssize_t b;

/* Initialzed these values so valgrind would be happy */
	connected_terminal = 1;
	b = 9;

/* Check if the program is connected to a terminal or not */
	connected_terminal = isatty(fileno(stdin));
	if (connected_terminal == 0)
		non_interactive();
	else
		interactive(b);

	return (0);
}

/**
 * interactive - If the program is connected to a terminal
 * @b: Not important
 * Return: Nothing
 */
void interactive(ssize_t b)
{
	size_t n;
	char *line_ptr;
	char *token;
	char *token_buf[100];
	int i, o_sps;
	pid_t pid;

/* Initialzed these values so valgrind would be happy */
	n = 20;
	line_ptr = NULL;
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
			printf("\nexiting\n");
			exit(3);
		}

		/* Check if only spaces was inputed */
		o_sps = only_spaces(line_ptr);
		if (o_sps == 0)
		{
			free(line_ptr);
			perror("./hsh");
			exit(44);
		}

		/* Split the string into tokens */
		token = strtok(line_ptr, " \n");
		while (token != NULL)
		{
			token_buf[i] = token;
			i++;
			token = strtok(NULL, " \n");
		}
		token_buf[i] = NULL;
		
		token = search_path(token_buf[0]);
		if (token != NULL)
		{
			/* Child process */
			pid = fork();
			if (pid == -1)
			{
				free(token);
				free(line_ptr);
				exit(99);
			}
			if (pid == 0)
			{
				if (execve(token, token_buf, environ) == -1)
				{
					perror("./hsh");
					free(line_ptr);
					free(token);
					exit(99);
				}
			}
			else
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
	int i, j, exe;
	int osp = 9;

/* Initialzed these values so valgrind would be happy */
	i = 0;
	exe = 0;
	line = NULL;
	n = 10;
	char_read = 1;

	char_read = getline(&line, &n, stdin);

	/* If there would be more than one line printed to the terminal */
	while (char_read >= 0)
	{
			buf[i] = line;
			i++;
		char_read = getline(&line, &n, stdin);
	}
	
	/* We will loop through each line printed to the terminal and execute them */
	i--;
	while (i >= 0)
	{
		j = 0;
		token = strtok(buf[i], " \n");
		if (token == NULL)
			exe = 1;
		while (token != NULL)
		{
			token_args[j] = token;
			j++;
			token = strtok(NULL, " \n");
		}
		token_args[j] = NULL;
		token = search_path(token_args[0]);
		if (token != NULL)
		{
		pid = fork();
		if (pid == 0)
		{
			if (exe == 0)
			{
				execve(token, token_args, environ);
			}
		}
		else
			wait(NULL);
		}
		i--;
	}
	free(line);
}
