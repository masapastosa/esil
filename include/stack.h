#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "types.h"

typedef struct{
	i32* data;
	i32 length;
	i32 sp;
} stack_t;

i32 push(stack_t*, i32);
i32 pop(stack_t* const);
i32 head(stack_t*);
void grow_stack(stack_t*);
i32* allocate_stack_data(size_t);
void init_stack(stack_t*);

#ifdef TEST
void print_head(stack_t const*);
void preety_print(stack_t const*);
#endif

#endif
