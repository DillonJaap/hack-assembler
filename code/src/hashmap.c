#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "hashmap.h"

uint32_t hash_string(char* s)
{
	int hash = 7;
	for (; *s != '\0'; s++)
		hash = hash * 31 + *s;
	return hash;

}

struct HashCell* init_cell(char key[], void* data, size_t data_size)
{
	int length = strlen(key);
	struct HashCell* cell =  malloc( sizeof(*cell) + sizeof(char)
		       	* (length + 1));

	strcpy(cell->key, key);
	cell->next = NULL;
	
	// copy data 
	cell->data = malloc(data_size);
	for (int i = 0; i < data_size; i++)
		*(char*)(cell->data + i) = *(char*)(data + i);
			
	return cell;
}

void map_insert(struct HashCell* map[], char key[], void* data, size_t data_size)
{
	uint32_t hash = hash_string(key);
	uint32_t index = hash % LENGTH;
	struct HashCell* cell;

	// first cell in current row
	if (map[index] == NULL)
	{
		map[index] = init_cell(key, data, data_size);
		return;
	}
		
	cell = map[index]; 

	for (;;)
	{
		if (strcmp(cell->key, key) == 0)
		{
			free(cell->data);
			cell->data = data;
			return;
		}
		else if (cell->next == NULL)
		{
			cell->next = init_cell(key, data, data_size);
			return;
		}

		cell = cell->next;
	}

}

int map_delete(struct HashCell* map[], char key[])
{
	uint32_t hash = hash_string(key);
	uint32_t index = hash % LENGTH;
	struct HashCell* cell = map[index];

	// first cell in current row
	if (cell == NULL)
		return 0;

	if(strcmp(map[index]->key, key) == 0)
	{
		struct HashCell* tmp = map[index];
		map[index] = map[index]->next;
		free(tmp->data);
		free(tmp);
		return 1;
	}

	for (;;)
	{
		if (cell->next == NULL)
			return 0;
		else if (strcmp(cell->next->key, key) == 0)
		{
			struct HashCell* tmp = cell->next;
			cell->next = cell->next->next;
			free(tmp->data);
			free(tmp);
			return 1;
		}
		cell = cell->next;
	}
}

int map_exists(struct HashCell* map[], char key[])
{
	uint32_t hash = hash_string(key);
	uint32_t index = hash % LENGTH;
	struct HashCell* cell = map[index];

	// first cell in current row
	if (cell == NULL)
		return 0;

	while (strcmp(cell->key, key) != 0)
	{
		if (cell->next == NULL)
			return 0;

		 cell = cell->next;
	}

	return 1;
}

void* map_find(struct HashCell* map[], char key[])
{
	uint32_t hash = hash_string(key);
	uint32_t index = hash % LENGTH;
	struct HashCell* cell = map[index];

	// first cell in current row
	if (cell == NULL)
		return 0;

	while (strcmp(cell->key, key) != 0)
	{
		if (cell->next == NULL)
			return 0;

		 cell = cell->next;
	}

	return cell->data;
}
