#include "../include/esil.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char* esil_op_str[] = {
  "+",
  "-",
  "*",
  "/",
  "<<",
  ">>",
  "<<<",
  "<<<",
  "&",
  "|",
  "="
};

const char* esil_regs_str[] = {
  "eax",
  "ebx",
  "ecx",
  "edx",
  "esi",
  "edi",
  "eip",
  "esp",
  "ebp"
};

void init_vm_regs(esil_vm_t *vm) {
  for (i32 i=0; i<NUM_ESIL_VM_REGS; i++) {
    vm->regs[i] = 0;
  }
}

void split_tokens(char* string, i32 max_len) {
  for(i32 i=0; i < max_len; i++) {
    if (string[i] == ESIL_DELIMITER) string[i] = '\0';
  }
}

esil_op get_operator(char* const str) {
  for (i32 i=0; i<NUM_ESIL_OPCODES; i++) {
    if (strncmp(esil_op_str[i], str, MAX_ESIL_OP_LEN) == 0) {
      return i;
    }
  }
  return INVALID;
}

register_t get_register(char* const str) {
  for (i32 i=0; i<NUM_ESIL_VM_REGS; i++) {
    if(strncmp(esil_regs_str[i], str, MAX_ESIL_REG_LEN) == 0) {
      return i;
    }
  }
  return INVALID_REG;
}

void preety_print_regs(const esil_vm_t esil_vm) {
  for (i32 i; i < NUM_ESIL_VM_REGS; i++) {
    printf("%s: 0x%x\n", esil_regs_str[i], esil_vm.regs[i]);
  }
}

i32 exec_operation(esil_vm_t *esil_vm, esil_op operator) {
  stack_t *stack = &(esil_vm->data_stack);
  stack_t *type_stack = &(esil_vm->type_stack);
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
  case ESIL_SHL:
    {
      i32 op1 = pop(stack);
      i32 op2 = pop(stack);
      push(stack, op1 << op2);
      break;

    }
  case ESIL_SHR:
    {
      i32 op1 = pop(stack);
      i32 op2 = pop(stack);
      push(stack, op1 >> op2);
      break;

    }
  case ESIL_ROTL:
    //TODO
    break;
  case ESIL_ROTR:
    // TODO
    break;
  case ESIL_AND:
    {
      i32 op1 = pop(stack);
      i32 op2 = pop(stack);
      push(stack, op1 & op2);
      break;
    }
  case ESIL_OR:
    {
      i32 op1 = pop(stack);
      i32 op2 = pop(stack);
      push(stack, op1 | op2);
      break;
    }
  case ESIL_REG_ASSIGN:
    {
      esil_type_t type_dest = pop(type_stack);
      if (type_dest != REGISTER) {
        printf("Not a register!\n");
        push(type_stack, type_dest);
        break;
      }

      register_t dest = pop(stack);

      esil_type_t type_src = pop(type_stack);
      i32 src = pop(stack);
      if (type_src == REGISTER) {
        esil_vm->regs[dest] = esil_vm->regs[src];
      } else if (type_src == IMMEDIATE) {
        esil_vm->regs[dest] = src;
      }

      break;
    }
  }

  return head(stack);
}
