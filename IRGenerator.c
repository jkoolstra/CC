#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "AST.h"
#include "IRGenerator.h"

int idx;
void generate(FILE*, ASTNode*);

void generateProgram(FILE* file, void *data){
	idx = 0;
	ProgramNode *program = (ProgramNode *)data;
	for(int i = 0; i < program->declarations.n; i++){
		generate(file, program->declarations.nodes[i]);
	}
	generate(file, program->compound);
}

void generateIValue(FILE* file, void *data){
	IValueNode *var = (IValueNode *)data;
	printf("int t%d = %d\n", idx, var->value);
	idx++;
}

void generateAssignment(FILE* file, void *data){
	AssignmentNode *assignment = (AssignmentNode *)data;
	generate(file, assignment->right);
	if(assignment->left->type == NODE_VARIABLE){
		VariableNode *var = (VariableNode *)assignment->left;
		printf("var%d = t%d\n", var->name, idx-1);
	}
	if(assignment->left->type == NODE_ARRAY_VARIABLE){
		ArrayVariableNode *var = (ArrayVariableNode *)assignment->left->data;
		for(int i =0; i < var->indices.n; i++){
			int idxRight = idx-1;
			generate(file, var->indices.nodes[i]);
			printf("var%d[t%d] = t%d\n", var->name, idx-1, idxRight);
		}
	}
}

void generateCompoundStatement(FILE* file, void *data){
	CompoundStatementNode *compound = (CompoundStatementNode *)data;
	for(int i = 0; i < compound->statements.n; i++){
		generate(file, compound->statements.nodes[i]);
	}
}

void generate(FILE* file, ASTNode *node){
	switch(node->type){
		case NODE_IVALUE: generateIValue(file, node->data); break;//TODO
		case NODE_RVALUE: break;//TODO
		case NODE_VARIABLE: break;//TODO
		case NODE_ARRAY_VARIABLE : break;//TODO
		case NODE_ARRAY: break;//TODO
		case NODE_EXPRESSION: break;//TODO
		case NODE_FUNCTION_CALL: break;//TODO
		case NODE_ASSIGNMENT: generateAssignment(file, node->data); break;
		case NODE_COMPOUND_STATEMENT: generateCompoundStatement(file, node->data); break;//TODO
		case NODE_PROCEDURE_CALL: break;//TODO
		case NODE_IF_ELSE: break;//TODO
		case NODE_WHILE: break;//TODO
		case NODE_PROGRAM: break;//TODO
		case NODE_FUNCTION: break;//TODO
		case NODE_PROCEDURE: break;//TODO
		case NODE_DECLARATION: break; printf("DECLARATION\n");//TODO
	}
}

void generateIR(FILE *file, ASTNode *programNode){
	printf("STARTING GENERATION\n");
	if(programNode->type != NODE_PROGRAM){
		exit(EXIT_FAILURE); // TODO : move error handling to seperate module
	} else {
		generateProgram(file, programNode->data);
	}
}
