#ifndef AST_H
#define AST_H

#include "StringTable.h"
#include "common.h"
#include "IdEntry.h"

typedef enum nodeType {
	NODE_PROGRAM,
	NODE_DECLARATION,
	NODE_IVALUE,
	NODE_RVALUE,
	NODE_VARIABLE,
	NODE_ARRAY_VARIABLE,
	NODE_ARRAY,
	NODE_EXPRESSION,
	NODE_FUNCTION_CALL,
	NODE_PROCEDURE_CALL,
	NODE_COMPOUND_STATEMENT,
	NODE_ASSIGNMENT,
	NODE_IF_ELSE,
	NODE_WHILE,
	NODE_FUNCTION,
	NODE_PROCEDURE,
	NODE_READLN,
	NODE_WRITELN
} NodeType;

typedef enum operator {
	OP_RELOP_GR = 275,
	OP_RELOP_GREQ = 276,
	OP_RELOP_SM = 277,
	OP_RELOP_SMEQ = 278,
	OP_RELOP_NOEQ = 279,
	OP_RELOP_EQ = 280,
	OP_ADDOP_MIN = 281,
	OP_ADDOP_ADD = 282,
	OP_I_MULOP_M = 283,
	OP_I_MULOP_D = 284,
	OP_R_MULOP_M = 285,
	OP_R_MULOP_D = 286,
} Operator;

typedef struct astNode {
  NodeType type;
  void *data;
} ASTNode;

typedef struct nodeList {
	unsigned n;
	ASTNode **nodes;
} NodeList;

typedef struct programNode {
	unsigned name;
	NodeList declarations;
	ASTNode *compound;
} ProgramNode;

typedef struct declarationNode {
	unsigned name;
	Type type;
} DeclarationNode;

typedef struct iValueNode {
	int value;
} IValueNode;

typedef struct rValueNode {
	float value;
} RValueNode;

typedef struct variableNode {
	unsigned name;
	Type type;
} VariableNode;

typedef struct arrayVariableNode {
	unsigned name;
	Type type;
	NodeList indices;
} ArrayVariableNode;

typedef struct arrayNode {
	unsigned name;
	ASTNode *index;
	Type type;
} ArrayNode;

typedef struct expressionNode {
	ASTNode *left;
	ASTNode *right;
	Operator operation;
} ExpressionNode;

typedef struct functionCallNode{
	unsigned name;
	Type returnType;
	NodeList arguments;
} FunctionCallNode;

typedef struct procedureCallNode{
	unsigned name;
	NodeList arguments;
} ProcedureCallNode;

typedef struct compoundStatementNode{
	NodeList statements;
} CompoundStatementNode;

typedef struct assignmentNode {
	ASTNode *left;
	ASTNode *right;
} AssignmentNode;

typedef struct ifElseNode{
	ASTNode *condition;
	ASTNode *then;
	ASTNode *els;
} IfElseNode;

typedef struct whileNode{
	ASTNode *condition;
	ASTNode *compound;
} WhileNode;

typedef struct functionNode {
	unsigned name;
	Type type;
	ASTNode *compound;
} FunctionNode;

typedef struct procedureNode {
	unsigned name;
	ASTNode *compound;
} ProcedureNode;

typedef struct readLnNode {
	NodeList factors;
} ReadLnNode;

typedef struct writeLnNode {
	NodeList arguments;
} WriteLnNode;

// Node creation
ASTNode *createEmptyNode(NodeType);

ASTNode *createProgramNode(unsigned, NodeList, ASTNode*);
ASTNode *createDeclarationNode(unsigned, Type);
ASTNode *createIValueNode(int);
ASTNode *createRValueNode(float);
ASTNode *createVariableNode(unsigned,Type);
ASTNode *createArrayVariableNode(unsigned, Type, NodeList);
ASTNode *createArrayNode(unsigned, Type, ASTNode*);
ASTNode *createExpressionNode(ASTNode*, ASTNode*, Operator);
ASTNode *createFunctionCallNode(unsigned, Type, NodeList);
ASTNode *createProcedureCallNode(unsigned, NodeList);
ASTNode *createCompoundStatementNode(NodeList);
ASTNode *createAssignmentNode(ASTNode*, ASTNode*);
ASTNode *createIfElseNode(ASTNode*, ASTNode*, ASTNode*);
ASTNode *createWhileNode(ASTNode*, ASTNode*);
ASTNode *createFunctionNode(unsigned,Type, ASTNode*);
ASTNode *createProcedureNode(unsigned, ASTNode*);
ASTNode *createReadLnNode(NodeList);
ASTNode *createWriteLnNode(NodeList);


void freeNode(ASTNode*);
void freeNodeList(NodeList);

// Nodelists
NodeList createEmptyNodeList();
NodeList createNodeList(ASTNode*);
void appendToNodeLists(NodeList*, ASTNode*);
NodeList combineNodeLists(NodeList, NodeList);


// Helper
Type determineType(ASTNode*);
void printListNode(NodeList list);

#endif
