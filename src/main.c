#include "vm.h"
#include "opcodes.h"

int main(void) {
  VM vm;

  // test program
  int program[] = {
    OP_LOAD, 0, 10,
    OP_LOAD, 1, 20,

    OP_ADD, 2, 0, 1,
    OP_PRINT, 2,

    OP_MUL, 3, 2, 1,
    OP_PRINT, 3,

    OP_XOR, 4, 0, 1,
    OP_PRINT, 4,

    OP_CMP, 5, 0, 1,
    OP_PRINT, 5,

    OP_HALT
  };

  // total number of integers, including opcode arguments
  int size = sizeof(program) / sizeof(program[0]);

  vm_init(&vm);
  vm_run(&vm, program, size);

  return 0;
}