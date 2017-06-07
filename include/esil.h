#ifndef ESIL_H
#define ESIL_H

#include <stdbool.h>
#include "stack.h"

#define ESIL_DELIMITER ','

#define NUM_ESIL_OPCODES 11
#define MAX_ESIL_OP_LEN 2

typedef enum {
  INVALID = -1,
  ESIL_ADD,
  ESIL_SUB,
  ESIL_MUL,
  ESIL_DIV,
  ESIL_SHL,
  ESIL_SHR,
  ESIL_ROTL,
  ESIL_ROTR,
  ESIL_AND,
  ESIL_OR,
  ESIL_REG_ASSIGN
} esil_op;

#define NUM_ESIL_VM_REGS 9
#define MAX_ESIL_REG_LEN 3

// Just support 32 bits registers for now (as we use 32 bits integers in the stack)
typedef enum {
  INVALID_REG = -2,
  EAX = 0,
  EBX,
  EXC,
  EDX,
  ESI,
  EDI,
  EIP,
  ESP,
  EBP
} register_t;

typedef struct {
  stack_t data_stack;
  stack_t regs_stack;
  i32 regs[NUM_ESIL_VM_REGS];
} esil_vm_t;

void init_vm_regs(esil_vm_t*);
void split_tokens(char*, i32);
void preety_print_regs(const esil_vm_t);
esil_op get_operator(char* const);
register_t get_register(char* const);
i32 exec_operation(esil_vm_t*, esil_op);

#endif
