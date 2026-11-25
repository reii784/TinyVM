#include <stdio.h>
#include "vm.h"
#include "opcodes.h"

// scary stuff

static int next(VM *vm, const int *program, int size) {
  // fetch next value and advance the program counter
  if (vm->pc < 0 || vm->pc >= size) {
    vm->running = false;
    return 0;
  }

  return program[vm->pc++];
}

void vm_init(VM *vm) {
  *vm = (VM){0};
  vm->running = true;

  printf("[VM[] booted successfully\n");
}

void vm_run(VM *vm, const int *program, int size) {
  while (vm->running) {
    int op = next(vm, program, size);

    if (!vm->running)
      break;

    switch (op) {
      case OP_HALT:
        printf("[VM] shutting down\n");
        vm->running = false;
        break;

      case OP_LOAD: {
        int dst = next(vm, program, size);
        int val = next(vm, program, size);

        if (!vm->running || dst < 0 || dst >= REG_COUNT)
          goto error;

        vm->regs[dst] = val;
        break;
      }

      // it works ツ
      case OP_ADD:
      case OP_SUB:
      case OP_MUL:
      case OP_XOR:
      case OP_CMP: {
        int dst = next(vm, program, size);
        int a = next(vm, program, size);
        int b = next(vm, program, size);

        if (!vm->running ||
            dst < 0 || dst >= REG_COUNT ||
            a < 0 || a >= REG_COUNT ||
            b < 0 || b >= REG_COUNT)
          goto error;

        // all these operations use the same register layout
        switch (op) {
          case OP_ADD:
            vm->regs[dst] = vm->regs[a] + vm->regs[b];
            break;

          case OP_SUB:
            vm->regs[dst] = vm->regs[a] - vm->regs[b];
            break;

          case OP_MUL:
            vm->regs[dst] = vm->regs[a] * vm->regs[b];
            break;

          case OP_XOR:
            vm->regs[dst] = vm->regs[a] ^ vm->regs[b];
            break;

          case OP_CMP:
            vm->regs[dst] = vm->regs[a] == vm->regs[b];
            break;
        }

        break;
      }

      case OP_JMP: {
        int addr = next(vm, program, size);

        if (!vm->running || addr < 0 || addr >= size)
          goto error;

        vm->pc = addr;
        break;
      }

      case OP_JNZ: {
        int reg = next(vm, program, size);
        int addr = next(vm, program, size);

        if (!vm->running ||
            reg < 0 || reg >= REG_COUNT ||
            addr < 0 || addr >= size)
          goto error;

        // jump only if the register contains a nonzero value
        if (vm->regs[reg] != 0)
          vm->pc = addr;

        break;
      }

      case OP_PRINT: {
        int reg = next(vm, program, size);

        if (!vm->running || reg < 0 || reg >= REG_COUNT)
          goto error;

        printf("[VM] R%d = %d\n", reg, vm->regs[reg]);
        break;
      }

      default:
        goto error;
    }
  }

  return;

error:
  printf("[VM] something definently went wrong\n");
  vm->running = false;
}