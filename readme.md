# TinyVM

A tiny virtual machine written in C.

Made this mostly because I wanted to mess around with C and understand how VM's work.

## Features

- 8 registers
- 256 bytes of RAM
- Basic math operations
- Bitwise operations
- Jumps
- Bytecode execution

## Build

You need GCC installed.

```bash
gcc -Wall -Wextra -O2 -Isrc src/main.c src/vm.c src/memory.c -o tinyvm
```

## Run

```bash
./tinyvm
```