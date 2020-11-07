#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "assembler.h"
#include "parser.h"
#include "errors.h"
#include "code.h"
#include "lookup.h"
#include "comptable.h"
#include "conversions.h"


// scan for errors and build symbol table
// returns number of errors
uint64_t preparse(FILE* f, struct table* lookup)
{
	struct HashCell** map = init_comp_table();

	int line_num    = 0;
	int cur_addr    = 0;
	int num         = 0;

	uint8_t  error_code = 0;
	uint64_t num_errors = 0;

	int type = 0;

	char cmd[MAX_LEN];
	char field[MAX_LEN];
	char value [MAX_LEN];

	fseek(f, 0L, SEEK_SET);

	while(is_more_cmds(f))
	{
		line_num += get_next_cmd(cmd, f);
		type = get_cmd_type(cmd);

		error_code  = errors_in_command(lookup, map, cmd);
		num_errors += get_num_errors(error_code);
		print_error(cmd, error_code, line_num);

		if (type == L_COMMAND && num_errors == 0)
		{
			get_symbol_field(field, cmd);
			table_insert(lookup, field, cur_addr, line_num, 1);
		}
		else if (type == DIRECTIVE && num_errors == 0)
		{
			get_directive_fields(field, value, cmd);
			num = get_dec_num(value);
			table_insert(lookup, field, num, line_num, 0);
		}
		else
		{
			cur_addr++;
		}
	}

	return num_errors;
}

void assemble(FILE* f, FILE* out, int print)
{
	struct table* lookup = init_table(); 
	struct HashCell** map = init_comp_table();

	char cmd[MAX_LEN];
	char code[MAX_LEN];

	int line_num = 0;
	int type = 0;
	uint64_t errors = 0;

	if ((errors = preparse(f, lookup)) > 0)
	{
		printf("+--------------------- ERROR ---------------------+\n");
		printf("| Program did not assemble... %5lu errors found  |\n", errors);
		printf("+-------------------------------------------------+\n");
		goto free;
	}

	fseek(f, 0L, SEEK_SET);
	while(is_more_cmds(f))
	{
		line_num += get_next_cmd(cmd, f);
		type = get_cmd_type(cmd);

		if (type == C_COMMAND)
		{
			fputs("111", out);

			get_comp_code(map, code, cmd);
			fputs(code, out);

			get_dest_code(code, cmd);
			fputs(code, out);

			get_jump_code(code, cmd);
			fputs(code, out);
			fputc('\n', out);
		}
		else if (type == A_COMMAND)
		{
			fputc('0', out);
			get_symbol_code(lookup, code, cmd, line_num);
			fputs(code, out);
			fputc('\n', out);
		}
	}

	if (print)
		print_table(lookup);

	free:
		free_table(lookup);
}
