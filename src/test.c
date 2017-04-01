#include "../include/types.h"
#include "../include/stack.h"
#include "../include/esil.h"

#include <stdio.h>

int main() {
#ifdef TEST
	#include <string.h>
	// Stack tests
	stack_t stack;
	init_stack(&stack);
	push(&stack, 5);
	push(&stack, 6);
	push(&stack, 7);
	push(&stack, 8);
	push(&stack, 9);
	push(&stack, 10);
	print_head(&stack);
	preety_print(&stack);
	free(stack.data);

	// ESIL tests
	i64 t_len;
	char str[10];
	strncpy(str, "1,2,+,3,2,[],GOTO", 18);
	puts(str);
	char** tokens = tokens_from_string(str, 17, &t_len);
	printf("LEN: %" PRId64 "\n", t_len);
	for(i64 i=0; i<t_len; i++) {
		printf("TOKEN %" PRId64 ": %s\n", i, tokens[i]);
	}

	free_tokens(tokens);
#endif
	return 0;
}
