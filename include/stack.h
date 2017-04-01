#pragma once

#include <stdlib.h>
#include "types.h"

typedef struct{
	i64* data;
	i64 length;
	i64 sp;
} stack_t;

i64 push(stack_t*, i64);
i64 pop(stack_t*);
void grow_stack(stack_t*);
i64* allocate_stack_data(size_t);
void init_stack(stack_t*);

#ifdef TEST
void print_head(stack_t const*);
void preety_print(stack_t const*);
#endif
