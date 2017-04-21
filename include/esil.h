#ifndef ESIL_H
#define ESIL_H

#include <stdbool.h>
#include "stack.h"

#define ESIL_DELIMITER ','
#define NUM_ESIL_OPCODES 4
#define MAX_ESIL_OP_LEN 1

typedef enum {
  INVALID = -1,
  ESIL_ADD,
  ESIL_SUB,
  ESIL_MUL,
  ESIL_DIV
} esil_op;

char** tokens_from_string(char*, i32, i32*);
void free_tokens(char**);
esil_op get_operator(char* const);
i32 exec_operation(stack_t*, esil_op);

#endif
