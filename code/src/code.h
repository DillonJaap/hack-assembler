#ifndef CODE_H
#define CODE_H

#include "hashmap.h"
#include "lookup.h"

void get_comp_code(struct HashCell* map[], char* code, char* cmd);
void get_dest_code(char* code, char* cmd);
void get_jump_code(char* code, char* cmd);
void get_symbol_code(struct table* lookup, char* code, char* cmd, int line_num);

#endif
