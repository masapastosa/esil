#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/types.h"
#include "../include/esil.h"
#include "../include/stack.h"

#define LINE_SIZE 2048

size_t strnlen(char* str, size_t max_len) {
  size_t len;
  for(len=0; len < max_len && str[len]; len++);
  return len;
}

void exec_input_str(char* line, i32 len, esil_vm_t *esil_vm) {
  split_tokens(line, len);
  char* current_token = line;

  while (len > 0) {
    esil_op operator = get_operator(current_token);
    if (operator != INVALID) {
      // It's an operator (+, -, <<, >>...)
      exec_operation(esil_vm, operator);
    } else {
      register_t reg = get_register(current_token);
      if (reg != INVALID_REG) {
        // It's a register (eax, ebx, ecx...)
        push(&(esil_vm->regs_stack), reg);
      } else {
        // It's an operand
        long operand = strtol(current_token, NULL, 0);
        push(&(esil_vm->data_stack), operand);
      }
    }

    size_t n_bytes = strnlen(current_token, len) + 1;
    len -= n_bytes;
    current_token += n_bytes;
  }
}

int main() {
  esil_vm_t esil_vm;
  init_stack(&esil_vm.data_stack);
  init_stack(&esil_vm.regs_stack);
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
  free(esil_vm.regs_stack.data);
}
