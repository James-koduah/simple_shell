#include "main.h"
/**
 * main - kskksks
 * @ac: kkskks
 * @av: ksksk
 * Return: nothing
 */

int main(int ac, char *av[])
{
	int i, b;
	ssize_t char_read;
	size_t n;
	char *ptr;
	char *lineptr = NULL;
	pid_t pid;
	char *array[15];
	char *delim = " \n";

	while (ac)
	{
		printf("#cisfun$ ");
		char_read = getline(&lineptr, &n, stdin);
		if (char_read == -1)
		{
			printf("\nExiting shell...\n");
			free(lineptr);
			exit(99);
		}
		i = 0;
		ptr = strtok(lineptr, delim);
		while(ptr)
		{
			array[i] = ptr;
			i++;
			ptr = strtok(NULL, delim);
		}
		array[i] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror(av[0]);
			return (1);
		}
		if (pid == 0)
		{
			if (execve(array[0], array, NULL) == -1)
			{
				perror(av[0]);
				exit(98);
			}
		}
		else
			wait(&b);
	}
	return (0);
}
