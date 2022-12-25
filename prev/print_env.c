#include "main.h"

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
