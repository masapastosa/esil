#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/types.h"
#include "../include/esil.h"
#include "../include/stack.h"

#define LINE_SIZE 256

int main() {
  stack_t stack;
  init_stack(&stack);

  char line[LINE_SIZE] = {0};
  printf("> ");
  while(fgets(line, LINE_SIZE, stdin) != NULL) {
    size_t len = strlen(line);
    // Avoid newline character
    line[--len] = 0;

    i32 n_tokens = 0;
    char** tokens = tokens_from_string(line, len, &n_tokens);

    for (i32 i=0; i<n_tokens; i++) {
      esil_op operator = get_operator(tokens[i]);
      if (operator == INVALID) {
        long operand = strtol(tokens[i], NULL, 0);
        push(&stack, operand);
      } else {
        exec_operation(&stack, operator);
      }
    }
    i32 result = head(&stack);
    printf("%" PRId32 "\n", result);
    free_tokens(tokens);
    printf("> ");
  }
  free(stack.data);
}
