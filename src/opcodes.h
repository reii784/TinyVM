#ifndef OPCODES_H
#define OPCODES_H

// VM instructions
enum {
  OP_HALT,
  OP_LOAD,

  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_XOR,
  OP_CMP,

  OP_JMP,
  OP_JNZ,
  
  OP_PRINT
};

#endif