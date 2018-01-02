
#define _AST_C
#include <stdio.h>
#include <stdlib.h>
#include "AST.h"
#include "common.h"

ASTNode* buildASTNode(ASTNodeType type, ASTNodeValue value,
  SemanticValue sem, int nChildren, ...) {
    ASTNode *node = safeMalloc(sizeof(ASTNode));
    node->type = type;
    node->value = value;
    node->sem = sem;
    node->nChildren = nChildren;
    if (nChildren != NUM_OF_CHILDREN_UNKNOWN) {
        int i;
        va_list vl;
        va_start(vl, nChildren);
        for (i=0; i < nChildren; ++i) {
            node->child[i] = va_arg(vl, ASTNode*);
        }
        va_end(vl);
    }
    return node;
}

void freeAST(AST ast) {
    int i;
    if (ast == NULL) {
        return;
    }
    for (i = 0; i < ast->nChildren; ++i) {
        freeAST(ast->child[i]);
    }
    free(ast);
}
