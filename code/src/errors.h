#ifndef ERRORS_H
#define ERRORS_H

#include "hashmap.h"
#include "lookup.h"

enum Errors 
{
	E_SUCCESS       = 0,
	E_TO_LARGE      = 1,
	E_NAN           = 2,
	E_ALREADY_EXIST = 4,	
	E_ILLEGAL_CHAR  = 8,
	E_ILLEGAL_DEST  = 16,	
	E_ILLEGAL_COMP  = 32,	
	E_ILLEGAL_JUMP  = 64,	
};

int errors_in_command(struct table* lookup, struct HashCell* map[], char* cmd);
void print_error(char* cmd, uint8_t error_code, int line_num);
int get_num_errors(uint8_t error_code);
int errors_in_ccmd(struct HashCell* map[], char* cmd);
int errors_in_acmd(char* cmd);
int errors_in_lcmd(struct table* lookup, char* cmd);
int errors_in_directive(struct table* lookup, char* cmd);
int errors_in_comp(struct HashCell* map[], char* comp);
int errors_in_dest(char* dest);
int errors_in_jump(char* jump);
int errors_in_symbol(char* symbol);
int name_is_valid(char* name);
int num_is_correct_size(char* num, int bits);
int is_num(const char* num);

#endif
