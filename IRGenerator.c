#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "AST.h"
#include "IRGenerator.h"

#define PRINT 1

int idx;
void generate(FILE*, ASTNode*);
char *operatorString(Operator op);

void generateProgram(FILE* file, ASTNode *node){
	fprintf(file,"#include <stdio.h>\n");
	fprintf(file,"#include <stdlib.h>\n");
	fprintf(file,"int main(int argc, char **argv){\n");
	idx = 0;
	ProgramNode *program = (ProgramNode *)node->data;
	for(int i = 0; i < program->declarations.n; i++){
		generate(file, program->declarations.nodes[i]);
	}
	generate(file, program->compound);
	fprintf(file,"return 1;\n}");
}

void generateDeclarations(FILE *file, ASTNode *given){
	DeclarationNode *declaration = (DeclarationNode *)given->data;
	if(declaration->type.base == TYPE_REAL){
		fprintf(file,"float ");
	} else {
		fprintf(file,"int ");
	}

	if(declaration->type.secondary == TYPE_SCALAR){
		fprintf(file,"var%d;\n",declaration->name);
	} else {
		int range = declaration->type.high - declaration->type.low;
		fprintf(file,"var%d[%d];\n",declaration->name, range);
	}
}

void generateWriteLn(FILE *file, ASTNode *given){
	WriteLnNode *node = (WriteLnNode *)given->data;
	for(int i = 0; i < node->arguments.n; i++){
		generate(file, node->arguments.nodes[i]);
		fprintf(file,"printf(\"");
		if(determineType(node->arguments.nodes[i]).base == TYPE_REAL){
			fprintf(file,"%%.2f\\n\", t%d);\n", idx - 1);
		} else {
			fprintf(file,"%%d\\n\", t%d);\n", idx - 1);
		}
	}
}

void generateReadLn(FILE *file, ASTNode *given){
	ReadLnNode *node = (ReadLnNode *)given->data;
	for(int i = 0; i < node->factors.n; i++){
		unsigned intialIdx = idx;
		if(determineType(node->factors.nodes[i]).base == TYPE_REAL){
			fprintf(file,"float t%d;\n", idx);
			fprintf(file,"scanf(\"%%f\", &t%d);\n", intialIdx);
		} else {
			fprintf(file,"int t%d;\n", idx);
			fprintf(file,"scanf(\"%%d\", &t%d);\n", intialIdx);
		}
		if(node->factors.nodes[i]->type == NODE_VARIABLE){
			VariableNode *var = (VariableNode *)node->factors.nodes[i]->data;
			fprintf(file,"var%d = t%d;\n", var->name, intialIdx);
		} else if(node->factors.nodes[i]->type == NODE_ARRAY_VARIABLE){
			ArrayVariableNode *var = (ArrayVariableNode *)node->factors.nodes[i]->data;
			for(int i =0; i < var->indices.n; i++){
				generate(file, var->indices.nodes[i]);
				fprintf(file,"var%d[t%d] = t%d;\n", var->name, idx-1, intialIdx);
			}
		}
		idx++;
	}
}

void generateVariable(FILE* file, ASTNode *given){
	VariableNode *var = (VariableNode *)given->data;
	if(determineType(given).base == TYPE_REAL){
		fprintf(file,"float t%d = var%d;\n", idx, var->name);
	} else {
		fprintf(file,"int t%d = var%d;\n", idx, var->name);
	}
	idx++;
}

void generateArray(FILE* file, ASTNode *given){
	ArrayNode *var = (ArrayNode *)given->data;
	generate(file, var->index);
	if(determineType(given).base == TYPE_REAL){
		fprintf(file,"float t%d = var%d[t%d];\n", idx, var->name, idx-1);
	} else {
		fprintf(file,"int t%d = var%d[t%d];\n", idx, var->name, idx-1);
	}
	idx++;
}

void generateExpression(FILE* file, ASTNode *given){
	ExpressionNode *var = (ExpressionNode *)given->data;
	generate(file, var->left);
	int leftIdx = idx-1;
	generate(file, var->right);
	int rightIdx = idx-1;
	if(determineType(given).base == TYPE_REAL){
		fprintf(file,"float t%d = t%d %s t%d;\n", idx, leftIdx, operatorString(var->operation), rightIdx);
	} else {
		fprintf(file,"int t%d = t%d %s t%d;\n", idx, leftIdx, operatorString(var->operation), rightIdx);
	}
	idx++;
}

void generateIValue(FILE* file, ASTNode *given){
	IValueNode *var = (IValueNode *)given->data;
	fprintf(file,"int t%d = %d;\n", idx, var->value);
	idx++;
}

void generateRValue(FILE* file, ASTNode *given){
	RValueNode *var = (RValueNode *)given->data;
	fprintf(file,"float t%d = %f;\n", idx, var->value);
	idx++;
}

void generateAssignment(FILE* file, ASTNode *given){
	AssignmentNode *assignment = (AssignmentNode *)given->data;
	generate(file, assignment->right);
	int idxRight = idx-1;
	if(assignment->left->type == NODE_VARIABLE){
		VariableNode *var = (VariableNode *)assignment->left->data;
		fprintf(file,"var%d = t%d;\n", var->name, idxRight);
	}
	if(assignment->left->type == NODE_ARRAY_VARIABLE){
		ArrayVariableNode *var = (ArrayVariableNode *)assignment->left->data;
		for(int i =0; i < var->indices.n; i++){
			generate(file, var->indices.nodes[i]);
			fprintf(file,"var%d[t%d] = t%d;\n", var->name, idx-1, idxRight);
		}
	}
}

void generateCompoundStatement(FILE* file, ASTNode *given){
	CompoundStatementNode *compound = (CompoundStatementNode *)given->data;
	for(int i = 0; i < compound->statements.n; i++){
		generate(file, compound->statements.nodes[i]);
	}
}

char *operatorString(Operator op){
	switch(op){
		case OP_RELOP_GR : return "<";
		case OP_RELOP_GREQ : return "<=";
		case OP_RELOP_SM : return ">";
		case OP_RELOP_SMEQ : return ">=";
		case OP_RELOP_NOEQ : return "!=";
		case OP_RELOP_EQ : return "==";
		case OP_ADDOP_MIN : return "-";
		case OP_ADDOP_ADD : return "+";
		case OP_I_MULOP_M : return "*";
		case OP_I_MULOP_D : return "/";
		case OP_R_MULOP_M : return "*";
		case OP_R_MULOP_D : return "/";
	}
}

void generate(FILE* file, ASTNode *node){
	switch(node->type){
		case NODE_IVALUE:if(PRINT){fprintf(file,"//NODE_IVALUE\n");} generateIValue(file, node); break;//TODO
		case NODE_RVALUE: if(PRINT){fprintf(file,"//NODE_RVALUE\n");} generateRValue(file, node); break;//TODO
		case NODE_VARIABLE: if(PRINT){fprintf(file,"//NODE_VARIABLE\n");} generateVariable(file, node); break;//TODO
		case NODE_ARRAY_VARIABLE : if(PRINT){fprintf(file,"//NODE_ARRAY_VARIABLE\n");} // This node can only appear on the right side of a assignment
		case NODE_ARRAY: if(PRINT){fprintf(file,"//NODE_ARRAY\n");} generateArray(file, node); break;//TODO
		case NODE_EXPRESSION: if(PRINT){fprintf(file,"//NODE_EXPRESSION\n");} generateExpression(file, node); break;//TODO
		case NODE_FUNCTION_CALL: if(PRINT){fprintf(file,"//NODE_FUNCTION_CALL\n");} break;//TODO
		case NODE_ASSIGNMENT: if(PRINT){fprintf(file,"//NODE_ASSIGNMENT\n");} generateAssignment(file, node); break;
		case NODE_COMPOUND_STATEMENT: if(PRINT){fprintf(file,"//NODE_COMPOUND_STATEMENT\n");} generateCompoundStatement(file, node); break;//TODO
		case NODE_PROCEDURE_CALL: if(PRINT){fprintf(file,"//NODE_PROCEDURE_CALL\n");} break;//TODO
		case NODE_IF_ELSE: if(PRINT){fprintf(file,"//NODE_IF_ELSE\n");} break;//TODO
		case NODE_WHILE: if(PRINT){fprintf(file,"//NODE_WHILE\n");} break;//TODO
		case NODE_PROGRAM: if(PRINT){fprintf(file,"//NODE_PROGRAM\n");} generateProgram(file, node); break;//TODO
		case NODE_FUNCTION: if(PRINT){fprintf(file,"//NODE_FUNCTION\n");} break;//TODO
		case NODE_PROCEDURE: if(PRINT){fprintf(file,"//NODE_PROCEDURE\n");} break;//TODO
		case NODE_DECLARATION: if(PRINT){fprintf(file,"//NODE_DECLARATION\n");} generateDeclarations(file, node); break; //TODO
		case NODE_READLN: if(PRINT){fprintf(file,"//NODE_READLN\n");} generateReadLn(file, node); break;
		case NODE_WRITELN: if(PRINT){fprintf(file,"//NODE_WRITELN\n");} generateWriteLn(file, node); break;
	}
}

void generateIR(FILE *file, ASTNode *programNode){
	if(programNode->type != NODE_PROGRAM){
		exit(EXIT_FAILURE); // TODO : move error handling to seperate module
	} else {
		generate(file, programNode);
	}
}
