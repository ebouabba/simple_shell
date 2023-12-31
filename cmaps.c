#include "shell.h"

/**
 * _clear_entry - free cated for an entry in the hash table.
 *
 * @data :  entry data
 *
 * Return: nothing
 */
void _clear_entry(void *data)
{
	entry_t *entry;

	entry = data;
	free(entry->key);
	free(entry->value);
	free(data);
}
