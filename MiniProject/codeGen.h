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

// Restore value from memory into register
extern void registerRestore(int reg);

#endif // __CODEGEN__
