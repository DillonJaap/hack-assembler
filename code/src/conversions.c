#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"

// convert decimal int to n-bit binary string
void dec_to_bin(int dec, char* bin)
{
	printf("%d\n", dec);
	char temp;
	bin[0] = '\0';
	
	int i;
	for (i = 0; (dec >> i) > 0; i++)
	{
		if ((dec >> i) & 1)
		{
			bin[i] = '1';
		}
		else
			bin[i] = '0';
	}
	bin[i] = '\0';

	// reverse
	for (char* end = bin + i-1; bin < end; bin++, end--)
	{
		temp = *bin;
		*bin = *end;
		*end = temp;
	}
}

void get_bin_code_from_hex(char* bin, char hex)
{
	switch(hex)
	{
		case '0': strcat(bin, "0000");
			break;
		case '1': strcat(bin, "0001");
			break;
		case '2': strcat(bin, "0010");
			break;
		case '3': strcat(bin, "0011");
			break;
		case '4': strcat(bin, "0100");
			break;
		case '5': strcat(bin, "0101");
			break;
		case '6': strcat(bin, "0110");
			break;
		case '7': strcat(bin, "0111");
			break;
		case '8': strcat(bin, "1000");
			break;
		case '9': strcat(bin, "1001");
			break;
		case 'a':
		case 'A': strcat(bin, "1010");
			break;
		case 'b':
		case 'B': strcat(bin, "1011");
			break;
		case 'c':
		case 'C': strcat(bin, "1100");
			break;
		case 'd':
		case 'D': strcat(bin, "1101");
			break;
		case 'e':
		case 'E': strcat(bin, "1110");
			break;
		case 'f':
		case 'F': strcat(bin, "1111");
			break;
		default:
			printf("Invalid hex input");
	}
}

// convert hex string to n-bit binary string
void hex_to_bin(char* bin, char* hex)
{
	bin[0] = '\0';

	for (int i = 0; hex[i] != '\0'; i++)
		get_bin_code_from_hex(bin, hex[i]);

	char* c = bin;
	for (; *c == '0'; c++);
	strcpy(bin, c);
}

void get_bin_num(char* dest, char* src)
{
	int offset = 2;

	if (!strncmp("0x", src, offset) || !strncmp("0X", src, offset))
		hex_to_bin(dest, src + offset);
	else if (!strncmp("0b", src, offset) || !strncmp("0B", src, offset))
	{
		//get rid of leading zeros
		while(*(src + offset) == '0')
			offset++;
		strcpy(dest, src + offset);
	}
	else
		dec_to_bin(atoi(src), dest);
}

int get_dec_num(char* num)
{
	if (!strncmp("0b", num, 2) || !strncmp("0B", num, 2))
		return (int)strtol(num + 2, NULL, 2);
	else
		return (int)strtol(num, NULL, 2);
}

void add_leading_zeros(char* dest, int length)
{
	char bin[33] = "\0";

	int i; 
	for (i = 0; i < (length - strlen(dest)); i++)
		bin[i] = '0';
	bin[i] = '\0';
	
	strcat(bin, dest);
	strcpy(dest, bin);
}
