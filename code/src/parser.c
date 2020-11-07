#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "code.h"
#include "lookup.h"
#include "comptable.h"

// fgetc but skip, comments
char fgetcskip(FILE *f)
{
	char prev = '\0';
	char cur  = '\0';

	for (;;)
	{
		prev = cur;
		cur = fgetc(f);

		if (cur == EOF)
			return cur;

		if (prev == '/' && cur =='/')
			while((cur = fgetc(f)) != '\n');

		// ignore Windows' dumb carriage return line endings
		// and potential comments
		if (cur != '/' && cur != '\r') 
			return cur;
	}
}


// copy until you find a char that is in s
char* strcpytil(char* dest, const char* src, const char* s)
{
	while (!strchr(s, *src) && *src != '\0')
		*(dest++) = *(src++);

	*dest = '\0';

	return src;
}

int is_more_cmds(FILE *f)
{
	char c = '\0';

	int pos = ftell(f);
	while ((c = fgetcskip(f)) == '\n'); // loop until non blank line
	fseek(f, pos, SEEK_SET);

	if (c == EOF)
		return 0;
	return 1;
}

// also returns the number of lines it traversed
int get_next_cmd(char* cmd, FILE *f)
{
	int lines = 0;
	int skipspace =  1;

	// skip blank lines
	while (isspace(*cmd = fgetcskip(f)))
	{
		if (*cmd == '\n')
			lines++;
	}

	// only skip spaces if its not a directive
	if (*cmd == '.')
		skipspace = 0;

	int i = 1;
	while ((cmd[i] = fgetcskip(f)) != '\n')
	{
		if (!skipspace || !isblank(cmd[i]))
			i++;

		if (i >= MAX_LEN - 1)
		{
			while (fgetcskip(f) != '\n');
			break;
		}
	}
	cmd[i] = '\0';

	return lines + 1;
}

int get_cmd_type(const char* cmd)
{
	switch(*cmd)
	{
		case '@': return A_COMMAND;
		case '(': return L_COMMAND;
		case '.': return DIRECTIVE;
		default:  return C_COMMAND;
	}
}

void get_comp_field(char* comp, const char* cmd)
{
	if (strchr(cmd, '='))
	{
		cmd = strchr(cmd, '=');
		cmd++;
	}

	strcpytil(comp, cmd, "; \t");
}

void get_dest_field(char* dest, const char* cmd)
{
	*dest = '\0';

	if (strchr(cmd, '='))
		strcpytil(dest, cmd, "=");
}

void get_jump_field(char* jump, const char* cmd)
{
	*jump = '\0';

	if ((cmd = strchr(cmd, ';')))
		strcpytil(jump, cmd + 1, " \t");
}

void get_symbol_field(char* symbol, const char* cmd)
{
	char* c = strcpytil(symbol, cmd + 1, ")");

	if (*cmd == '(' && *c != ')')
		*symbol = '\0';
}

void get_directive_fields(char* label, char* value, const char* cmd)
{
	if (strncmp(".EQU", cmd, 4) != 0)
	{
		*label = '\0';
		*value = '\0';
		return;
	}

	while (!isblank(*(cmd++)));
	cmd = strcpytil(label, cmd, " ");
	
	while (!isblank(*(cmd++)));
	strcpytil(value, cmd, " ");

}
