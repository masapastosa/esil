#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "../include/types.h"
#include "../include/stack.h"

i64 push(stack_t *stack, i64 value) {
	if ((stack->sp) >= (stack->length - 1)) grow_stack(stack);

	(stack->data)[stack->sp] = value;
	stack->sp++;

	return value;
}

i64 pop(stack_t *stack) {
	stack->sp--;

	return stack->data[stack->sp];
}

void grow_stack(stack_t *stack) {
	if (stack->data != NULL) free(stack->data);

	stack->data = allocate_stack_data(stack->length + 50);

	stack->length += 50;
}

i64* allocate_stack_data(size_t len) {
	i64 *ret = calloc(len, sizeof(i64));
	if (ret == NULL) {
		perror("Error allocating stack memory");
		exit(1);
	}

	return ret;
}

void init_stack(stack_t* stack) {
	stack->length = 50;
	stack->sp = 0;
	stack->data = allocate_stack_data(stack->length);
}

#ifdef TEST
void print_head(stack_t const *stack) {
	printf("%" PRId64 "\n", stack->data[stack->sp - 1]);
}

void preety_print(stack_t const *stack) {
	for (i32 i=0; i<stack->sp; i++) {
		printf("[%" PRId32 "] %" PRId64 "\n", i, stack->data[i]);
	}
}
#endif
