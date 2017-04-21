#include "../include/esil.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char* esil_op_str[] = {
  "+",
  "-",
  "*",
  "/"
};

char** tokens_from_string(char* string, i32 length, i32 *tokens_length) {
  i32 count = 1;
  for(i32 i=0; i<length; i++) {
    if (string[i] == ESIL_DELIMITER) count++;
  }

  char** tokens = calloc(count, sizeof(char*));

  i32 tokens_counter = 0;
  i32 from = 0;
  for (i32 i=0; i<length && string[i] != 0; i++) {
    if (string[i] == ESIL_DELIMITER) {
      string[i] = 0;
      if (i != 0) {
        if (string[i-1] != 0) {
          tokens[tokens_counter] = (string + from);
          tokens_counter++;
        }
      }
      from = i + 1;
    }
  }

  if (string[length - 1] != 0) {
    tokens[tokens_counter] = (string + from);
    tokens_counter++;
  }

  
  *tokens_length = tokens_counter;
  return tokens;
}

void free_tokens(char** tokens) {
  free(tokens);
}

esil_op get_operator(char* const str) {
  for (i32 i=0; i<NUM_ESIL_OPCODES; i++) {
    if (strncmp(esil_op_str[i], str, MAX_ESIL_OP_LEN) == 0) {
      return i;
    }
  }
  return INVALID;
}

i32 exec_operation(stack_t *stack, esil_op operator) {
  switch (operator) {
  case INVALID: break;
  case ESIL_ADD:
    {
    i32 op1 = pop(stack);
    i32 op2 = pop(stack);
    push(stack, op1 + op2);
    break;
    }
  case ESIL_SUB:
    {
    i32 op1 = pop(stack);
    i32 op2 = pop(stack);
    push(stack, op1 - op2);
    break;
    }
  case ESIL_MUL:
    {
      i32 op1 = pop(stack);
      i32 op2 = pop(stack);
      push(stack, op1 * op2);
      break;
    }
  case ESIL_DIV:
    {
      i32 op1 = pop(stack);
      i32 op2 = pop(stack);
      push(stack, op1 * op2);
      break;
    }
  }

  return head(stack);
}
