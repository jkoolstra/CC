#ifndef AST_H
#define AST_H

#include "StringTable.h"
#include "common.h"
#include "tokens.h"
#include "IdEntry.h"

typedef enum nodeType {
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
	NODE_PROGRAM
} NodeType;

typedef struct astNode {
  NodeType type;
  void *data;
} ASTNode;

typedef struct nodeList {
	unsigned n;
	ASTNode **nodes;
} NodeList;

typedef struct iValueNode {
	int value;
} IValueNode;

typedef struct rValueNode {
	int value;
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
	Token operation;
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

typedef struct programNode {
	unsigned name;
	ASTNode *compound;
} ProgramNode;

// Node creation
ASTNode *createEmptyNode(NodeType);

ASTNode *createIValueNode(int);
ASTNode *createRValueNode(float);
ASTNode *createVariableNode(unsigned,Type);
ASTNode *createArrayVariableNode(unsigned, Type, NodeList);
ASTNode *createArrayNode(unsigned, Type, ASTNode*);
ASTNode *createExpressionNode(ASTNode*, ASTNode*, Token);
ASTNode *createFunctionCallNode(unsigned, Type, NodeList);
ASTNode *createProcedureCallNode(unsigned, NodeList);
ASTNode *createCompoundStatementNode(NodeList);
ASTNode *createAssignmentNode(ASTNode*, ASTNode*);
ASTNode *createIfElseNode(ASTNode*, ASTNode*, ASTNode*);
ASTNode *createWhileNode(ASTNode*, ASTNode*);
ASTNode *createProgramNode(unsigned, ASTNode*);


/*
ASTNode *createNode(Type t);
void freeNode(ASTNode*);
*/
// Nodelists
NodeList createEmptyNodeList();
NodeList createNodeList(ASTNode*);
void appendToNodeLists(NodeList*, ASTNode*);
NodeList combineNodeLists(NodeList, NodeList);


// Helper
Type determineType(ASTNode*);
void printListNode(NodeList list);

#endif
