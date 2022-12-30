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
