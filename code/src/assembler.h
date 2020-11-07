#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <stdint.h>
#include "lookup.h"


uint64_t preparse(FILE* f, struct table* lookup);
void assemble(FILE* f, FILE* out, int print);

#endif
