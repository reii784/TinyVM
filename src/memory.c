#include "vm.h"

void vm_write(VM *vm, int addr, uint8_t value) {
  if (addr >= 0 && addr < RAM_SIZE)
    vm->ram[addr] = value;
}

uint8_t vm_read(VM *vm, int addr) {
  if (addr >= 0 && addr < RAM_SIZE)
    return vm->ram[addr];

  return 0;
}