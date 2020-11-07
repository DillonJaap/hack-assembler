#ifndef HASHMAP_H
#define HASHMAP_H
#define LENGTH 528

#include <stdint.h>
#include <stdlib.h>

struct HashCell 
{
	struct HashCell* next;
	void* data;
	char key[0];
};

uint32_t hash_string(char* s);
struct HashCell* init_cell(char key[], void* data, size_t data_size);
void map_insert(struct HashCell* map[], char key[], void* data, size_t data_size);
int map_delete(struct HashCell* map[], char key[]);
int map_exists(struct HashCell* map[], char key[]);
void* map_find(struct HashCell* map[], char key[]);

#endif
