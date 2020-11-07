#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "errors.h"
#include "hashmap.h"
#include "conversions.h"
#include "parser.h"

// returns error code of command
int errors_in_command(struct table* lookup, struct HashCell* map[], char* cmd)
{
	int type = get_cmd_type(cmd);
	uint8_t error_code = 0;

	switch(type)
	{
		case L_COMMAND: error_code = errors_in_lcmd(lookup, cmd);      break;
		case C_COMMAND: error_code = errors_in_ccmd(map, cmd);         break;
		case A_COMMAND: error_code = errors_in_acmd(cmd);              break;
		case DIRECTIVE: error_code = errors_in_directive(lookup, cmd); break;
	}

	return error_code;
}

void print_error(char* cmd, uint8_t error_code, int line_num)
{
	int type = get_cmd_type(cmd);
	char type_name[16];

	if (error_code == E_SUCCESS)
		return;

	switch (type)
	{
		case C_COMMAND: strcpy(type_name, "c-type");    break;
		case L_COMMAND: strcpy(type_name, "l-type");    break;
		case A_COMMAND: strcpy(type_name, "a-type");    break;
		case DIRECTIVE: strcpy(type_name, "directive"); break;
	}

	printf("ERROR %s instruction: ", type_name);

	if (error_code & E_TO_LARGE)
	{
		if (type == C_COMMAND)
			printf("value greater than 7-bit comp field size, ");
		else
			printf("value greater than 15-bit int size, ");
	}
	if (error_code & E_NAN)
		printf("value is not a number, ");
	if (error_code & E_ALREADY_EXIST)
		printf("previously defined symbol, ");
	if (error_code & E_ILLEGAL_CHAR)
		printf("illegal character in symbol, ");
	if (error_code & E_ILLEGAL_DEST)
		printf("unrecognized dest field, ");
	if (error_code & E_ILLEGAL_COMP)
		printf("unrecognized comp field, ");
	if (error_code & E_ILLEGAL_JUMP)
		printf("unrecognized jump field, ");

	printf("\nLine %d: \n\t%s\n\n", line_num, cmd);
	
	return;
}

// gets the number of errors from an error code
int get_num_errors(uint8_t error_code)
{
	int errors = 0;
	int end = sizeof(error_code) * 8;

	for (int i = 0; i < end; i++)
		errors += error_code >> i & 1;

	return errors;
}

int errors_in_ccmd(struct HashCell* map[], char* cmd)
{
	uint8_t error_code = 0;
	char field[MAX_LEN];

	get_dest_field(field, cmd);
	error_code += errors_in_dest(field);
	get_comp_field(field, cmd);
	error_code += errors_in_comp(map, field);
	get_jump_field(field, cmd);
	error_code += errors_in_jump(field);
	
	return error_code;
}

int errors_in_acmd(char* cmd)
{
	char symbol[MAX_LEN];

	get_symbol_field(symbol, cmd);
	return errors_in_symbol(symbol);
}

int errors_in_lcmd(struct table* lookup, char* cmd)
{
	char symbol[MAX_LEN];

	get_symbol_field(symbol, cmd);
	if (table_exists(lookup, symbol))
		return E_ALREADY_EXIST;
	else
		return errors_in_symbol(symbol);

}

int errors_in_directive(struct table* lookup, char* cmd)
{
	char label[MAX_LEN];
	char value[MAX_LEN];

	uint8_t error_code = 0;

	get_directive_fields(label, value, cmd);

	if (table_exists(lookup, label))
		return E_ALREADY_EXIST;

	if (!name_is_valid(label))
		return E_ILLEGAL_CHAR;

	if (!is_num(value))
		error_code += E_NAN;
	else if (!num_is_correct_size(value, 15))
		error_code += E_TO_LARGE;

	return error_code;
}

int errors_in_comp(struct HashCell* map[], char* comp)
{

	if (comp[0] == 'X' || comp[0] == 'x')
	{
		char test_num[MAX_LEN] = "0x";
		strcat(test_num, comp + 1);

		if (!is_num(test_num))
			return E_NAN;
		else if (!num_is_correct_size(test_num, 7))
			return E_TO_LARGE;
		else
			return E_SUCCESS;
	}
	else if (!map_exists(map, comp))
		return E_ILLEGAL_COMP;
	else
		return E_SUCCESS;
}

int errors_in_dest(char* dest)
{
	if (strcmp(dest, "A") != 0 && strcmp(dest, "M") != 0 
			&& strcmp(dest, "D")   != 0 && strcmp(dest, "MD") != 0 
			&& strcmp(dest, "AM")  != 0 && strcmp(dest, "AD") != 0 
			&& strcmp(dest, "AMD") != 0 && strcmp(dest, "")   != 0)
		return E_ILLEGAL_DEST;
	else
		return E_SUCCESS;
}

int errors_in_jump(char* jump)
{
	if (strcmp(jump, "JGT") != 0 && strcmp(jump, "JEQ") != 0 
			&& strcmp(jump, "JGE") != 0 && strcmp(jump, "JLT") != 0 
			&& strcmp(jump, "JNE") != 0 && strcmp(jump, "JLE") != 0 
			&& strcmp(jump, "JMP") != 0 && strcmp(jump, "") != 0)
		return E_ILLEGAL_JUMP;
	else
		return E_SUCCESS;
}


int errors_in_symbol(char* symbol)
{
	if (symbol[0] < '0' || symbol[0] > '9')
	{
		if(!name_is_valid(symbol))
			return E_ILLEGAL_CHAR;
		else
			return E_SUCCESS;
	}

	if (!is_num(symbol))
		return E_NAN;
	else if (!num_is_correct_size(symbol, 15))
		return E_TO_LARGE;
	else
		return E_SUCCESS;
}

int name_is_valid(char* name)
{
	// names cannot start with numbers
	if (!isalpha(name[0]) && name[0] != '.' && name[0] != '_'
			&& name[0] != '$' && name[0] != ':')
		return 0;

	char* valid = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_.$:";
	size_t valid_len = strspn(name, valid);

	if (valid_len != strlen(name))
		return 0;
	return 1;
}

// not greater than 32767 (2^5), or whatever value chosen
int num_is_correct_size(char* num, int bits)
{
	char bin[MAX_LEN];
	get_bin_num(bin, num);

	if (strlen(bin) > bits)
		return 0;
	return 1;
}

int is_num(const char* num)
{
	if (num[0] == '\0')
		return 0;

	char valid[24];

	if (!strncmp("0x", num, 2) || !strncmp("0X", num, 2))
	{
		strcpy(valid, "1234567890abcdefABCDEF");
		num += 2;
	}
	else if (!strncmp("0b", num, 2) || !strncmp("0B", num, 2))
	{
		strcpy(valid, "01");
		num += 2;
	}
	else
		strcpy(valid, "1234567890");

	size_t valid_len = strspn(num, valid);

	if (valid_len != strlen(num))
		return 0;
	return 1;
}
