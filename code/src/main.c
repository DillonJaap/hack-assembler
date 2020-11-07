#include <stdio.h>
#include <string.h>
#include "assembler.h"


int main(int argc, char* argv[])
{

	int print = 0; 
	char file_path[128] = "";
	char out_path[128]  = "hack/out.hack";

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-p") == 0)
			print = 1;
		if (strcmp(argv[i], "-o") == 0)
			strcpy(out_path, argv[++i]);
		else
			strcpy(file_path, argv[i]);
	}

	if (strcmp(file_path, "") == 0)
	{
		printf("ERROR: no file given >:(\n");
		return 1;
	}

	FILE* f = fopen(file_path, "r");
	FILE* out = fopen(out_path, "w");

	assemble(f, out, print);
	fclose(f);
	fclose(out);
	return 0;
}
