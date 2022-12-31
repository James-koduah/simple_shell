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
		return (NULL);
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
