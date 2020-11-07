#ifndef LOOKUP_H
#define LOOKUP_H

struct table
{
	int free_addr;
	struct HashCell* map[0];
};

struct data {int value, linenum, type;};

struct table* init_table();
void free_table(struct table* lookup);
void table_insert(struct table* lookup, char key[], int value, int linenum, int type);
int table_delete(struct table* lookup, char key[]);
int table_exists(struct table* lookup, char key[]);
struct data* table_find(struct table* lookup, char key[]);
void table_insert_addresses(struct table* lookup);
void print_table(struct table* lookup);

#endif
