#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/types.h"
#include "../include/esil.h"
#include "../include/stack.h"

#define LINE_SIZE 256

void exec_input_str(char* const line, i32 len, esil_vm_t *esil_vm) {
  i32 n_tokens = 0;
  char** tokens = tokens_from_string(line, len, &n_tokens);

  for (i32 i=0; i<n_tokens; i++) {

    register_t reg = EAX;
    reg = get_register(tokens[i]);
    esil_op operator = get_operator(tokens[i]);

    if (operator != INVALID) {
      exec_operation(&(esil_vm->data_stack), operator);
    } else if (reg != INVALID_REG) {
      // TODO
      printf("yay registers! #%d \n", reg);
    } else {
      long operand = strtol(tokens[i], NULL, 0);
      push(&(esil_vm->data_stack), operand);
    }
  }
  free_tokens(tokens);
}

int main() {
  esil_vm_t esil_vm;
  init_stack(&esil_vm.data_stack);
  init_vm_regs(&esil_vm);

  char line[LINE_SIZE] = {0};
  printf("> ");
  while(fgets(line, LINE_SIZE, stdin) != NULL) {
    size_t len = strnlen(line, LINE_SIZE);
    // Avoid newline character
    line[--len] = 0;

    exec_input_str(line, len, &esil_vm);
    
    i32 result = head(&esil_vm.data_stack);
    printf("%" PRId32 "\n", result);
    printf("> ");
  }
  free(esil_vm.data_stack.data);
}
