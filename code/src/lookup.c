#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "lookup.h"
#include "hashmap.h"

struct table* init_table()
{
	struct table* lookup = malloc(sizeof(*lookup) + sizeof(struct HashCell*) * LENGTH);

	lookup->free_addr = 0;

	for (int i = 0; i < LENGTH; i++)
		lookup->map[i] = NULL;

	table_insert_addresses(lookup);

	return lookup;
}

void table_insert_addresses(struct table* lookup)
{
	// insert predefined addresses
	table_insert(lookup, "R0",  -1, 0, 0);
	table_insert(lookup, "R1",  -1, 0, 0);
	table_insert(lookup, "R2",  -1, 0, 0);
	table_insert(lookup, "R3",  -1, 0, 0);
	table_insert(lookup, "R4",  -1, 0, 0);
	table_insert(lookup, "R5",  -1, 0, 0);
	table_insert(lookup, "R6",  -1, 0, 0);
	table_insert(lookup, "R7",  -1, 0, 0);
	table_insert(lookup, "R8",  -1, 0, 0);
	table_insert(lookup, "R9",  -1, 0, 0);
	table_insert(lookup, "R10", -1, 0, 0);
	table_insert(lookup, "R11", -1, 0, 0);
	table_insert(lookup, "R12", -1, 0, 0);
	table_insert(lookup, "R13", -1, 0, 0);
	table_insert(lookup, "R14", -1, 0, 0);
	table_insert(lookup, "R15", -1, 0, 0);

	table_insert(lookup, "SP",   0, 0, 0);
	table_insert(lookup, "LCL",  1, 0, 0);
	table_insert(lookup, "ARG",  2, 0, 0);
	table_insert(lookup, "THIS", 3, 0, 0);
	table_insert(lookup, "THAT", 4, 0, 0);

	table_insert(lookup, "SCREEN", 16384, 0, 0);
	table_insert(lookup, "KBD",    24576, 0, 0);
}


void table_insert(struct table* lookup, char key[], int value, int linenum,
	       	int type)
{
	struct data data;
	data.value   = value;
	data.linenum = linenum;
	data.type    = type;

	// if data = -1, use the next free address
	if (data.value < 0)
		data.value = lookup->free_addr++;

	map_insert(lookup->map, key, (void*)&data, sizeof(data));
}

int table_delete(struct table* lookup, char key[])
{
	return map_delete(lookup->map, key);
}

int table_exists(struct table* lookup, char key[])
{
	return map_exists(lookup->map, key);
}

struct data* table_find(struct table* lookup, char key[])
{
	return (struct data*)map_find(lookup->map, key);
}

void free_table(struct table* lookup)
{
	struct HashCell* cell;
	struct HashCell* prev;

	for (int i = 0; i < LENGTH; i++)
	{
		cell = lookup->map[i];

		if (cell == NULL)
			continue;

		while (cell->next != NULL)
		{
			prev = cell;
			cell = cell->next;
			free(prev);
		} 

		free(cell);
	}

	free(lookup);
}

void print_table(struct table* lookup)
{
	struct HashCell* cell = lookup->map[0];

	printf("******************************************************************\n");
	printf("EQU:\n");
	printf("******************************************************************\n");
	for (int i = 1; i < LENGTH; i++)
	{
		while (cell != NULL)
		{
			if (((struct data*)(cell->data))->type == 0)
			{
				printf("key: %s, value: %d, line num: %d\n",
					cell->key,
					((struct data*)(cell->data))->value,
					((struct data*)(cell->data))->linenum);
			}
			cell = cell->next;
		} 
		cell = lookup->map[i];
	}


	cell = lookup->map[0];

	printf("******************************************************************\n");
	printf("ROM:\n");
	printf("******************************************************************\n");
	for (int i = 1; i < LENGTH; i++)
	{
		while (cell != NULL)
		{
			if (((struct data*)(cell->data))->type == 1)
			{
				printf("key: %s, value: %d, line num: %d\n",
					cell->key,
					((struct data*)(cell->data))->value,
					((struct data*)(cell->data))->linenum);
			}
			cell = cell->next;
		} 
		cell = lookup->map[i];
	}

	cell = lookup->map[0];

	printf("******************************************************************\n");
	printf("RAM:\n");
	printf("******************************************************************\n");
	for (int i = 1; i < LENGTH; i++)
	{
		while (cell != NULL)
		{
			if (((struct data*)(cell->data))->type == 2)
			{
				printf("key: %s, value: %d, line num: %d\n",
					cell->key,
					((struct data*)(cell->data))->value,
					((struct data*)(cell->data))->linenum);
			}
			cell = cell->next;
		} 
		cell = lookup->map[i];
	}
}
