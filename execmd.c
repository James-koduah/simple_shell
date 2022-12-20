#include "main.h"

/**
 * search_path - search the directories listed in PATH
 * for the specified executable
 * @command: the name of the executable to search for
 *
 * Return: a pointer to the full path of the executable,
 * or NULL if it is not found
 */
char *search_path(const char *command)
{
	char *path, *dir, *tmp;
	char full_path[BUFFER_SIZE];

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0) /* exec abs path if exists */
			return (strdup(command));
		else
			return (NULL);
	}

	path = getenv("PATH"); /* get the value of PATH from the environment */
	if (path == NULL)
		return (NULL);
	tmp = strdup(path); /* make a copy of path so we can modify it */
	if (tmp == NULL)
		return (NULL);
	dir = strtok(tmp, ":"); /* search each directory in PATH */
	while (dir != NULL)
	{
		strcpy(full_path, dir); /* construct the full path of the executable */
		strcat(full_path, "/");
		strcat(full_path, command);
		if (access(full_path, X_OK) == 0) /* check if the executable exists */
		{
			free(tmp);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(tmp);
	return (NULL);
}
