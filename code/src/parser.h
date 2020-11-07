#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include "lookup.h"

#define MAX_LEN 128

enum COMMAND
{
	A_COMMAND,
	C_COMMAND,
	L_COMMAND,
	DIRECTIVE,
};

char fgetcskip(FILE *f);
char* strcpytil(char* dest, const char* src, const char* s);
int is_more_cmds(FILE *f);
int get_next_cmd(char* cmd, FILE *f);
int get_cmd_type(const char* cmd);
void get_comp_field(char* comp, const char* cmd);
void get_dest_field(char* dest, const char* cmd);
void get_jump_field(char* jump, const char* cmd);
void get_symbol_field(char* symbol, const char* cmd);
void get_directive_fields(char* label, char* value, const char* cmd);

#endif
