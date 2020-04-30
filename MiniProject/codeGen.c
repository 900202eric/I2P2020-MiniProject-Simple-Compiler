#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codeGen.h"

int r = 0;
int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0, address = -1;;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme);
                for (int i = 0; i < sbcount; i++)
                    if (strcmp(root->lexeme, table[i].name) == 0)
                        address = i * 4;
                root->reg = r++;
                printf("MOV r%d [%d]\n", root->reg, address);
                break;
            case INT:
                retval = atoi(root->lexeme);
                root->reg = r++;
                printf("MOV r%d %d\n", root->reg, retval);
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                address = -1;
                for (int i = 0; i < sbcount; i++)
                    if (strcmp(root->left->lexeme, table[i].name) == 0)
                        address = i * 4;
                printf("MOV [%d] r%d\n", address, root->right->reg);
                root->reg = root->right->reg;
                break;
            case ADDSUB:
            case MULDIV:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                    printf("ADD r%d r%d\n", root->left->reg, root->right->reg);
                    root->reg = root->left->reg;
                    r--;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                    printf("SUB r%d r%d\n", root->left->reg, root->right->reg);
                    root->reg = root->left->reg;
                    r--;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                    printf("MUL r%d r%d\n", root->left->reg, root->right->reg);
                    root->reg = root->left->reg;
                    r--;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0)
                        error(DIVZERO);
                    retval = lv / rv;
                    printf("DIV r%d r%d\n", root->left->reg, root->right->reg);
                    root->reg = root->left->reg;
                    r--;
                }
                break;
            case LOGICAL:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "&") == 0) {
                    retval = lv & rv;
                    printf("AND r%d r%d\n", root->left->reg, root->right->reg);
                    root->reg = root->left->reg;
                    r--;
                } else if (strcmp(root->lexeme, "|") == 0) {
                    retval = lv | rv;
                    printf("OR r%d r%d\n", root->left->reg, root->right->reg);
                    root->reg = root->left->reg;
                    r--;
                } else if (strcmp(root->lexeme, "^") == 0) {
                    retval = lv ^ rv;
                    printf("XOR r%d r%d\n", root->left->reg, root->right->reg);
                    root->reg = root->left->reg;
                    r--;
                }
                break;
            case INCDEC:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                retval = lv;
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
