#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comptable.h"
#include "hashmap.h"


struct HashCell** init_comp_table()
{
	struct HashCell** map = malloc(sizeof(struct HashCell**) * LENGTH);
	for (int i = 0; i < LENGTH; i++)
			map[i] = NULL;

	char temp[8];
	size_t tmp_size = sizeof(temp);

	strcpy(temp, "0101010");
	map_insert(map, "0", (void*)temp, tmp_size);
	strcpy(temp, "0111111");
	map_insert(map, "1", (void*)temp, tmp_size);
	strcpy(temp, "0111010");
	map_insert(map, "-1", (void*)temp, tmp_size);
	strcpy(temp, "0001100");
	map_insert(map, "D", (void*)temp, tmp_size);
	strcpy(temp, "0110000");
	map_insert(map, "A", (void*)temp, tmp_size);
	strcpy(temp, "0001101");
	map_insert(map, "!D", (void*)temp, tmp_size);
	strcpy(temp, "0110001");
	map_insert(map, "!A", (void*)temp, tmp_size);
	strcpy(temp, "0001111");
	map_insert(map, "-D", (void*)temp, tmp_size);
	strcpy(temp, "0110011");
	map_insert(map, "-A", (void*)temp, tmp_size);
	strcpy(temp, "0011111");
	map_insert(map, "D+1", (void*)temp, tmp_size);
	strcpy(temp, "0110111");
	map_insert(map, "A+1", (void*)temp, tmp_size);
	strcpy(temp, "0001110");
	map_insert(map, "D-1", (void*)temp, tmp_size);
	strcpy(temp, "0110010");
	map_insert(map, "A-1", (void*)temp, tmp_size);
	strcpy(temp, "0000010");
	map_insert(map, "D+A", (void*)temp, tmp_size);
	strcpy(temp, "0010011");
	map_insert(map, "D-A", (void*)temp, tmp_size);
	strcpy(temp, "0000111");
	map_insert(map, "A-D", (void*)temp, tmp_size);
	strcpy(temp, "0000000");
	map_insert(map, "D&A", (void*)temp, tmp_size);
	strcpy(temp, "0010101");
	map_insert(map, "D|A", (void*)temp, tmp_size);
	strcpy(temp, "1110000");
	map_insert(map, "M", (void*)temp, tmp_size);
	strcpy(temp, "1110001");
	map_insert(map, "!M", (void*)temp, tmp_size);
	strcpy(temp, "1110011");
	map_insert(map, "-M", (void*)temp, tmp_size);
	strcpy(temp, "1110111");
	map_insert(map, "M+1", (void*)temp, tmp_size);
	strcpy(temp, "1110010");
	map_insert(map, "M-1", (void*)temp, tmp_size);
	strcpy(temp, "1000010");
	map_insert(map, "D+M", (void*)temp, tmp_size);
	strcpy(temp, "1010011");
	map_insert(map, "D-M", (void*)temp, tmp_size);
	strcpy(temp, "1000111");
	map_insert(map, "M-D", (void*)temp, tmp_size);
	strcpy(temp, "1000000");
	map_insert(map, "D&M", (void*)temp, tmp_size);
	strcpy(temp, "1010101");
	map_insert(map, "D|M", (void*)temp, tmp_size);

	strcpy(temp, "0010000");
	map_insert(map, "!D&A", (void*)temp, tmp_size);
	strcpy(temp, "0000100");
	map_insert(map, "D&!A", (void*)temp, tmp_size);
	strcpy(temp, "0010100");
	map_insert(map, "!D&!A", (void*)temp, tmp_size);
	strcpy(temp, "0000001");
	map_insert(map, "!(D&A)", (void*)temp, tmp_size);
	strcpy(temp, "0010001");
	map_insert(map, "!(!D&A)", (void*)temp, tmp_size);
	strcpy(temp, "0000101");
	map_insert(map, "!(D&!A)", (void*)temp, tmp_size);
	strcpy(temp, "0010101");
	map_insert(map, "!(!D&!A)", (void*)temp, tmp_size);
	strcpy(temp, "0000101");
	map_insert(map, "!D|A", (void*)temp, tmp_size);
	strcpy(temp, "0010001");
	map_insert(map, "D|!A", (void*)temp, tmp_size);
	strcpy(temp, "0000001");
	map_insert(map, "!D|!A", (void*)temp, tmp_size);
	strcpy(temp, "0010100");
	map_insert(map, "!(D|A)", (void*)temp, tmp_size);
	strcpy(temp, "0000100");
	map_insert(map, "!(!D|A)", (void*)temp, tmp_size);
	strcpy(temp, "0010000");
	map_insert(map, "!(D|!A)", (void*)temp, tmp_size);
	strcpy(temp, "0000000");
	map_insert(map, "!(!D|!A)", (void*)temp, tmp_size);

	strcpy(temp, "1010000");
	map_insert(map, "!D&M", (void*)temp, tmp_size);
	strcpy(temp, "1000100");
	map_insert(map, "D&!M", (void*)temp, tmp_size);
	strcpy(temp, "1010100");
	map_insert(map, "!D&!M", (void*)temp, tmp_size);
	strcpy(temp, "1000001");
	map_insert(map, "!(D&M)", (void*)temp, tmp_size);
	strcpy(temp, "1010001");
	map_insert(map, "!(!D&M)", (void*)temp, tmp_size);
	strcpy(temp, "1000101");
	map_insert(map, "!(D&!M)", (void*)temp, tmp_size);
	strcpy(temp, "1010101");
	map_insert(map, "!(!D&!M)", (void*)temp, tmp_size);
	strcpy(temp, "1000101");
	map_insert(map, "!D|M", (void*)temp, tmp_size);
	strcpy(temp, "1010001");
	map_insert(map, "D|!M", (void*)temp, tmp_size);
	strcpy(temp, "1000001");
	map_insert(map, "!D|!M", (void*)temp, tmp_size);
	strcpy(temp, "1010100");
	map_insert(map, "!(D|M)", (void*)temp, tmp_size);
	strcpy(temp, "1000100");
	map_insert(map, "!(!D|M)", (void*)temp, tmp_size);
	strcpy(temp, "1010000");
	map_insert(map, "!(D|!M)", (void*)temp, tmp_size);
	strcpy(temp, "1000000");
	map_insert(map, "!(!D|!M)", (void*)temp, tmp_size);
	
	return map;
}
