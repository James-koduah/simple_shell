#include "main.h"

/**
 * only_spaces - check if the input is only spaces
 * @token: string
 * Return: greater than 0 if string is not empty
 */
int only_spaces(char *token)
{
	int i, len, yes;

	yes = 0;
	len = strlen(token);
	for (i = 0; i < len; i++)
	{
		if (token[i] == ' ' || token[i] == '\n')
			yes += 0;
		else
			yes++;
	}
	return (yes);
}

/**
 * search_path - search for the command
 * @str: the command
 * Return: modified command or NULL if the command doesn't exist
 */
char *search_path(const char *str)
{
	char *path, *token, *tmp;
	char fullpath[1024];

	if (str[0] == '/' || str[0] == '.')
	{
		if (access(str, X_OK) == 0)
			return (strdup(str));
		else
			return (NULL);
	}

	path = getenv("PATH");
	if (path == NULL)
	{
		perror("./hsh");
		return (NULL);
	}
	tmp = strdup(path);
	if (tmp == NULL)
		return (NULL);
	token = strtok(tmp, ":");
	while (token != NULL)
	{
		strcpy(fullpath, token);
		strcat(fullpath, "/");
		strcat(fullpath, str);
		if (access(fullpath, X_OK) == 0)
		{

			free(tmp);
			return (strdup(fullpath));
		}
		token = strtok(NULL, ":");
	}

	free(tmp);
	return (NULL);
}


/**
 * print_env - env builtin that prints current environment
 *
 * Return: void
 */
void print_env(void)
{
	char **env; /* variables to store environ and name, value keys */
	char *name, *value;
	/* iterate through all env variables */
	for (env = environ; *env != NULL; env++)
	{
		name = *env; /* get env name and value */
		value = getenv(name);

		printf("%s=%s\n", name, value);
	}
}


/**
 * exit_env - Used to reduce the number of lines in the main function
 * @str: The command from the shell either (exit) or (env);
 * @line: A buffer from the main function to be freed
 * @line_copy: A buffer from the main function to be freed
 * Return: Nohthing
 */
int exit_env(char *str)
{
	if (strcmp(str, "exit") == 0) /* exit */
	{
		printf("exit\n");
		return (1);
	}
	if (strcmp(str, "env") == 0) /* print env vars */
	{
		print_env();
	}
	return (0);
}
