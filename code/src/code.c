#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "code.h"
#include "lookup.h"
#include "hashmap.h"
#include "conversions.h"
#include "parser.h"

void get_comp_code(struct HashCell* map[], char* code, char* cmd)
{
	char comp[33];
	get_comp_field(comp, cmd);

	if (comp[0] == 'X' || comp[0] == 'x')
	{
		hex_to_bin(code, comp + 1);
		add_leading_zeros(code, 7);
	}
	else
	{
		char* temp = (char*)map_find(map, comp);
		strcpy(code, temp);
	}
}

void get_dest_code(char* code, char* cmd)
{
	char dest[33];
	get_dest_field(dest, cmd);

	strcpy(code, "000");

	for(int i = 0; dest[i] != '\0'; i++)
	{
		if (dest[i] == 'A')
			code[0] = '1';
		else if (dest[i] == 'D')
			code[1] = '1';
		else if (dest[i] == 'M')
			code[2] = '1';
	}
}

void get_jump_code(char* code, char* cmd)
{
	char jump[33];
	get_jump_field(jump, cmd);

	strcpy(code, "000");

	if (strcmp(jump, "JGT") == 0)
		strcpy(code, "001");
	else if (strcmp(jump, "JEQ") == 0)
		strcpy(code, "010");
	else if (strcmp(jump, "JGE") == 0)
		strcpy(code, "011");
	else if (strcmp(jump, "JLT") == 0)
		strcpy(code, "100");
	else if (strcmp(jump, "JNE") == 0)
		strcpy(code, "101");
	else if (strcmp(jump, "JLE") == 0)
		strcpy(code, "110");
	else if (strcmp(jump, "JMP") == 0)
		strcpy(code, "111");
}

void get_symbol_code(struct table* lookup, char* code, char* cmd, int line_num)
{
	char symbol[33];
	get_symbol_field(symbol, cmd);
	printf("%d ", line_num);

	// check if label
	if (symbol[0] < '0' || symbol[0] > '9')
	{
		if (!table_exists(lookup, symbol))
			table_insert(lookup, symbol, -1, line_num, 2);

		struct data* data = table_find(lookup, symbol);
		dec_to_bin(data->value, code);
	}
	else
		get_bin_num(code, symbol);
	//printf("%s\n", code);

	add_leading_zeros(code, 15);
}
