
#ifndef GEN_STR
#define GEN_STR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void destroy_p_string(void* s);

void *copy_p_string(const void* s);

int print_p_string(FILE* pf, const void* s);

#endif
