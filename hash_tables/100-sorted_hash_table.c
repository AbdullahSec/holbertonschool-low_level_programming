#include "hash_tables.h"

/**
 * shash_table_create - creates a sorted hash table
 * @size: the size of the array
 *
 * Return: a pointer to the new sorted hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	unsigned long int i;

	if (size == 0)
		return (NULL);

	ht = malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
	ht->array = malloc(sizeof(shash_node_t *) * size);
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	for (i = 0; i < size; i++)
		ht->array[i] = NULL;
	ht->shead = NULL;
	ht->stail = NULL;
	return (ht);
}

/**
 * make_snode - creates a sorted hash node with duplicated key and value
 * @key: the key to store
 * @value: the value to store
 *
 * Return: pointer to the new node, or NULL on failure
 */
shash_node_t *make_snode(const char *key, const char *value)
{
	shash_node_t *new;

	new = malloc(sizeof(shash_node_t));
	if (new == NULL)
		return (NULL);
	new->key = strdup(key);
	if (new->key == NULL)
	{
		free(new);
		return (NULL);
	}
	new->value = strdup(value);
	if (new->value == NULL)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->sprev = NULL;
	new->snext = NULL;
	return (new);
}

/**
 * insert_sorted - inserts a node into the sorted linked list by key
 * @ht: the sorted hash table
 * @new: the node to insert
 */
void insert_sorted(shash_table_t *ht, shash_node_t *new)
{
	shash_node_t *current;

	if (ht->shead == NULL)
	{
		ht->shead = new;
		ht->stail = new;
		return;
	}
	if (strcmp(new->key, ht->shead->key) < 0)
	{
		new->snext = ht->shead;
		ht->shead->sprev = new;
		ht->shead = new;
		return;
	}
	current = ht->shead;
	while (current->snext != NULL && strcmp(new->key, current->snext->key) > 0)
		current = current->snext;
	new->snext = current->snext;
	new->sprev = current;
	if (current->snext != NULL)
		current->snext->sprev = new;
	else
		ht->stail = new;
	current->snext = new;
}

/**
 * shash_table_set - adds or updates an element in the sorted hash table
 * @ht: the sorted hash table
 * @key: the key (cannot be an empty string)
 * @value: the value associated with the key (duplicated)
 *
 * Return: 1 if it succeeded, 0 otherwise
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *new, *current;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	current = ht->array[index];
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			return (1);
		}
		current = current->next;
	}
	new = make_snode(key, value);
	if (new == NULL)
		return (0);
	new->next = ht->array[index];
	ht->array[index] = new;
	insert_sorted(ht, new);
	return (1);
}

/**
 * shash_table_get - retrieves a value associated with a key
 * @ht: the sorted hash table
 * @key: the key to look for
 *
 * Return: the value associated with the key, or NULL if not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *current;
	unsigned long int index;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);
	current = ht->array[index];
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/**
 * shash_table_print - prints a sorted hash table using the sorted list
 * @ht: the sorted hash table
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *current;
	int first;

	if (ht == NULL)
		return;

	printf("{");
	first = 1;
	current = ht->shead;
	while (current != NULL)
	{
		if (first == 0)
			printf(", ");
		printf("'%s': '%s'", current->key, current->value);
		first = 0;
		current = current->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - prints a sorted hash table in reverse order
 * @ht: the sorted hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *current;
	int first;

	if (ht == NULL)
		return;

	printf("{");
	first = 1;
	current = ht->stail;
	while (current != NULL)
	{
		if (first == 0)
			printf(", ");
		printf("'%s': '%s'", current->key, current->value);
		first = 0;
		current = current->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - deletes a sorted hash table
 * @ht: the sorted hash table
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *current;
	shash_node_t *tmp;

	if (ht == NULL)
		return;

	current = ht->shead;
	while (current != NULL)
	{
		tmp = current->snext;
		free(current->key);
		free(current->value);
		free(current);
		current = tmp;
	}
	free(ht->array);
	free(ht);
}
