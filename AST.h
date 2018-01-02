
#ifndef _AST_H
#define _AST_H
#include <stdio.h>
#include <stdarg.h>

#define NUM_OF_CHILDREN_UNKNOWN (-1)

typedef unsigned char byte;
typedef int Token;
typedef int Syntax;

typedef enum BasicType {
    TYPE_REAL, TYPE_INT
} BasicType;

typedef enum IdentifierType {
    FUNCTION_IDENTIFIER, ARRAY_IDENTIFIER,
    SCALAR_IDENTIFIER
} IdentifierType;

typedef struct SemanticValue_Identifier {
    int strTabIndex;
    IdentifierType type;
    BasicType subType; // Optional; for type ARRAY_IDENTIFIER
    struct {
        int no;
        BasicType *type;
    } params; // Optional; for type FUNCTION_IDENTIFIER
    byte *value; // For interpreting the AST. Not currently used.
} SemanticValue_Identifier;

typedef enum Operator_Assign { OP_SET_EQUAL } Operator_Assign;
typedef enum Operator_Rel {
    OP_LE, OP_LEQ, OP_GE, OP_GEQ, OP_NEQ, OP_EQ
} Operator_Rel;
typedef enum Operator_Add {
    OP_PLUS, OP_MIN //, OP_UNARY_MIN
} Operator_Add;
typedef enum Operator_Mul {
    OP_MUL, OP_DIV, OP_DIV_INT, OP_MOD
} Operator_Mul;
typedef union Operator {
    Operator_Assign assign;
    Operator_Rel rel;
    Operator_Add add;
    Operator_Mul mul;
} Operator;

typedef union SemanticValue {
    float realVal; 
    int intVal;
    int strTabIndex;
    Operator op;
} SemanticValue;

typedef enum ASTNodeType {
    TOKEN_NODE, SYNTAX_NODE
} ASTNodeType;

typedef union ASTNodeValue {
    Token token;
    Syntax syntax;
} ASTNodeValue;

typedef struct ASTNode {
    ASTNodeType type;
    ASTNodeValue value;
    SemanticValue sem;
    struct ASTNode **child;
    int nChildren;
} ASTNode;
typedef ASTNode* AST;
typedef AST* ASTPtr;

ASTNode* buildASTNode(ASTNodeType, ASTNodeValue, SemanticValue, int, ...);
void freeAST(AST);
#endif // #ifndef _AST_H

























