#ifndef __CODEGEN__
#define __CODEGEN__

#include "parser.h"

// the register number
extern int r;

// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);

// Check register is full and move value into memory
extern void registerStore(void);

// Restore value of register 7 from memory into register (Part 1)
extern void registerRestoreNum7(int reg);

// Restore value from memory into register (Part 2)
extern void registerRestore(int reg);

#endif // __CODEGEN__
