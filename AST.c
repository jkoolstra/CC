#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "AST.h"
#include "IRGenerator.h"

ASTNode *createEmptyNode(NodeType type){
	ASTNode *node = safeMalloc(sizeof(IValueNode));
	node->type = type;

	return node;
}

ASTNode *createProgramNode(unsigned name, NodeList declarations, ASTNode *compound){
	ProgramNode *data = safeMalloc(sizeof(ProgramNode));
	data->name = name;
	data->declarations = declarations;
	data->compound = compound;

	ASTNode *node = createEmptyNode(NODE_PROGRAM);
	node->data = data;

	return node;
}

ASTNode *createDeclarationNode(unsigned name, Type type){
	DeclarationNode *data = safeMalloc(sizeof(DeclarationNode));
	data->name = name;
	data->type = type;

	ASTNode *node = createEmptyNode(NODE_DECLARATION);
	node->data = data;

	return node;
}

ASTNode *createIValueNode(int value){
	IValueNode *data = safeMalloc(sizeof(IValueNode));
	data->value = value;

	ASTNode *node = createEmptyNode(NODE_IVALUE);
	node->data = data;

	return node;
}

ASTNode *createRValueNode(float value){
	RValueNode *data = safeMalloc(sizeof(RValueNode));
	data->value = value;

	ASTNode *node = createEmptyNode(NODE_RVALUE);
	node->data = data;

	return node;
}

ASTNode *createVariableNode(unsigned name, Type type){
	VariableNode *data = safeMalloc(sizeof(VariableNode));
	data->name = name;
	data->type = type;

	ASTNode *node = createEmptyNode(NODE_VARIABLE);
	node->data = data;

	return node;
}

ASTNode *createArrayVariableNode(unsigned name, Type type, NodeList indices){
	ArrayVariableNode *data = safeMalloc(sizeof(ArrayVariableNode));
	data->name = name;
	data->type = type;
	data->indices = indices;

	ASTNode *node = createEmptyNode(NODE_ARRAY_VARIABLE);
	node->data = data;

	return node;
}

ASTNode *createArrayNode(unsigned name, Type type, ASTNode *index){
	ArrayNode *data = safeMalloc(sizeof(ArrayNode));
	data->name = name;
	data->type = type;
	data->type.secondary = TYPE_SCALAR;
	data->index = index;

	ASTNode *node = createEmptyNode(NODE_ARRAY);
	node->data = data;

	return node;
}

ASTNode *createExpressionNode(ASTNode *left, ASTNode *right, Operator operation){
	ExpressionNode *data = safeMalloc(sizeof(ExpressionNode));
	data->left = left;
	data->right = right;
	data->operation = operation;

	ASTNode *node = createEmptyNode(NODE_EXPRESSION);
	node->data = data;

	return node;
}

ASTNode *createFunctionCallNode(unsigned name, Type returnType, NodeList arguments){
	FunctionCallNode *data = safeMalloc(sizeof(FunctionCallNode));
	data->name = name;
	data->returnType = returnType;
	data->arguments = arguments;

	ASTNode *node = createEmptyNode(NODE_FUNCTION_CALL);
	node->data = data;

	return node;
}

ASTNode *createProcedureCallNode(unsigned name, NodeList arguments){
	ProcedureCallNode *data = safeMalloc(sizeof(ProcedureCallNode));
	data->name = name;
	data->arguments = arguments;

	ASTNode *node = createEmptyNode(NODE_PROCEDURE_CALL);
	node->data = data;

	return node;
}

ASTNode *createCompoundStatementNode(NodeList statements){
	CompoundStatementNode *data = safeMalloc(sizeof(CompoundStatementNode));
	data->statements = statements;

	ASTNode *node = createEmptyNode(NODE_COMPOUND_STATEMENT);
	node->data = data;

	return node;
}

ASTNode *createAssignmentNode(ASTNode *left, ASTNode *right){
	AssignmentNode *data = safeMalloc(sizeof(AssignmentNode));

	data->left = left;
	data->right = right;

	ASTNode *node = createEmptyNode(NODE_ASSIGNMENT);
	node->data = data;

	return node;
}

ASTNode *createIfElseNode(ASTNode *condition, ASTNode *then, ASTNode *els){
	IfElseNode *data = safeMalloc(sizeof(IfElseNode));
	data->condition = condition;
	data->then = then;
	data->els = els;

	ASTNode *node = createEmptyNode(NODE_IF_ELSE);
	node->data = data;

	return node;
}

ASTNode *createWhileNode(ASTNode *condition, ASTNode *compound){
	WhileNode *data = safeMalloc(sizeof(WhileNode));
	data->condition = condition;
	data->compound = compound;

	ASTNode *node = createEmptyNode(NODE_WHILE);
	node->data = data;

	return node;
}

ASTNode *createFunctionNode(unsigned name, Type type, ASTNode *compound){
	FunctionNode *data = safeMalloc(sizeof(FunctionNode));
	data->name = name;
	data->type = type;
	data->compound = compound;

	ASTNode *node = createEmptyNode(NODE_FUNCTION);
	node->data = data;

	return node;
}

ASTNode *createProceduremNode(unsigned name, ASTNode *compound){
	ProcedureNode *data = safeMalloc(sizeof(ProcedureNode));
	data->name = name;
	data->compound = compound;

	ASTNode *node = createEmptyNode(NODE_PROCEDURE);
	node->data = data;

	return node;
}

ASTNode *createReadLnNode(NodeList list){
	ReadLnNode *data = safeMalloc(sizeof(ReadLnNode));
	data->factors = list;

	ASTNode *node = createEmptyNode(NODE_READLN);
	node->data = data;

	return node;
}

ASTNode *createWriteLnNode(NodeList arguments){
	WriteLnNode *data = safeMalloc(sizeof(WriteLnNode));
	data->arguments = arguments;

	ASTNode *node = createEmptyNode(NODE_WRITELN);
	node->data = data;

	return node;
}

// Node list
NodeList createEmptyNodeList(){
    NodeList list;
	list.n = 0;

	return list;
}
NodeList createNodeList(ASTNode *node){
    NodeList list;
	list.n = 1;
	list.nodes = safeMalloc(sizeof(ASTNode *));
	list.nodes[0] = node;

	return list;
}

void appendToNodeLists(NodeList* list, ASTNode *node){
	printListNode(*list);
    list->n = list->n + 1;
    safeRealloc(list->nodes, list->n * sizeof(ASTNode *));
	list->nodes[list->n - 1] = node;
	printListNode(*list);
}

NodeList combineNodeLists(NodeList listOne, NodeList listTwo){
	// TODO : Free lists
	NodeList combinedList;
	combinedList.n = listOne.n + listTwo.n;
	combinedList.nodes = safeMalloc(combinedList.n * sizeof(ASTNode));
	int i;
	int j;
	for(i =0 ; i < listOne.n; i++){
		combinedList.nodes[i] = listOne.nodes[i];
	}
	for(j =0 ; j < listTwo.n; j++){
		combinedList.nodes[j+i] = listTwo.nodes[j];
	}
	return combinedList;
}

// Helper
Type determineExpressionType(ASTNode *initial){
	// TODO THERE ARE SOME ISSUES WITH CONDITIONS
	ExpressionNode *node = (ExpressionNode *)initial->data;
	Type leftType = determineType(node->left);
	Type rightType = determineType(node->right);

	switch(node->operation){
  		case OP_RELOP_GR :
    	case OP_RELOP_GREQ :
    	case OP_RELOP_SM :
    	case OP_RELOP_SMEQ :
    	case OP_RELOP_NOEQ :
    	case OP_RELOP_EQ : return makeType(TYPE_BOOL, TYPE_SCALAR, 0, 0);
      	case OP_I_MULOP_M : return makeType(TYPE_INTEGER, TYPE_SCALAR ,0, 0);
  		case OP_R_MULOP_D :
      	case OP_R_MULOP_M : return makeType(TYPE_REAL, TYPE_SCALAR, 0, 0);
  		case OP_ADDOP_ADD :
      	case OP_ADDOP_MIN : {
			if(leftType.base == TYPE_REAL || rightType.base == TYPE_REAL) {
				return makeType(TYPE_REAL, TYPE_SCALAR, 0, 0);
			} else {
				return makeType(TYPE_INTEGER, TYPE_SCALAR, 0, 0);
			}
		}
      	default: return makeType(TYPE_REAL, TYPE_SCALAR, 0, 0); // SHOULD NEVER HAPPEN
    }
}

Type determineType(ASTNode *node){
	switch(node->type){
		case NODE_IVALUE: return makeType(TYPE_INTEGER, TYPE_SCALAR, 0, 0);
		case NODE_RVALUE: return makeType(TYPE_REAL, TYPE_SCALAR,0,0);
		case NODE_VARIABLE: return ((VariableNode *)node->data)->type;
		case NODE_ARRAY_VARIABLE : return ((ArrayVariableNode *)node->data)->type;
		case NODE_ARRAY: return ((ArrayNode *)node->data)->type;
		case NODE_EXPRESSION: return determineExpressionType(node);
		case NODE_FUNCTION_CALL: return ((FunctionCallNode *)node->data)->returnType;
		case NODE_ASSIGNMENT: return determineType(((AssignmentNode *)node->data)->left);  // SHOULD NEVER HAPPEN
		case NODE_COMPOUND_STATEMENT: exit(EXIT_FAILURE); return makeType(TYPE_REAL, TYPE_SCALAR,0,0);// SHOULD NEVER HAPPEN;
		case NODE_PROCEDURE_CALL: exit(EXIT_FAILURE); return makeType(TYPE_REAL, TYPE_SCALAR,0,0);// SHOULD NEVER HAPPEN;
		case NODE_IF_ELSE: exit(EXIT_FAILURE); return makeType(TYPE_REAL, TYPE_SCALAR,0,0);// SHOULD NEVER HAPPEN;
		case NODE_WHILE: exit(EXIT_FAILURE); return makeType(TYPE_REAL, TYPE_SCALAR,0,0);// SHOULD NEVER HAPPEN;
		case NODE_PROGRAM: exit(EXIT_FAILURE); return makeType(TYPE_REAL, TYPE_SCALAR,0,0);// SHOULD NEVER HAPPEN;
		case NODE_FUNCTION: exit(EXIT_FAILURE); return makeType(TYPE_REAL, TYPE_SCALAR,0,0);// SHOULD NEVER HAPPEN;
		case NODE_PROCEDURE: exit(EXIT_FAILURE); return makeType(TYPE_REAL, TYPE_SCALAR,0,0);// SHOULD NEVER HAPPEN;
		case NODE_DECLARATION: exit(EXIT_FAILURE); return makeType(TYPE_REAL, TYPE_SCALAR,0,0);// SHOULD NEVER HAPPEN;
		case NODE_READLN: exit(EXIT_FAILURE); return makeType(TYPE_REAL, TYPE_SCALAR,0,0);// SHOULD NEVER HAPPEN;
		case NODE_WRITELN: exit(EXIT_FAILURE); return makeType(TYPE_REAL, TYPE_SCALAR,0,0);// SHOULD NEVER HAPPEN;
	}
}

void freeNode(ASTNode *node){
	switch(node->type){
		case NODE_IVALUE: break;
		case NODE_RVALUE: break;
		case NODE_VARIABLE: break;
		case NODE_ARRAY_VARIABLE: break; // TODO: free indices
		case NODE_ARRAY: break;	// TODO : free index
		case NODE_EXPRESSION: {
			freeNode(((ExpressionNode *)node->data)->left);
			freeNode(((ExpressionNode *)node->data)->right);
			break;
		}
		case NODE_FUNCTION_CALL: {
			// TODO
			break;
		}
		case NODE_PROCEDURE_CALL: {
			// TODO
			break;
		}
		case NODE_COMPOUND_STATEMENT: {
			//TODO
			break;
		}
		case NODE_ASSIGNMENT : {
			//TODO
			break;
		}
		case NODE_IF_ELSE : {
			//TODO
			break;
		}
		case NODE_WHILE : {
			//TODO
			break;
		}
		case NODE_FUNCTION : {
			//TODO
			break;
		}
		case NODE_PROCEDURE : {
			//TODO
			break;
		}
		case NODE_PROGRAM : {
			//TODO
			break;
		}
		case NODE_DECLARATION : {
			//TODO
			break;
		}
		case NODE_READLN : {
			//TODO
			break;
		}
		case NODE_WRITELN : {
			//TODO
			break;
		}
	}
	free(node->data);
	free(node);
}

void printListNode(NodeList list){
	printf("[%d] - ", list.n);
	for(int i = 0; i < list.n ; i++){
		ASTNode *node = list.nodes[i];
		printf("%d, ", node->type);
	}
	printf("\n");
}
