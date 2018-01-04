
#ifndef _AST_H
#define _AST_H
#include <stdio.h>
#include <stdarg.h>

#define NUM_OF_CHILDREN_UNKNOWN (-1)

typedef unsigned char byte;

/* Enums are nice for debuggers like gdb. */

// From parser.tab.h
// We need this because we cannot yet define YYSTYPE
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
 enum yytokentype {
    TOK_INVALID = 258,
    TOK_NEWLINE = 259,
    TOK_DO = 260,
    TOK_FUNCTION = 261,
    TOK_PROGRAM = 262,
    TOK_PROCEDURE = 263,
    TOK_VAR = 264,
    TOK_INTEGER = 265,
    TOK_REAL = 266,
    TOK_ARRAY = 267,
    TOK_OF = 268,
    TOK_IF = 269,
    TOK_THEN = 270,
    TOK_ELSE = 271,
    TOK_WHILE = 272,
    TOK_BEGIN = 273,
    TOK_END = 274,
    TOK_ID = 275,
    TOK_NUM = 276,
    TOK_ASSIGNOP = 277,
    TOK_RELOP = 278,
    TOK_ADDOP = 279,
    TOK_MULOP = 280
 };
#endif // #ifndef YYTOKENTYPE
typedef enum yytokentype Token;

typedef enum Syntax {
    SYNTAX_PROGRAM = 1000,
    SYNTAX_SUBPROGRAM,
    SYNTAX_SUBPROGRAM_LIST,
    SYNTAX_EXPRESSION_LIST,
    SYNTAX_STATEMENT_LIST,
    SYNTAX_PARAMETER_LIST,
    SYNTAX_ID_LIST,
    SYNTAX_DECL_LIST,
    SYNTAX_DECL_ARRAY_TYPE,
    SYNTAX_IF,
    SYNTAX_WHILE,
    SYNTAX_FUNCTION,
    SYNTAX_ARRAY_ELEMENT,
    SYNTAX_INLINE_ARRAY_ELEMENT,
    SYNTAX_FUNCTION_CALL,
    SYNTAX_INLINE_FUNCTION_CALL
} Syntax;

typedef enum BasicType {
    TYPE_REAL, TYPE_INT, TYPE_VOID
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
    //byte *value; // For interpreting the AST. Not currently used.
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

typedef enum ASTNodeType {
    TOKEN_NODE, SYNTAX_NODE
} ASTNodeType;

typedef union SemanticValue {
    // For ASTNodeType TOKEN_NODE
    float realVal; 
    int intVal;
    int strTabIndex;
    Operator op;
    // For ASTNodeType SYNTAX_NODE
    BasicType type;
} SemanticValue;
// To provide to buildASTNode() when no semantic value is required
#define NO_SEMANTIC_VALUE (no_semantic_value())
//#define NO_SEMANTIC_VALUE _NO_SEMANTIC_VALUE
//static SemanticValue _NO_SEMANTIC_VALUE = { .intVal = 0 };

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
SemanticValue no_semantic_value(void);
ASTNodeValue syntax(Syntax);
ASTNodeValue token(Token);
#endif // #ifndef _AST_H

























