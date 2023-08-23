#include "shell.h"

/**
* strduppp - function that takes a string and duplicates
* it and return new pointer of duplicated string
*
* @str: string to be duplicated
* Return: new char pointer to the new string
*/
char   *strduppp(const char *str)
{
	char *new_str;
	size_t  len, iterator;

	len = mYstrlen(str);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	new_str[len] = 0;
	iterator = 0;
	while (iterator < len)
	{
		new_str[iterator] = str[iterator];
		iterator++;
	}
	return (new_str);
}
