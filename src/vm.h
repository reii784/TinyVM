#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stdbool.h>

#define REG_COUNT 8
#define RAM_SIZE 256

typedef struct {
  int32_t regs[REG_COUNT]; // general-purpose registers
  uint8_t ram[RAM_SIZE];   // VM memory

  int pc;                  // current program position
  bool running;
} VM;

// VM setup and execution
void vm_init(VM *vm);
void vm_run(VM *vm, const int *program, int size);

// RAM access
void vm_write(VM *vm, int addr, uint8_t value);
uint8_t vm_read(VM *vm, int addr);

#endif