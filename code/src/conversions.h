#ifndef CONVERSIONS_H
#define CONVERSIONS_H

void dec_to_bin(int dec, char* bin);
void get_bin_code_from_hex(char* bin, char hex);
void hex_to_bin(char* bin, char* hex);
void get_bin_num(char* dest, char* src);
int get_dec_num(char* num);
void add_leading_zeros(char* dest, int length);

#endif
