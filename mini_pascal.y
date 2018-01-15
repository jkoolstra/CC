
%{
	//#include "tokens.h"
	#include "IRGenerator.h"
    #include "IdEntry.h"
	#include "AST.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include "lex.yy.c"
    #include "StringTable.h"
    #include "SymbolStack.h"
    #include "common.h"

    // CHECKING
	void checkCondition(ASTNode*);
	void checkAssignment(ASTNode*, ASTNode*);
    void checkIfIdentifierIsDeclared(unsigned);
    void checkIdentifierIdType(unsigned, IdType);
    void checkIdentifierSecondaryType(unsigned, SecondaryType);
	void checkIfArrayIndexIsInteger(ASTNode*);
	void checkIfMultipleArrayIndicesAreAllIntegers(NodeList);			//TODO: ADD this functionality back
	void checkParameterCountAndTypes(unsigned id, NodeList list, IdType type);
    void checkTypes(ASTNode*, ASTNode*, Operator);

	// DECLARING
    void declareFunctionLocallyAsVariable(StrtabIndexList, Type type);
    void declareParametersLocallyAsVariables(ParameterList);
    void declareVariable(StrtabIndexList, Type);
    void declareFunction(StrtabIndexList, Type, ParameterList);
    void declareProcedure(StrtabIndexList, ParameterList);

	// ERROR HANDLING
    int yyerror(char *errmsg);
    void errorMessage(char *msg);
    void warningMessage(char *msg);

    SymbolStack stack;
	ASTNode *programNode;
%}

%union{
	int iValue;
	float rValue;
	ASTNode *node;
	NodeList nodeList;

    StrtabIndexList indexList;
    ParameterList parameterList;
    Type type;
    TypeList typeList;
}

%token PROGRAM FUNCTION PROCEDURE BEG END IF THEN ELSE WHILE DO
%token VAR ARRAY OF ARRSEP INTEGER REAL
%token ASSIGNOP
%token RELOP_GR RELOP_GREQ RELOP_SM RELOP_SMEQ RELOP_NOEQ RELOP_EQ
%token ADDOP_MIN ADDOP_ADD
%token I_MULOP_M I_MULOP_D
%token R_MULOP_M R_MULOP_D
%token INUM RNUM ID

%type <node> Factor Term Simple_expression Expression Procedure_statement Statement Compound_statement Variable
%type <nodeList> Expression_list Statement_list Optional_statements Declarations
%type <indexList> Identifier_list Subprogram_head
%type <parameterList> Parameter_list Arguments
%type <type> Standard_type Type

%type <iValue> INUM
%type <rValue> RNUM
%type <indexList> ID


%start Program

%%  /****** grammar rules section ********/

/* --------- DECLARATIONS -------------- */

Program : PROGRAM
            ID
            '(' Identifier_list ')' ';'
            Declarations
            Subprogram_declarations
            Compound_statement
            '.'								{
												programNode = createProgramNode($2.indices[0], $7, $9);
											}

Identifier_list : ID { $$ = $1; }
                | Identifier_list ',' ID    {
                                                $$ = combineIdentifiers($1, $3);
                                            }

Declarations    : Declarations VAR Identifier_list ':' Type ';' {
                                                                    declareVariable($3, $5);
																	NodeList combined = $1;
																	for(int i = 0; i < $3.numberOfIndices ; i++){
																		ASTNode *declaration = createDeclarationNode($3.indices[i], $5);
																		NodeList declarations = createNodeList(declaration);
																		combined = combineNodeLists(combined, declarations);
																	}
																	$$ = combined;
                                                                }
                | /* Empty */									{
																	$$ = createEmptyNodeList();
																}


Type            : Standard_type {
                                    $$ = makeType($1.base, TYPE_SCALAR);
                                }
                | ARRAY '[' INUM '.''.' INUM ']' OF Standard_type   {
                                                                        $$ = makeType($9.base, TYPE_ARRAY);
                                                                    }

Standard_type   : INTEGER   {
                                $$.base = TYPE_INTEGER ;
                            }
                | REAL      {
                                $$.base = TYPE_REAL ;
                            }

Subprogram_declarations : Subprogram_declarations Subprogram_declaration ';'
                        | /* Empty */

Subprogram_declaration  : Subprogram_head
                            Declarations
                            Compound_statement  {
                                                    outdent(&stack);
                                                }

Subprogram_head : FUNCTION
                    ID
                    Arguments ':' Standard_type ';'     {
                                                            declareFunction($2, $5, $3);
                                                            indent(&stack);
                                                            declareFunctionLocallyAsVariable($2, $5);
                                                            declareParametersLocallyAsVariables($3);
															$$ = $2;
                                                        }
                | PROCEDURE
                    ID
                    Arguments ';'   {
                                        declareProcedure($2, $3);
                                        indent(&stack);
                                        declareParametersLocallyAsVariables($3);
										$$ = $2;
                                    }

Arguments       : '(' Parameter_list ')'    {
                                                $$ = $2;
                                            }
                | /* Empty */               {
                                                ParameterList list;
                                                list.numberOfParameters = 0;
                                                $$ = list;
                                            }

Parameter_list  : Identifier_list ':' Type  {
                                                $$ = createParameterList($1, $3);
                                            }
                | Parameter_list ';' Identifier_list ':' Type   {
																	ParameterList l = createParameterList($3, $5);
																	$$ = combineParameterLists($1, l);
																}

/* --------- STATEMENTS -------------- */

Compound_statement  : BEG
                      Optional_statements
                      END							{ $$ = createCompoundStatementNode($2);}

Optional_statements : Statement_list				{ $$ = $1;}
                    | /* Empty */

Statement_list  : Statement							{
														NodeList list = createNodeList($1);
														$$ = list;
													}
                | Statement_list ';' Statement		{
														NodeList list = combineNodeLists($1, createNodeList($3));
														$$ = list;
													}

Statement       : Variable ASSIGNOP Expression 	{
	 												checkAssignment($1, $3);
													$$ = createAssignmentNode($1, $3);
												}
                | Procedure_statement							{
																	$$ = $1;
																}
                | Compound_statement							{
																	$$ = $1;
																}
                | IF Expression THEN Statement ELSE Statement	{
																	checkCondition($2);
																	$$ = createIfElseNode($2, $4, $6);
																}
                | WHILE Expression DO Statement					{
																	checkCondition($2);
																	$$ = createWhileNode($2, $4);
																}

Variable        : ID                          {
                                                  checkIfIdentifierIsDeclared($1.indices[0]);
                                                  checkIdentifierIdType($1.indices[0], TYPE_VARIABLE);
												  checkIdentifierSecondaryType($1.indices[0], TYPE_SCALAR);
												  IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
												  VariableData *data = (VariableData *)entry->data;
												  $$ = createVariableNode($1.indices[0], *data->type);
                                              }
                | ID '[' Expression_list ']'  {
                                                  checkIfIdentifierIsDeclared($1.indices[0]);
                                                  checkIdentifierIdType($1.indices[0], TYPE_VARIABLE);
                                                  checkIdentifierSecondaryType($1.indices[0], TYPE_ARRAY);
												  checkIfMultipleArrayIndicesAreAllIntegers($3);
												  IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
												  VariableData *data = (VariableData *)entry->data;
												  $$ = createArrayVariableNode($1.indices[0], *data->type, $3);
                                              }

Procedure_statement : ID                        {
													checkIfIdentifierIsDeclared($1.indices[0]);
													checkIdentifierIdType($1.indices[0], TYPE_PROCEDURE);
													$$ = createProcedureCallNode($1.indices[0], createEmptyNodeList());
												}
                    | ID '(' Expression_list ')'  	{
														checkIfIdentifierIsDeclared($1.indices[0]);
														checkIdentifierIdType($1.indices[0], TYPE_PROCEDURE);
														checkParameterCountAndTypes($1.indices[0], $3, TYPE_PROCEDURE);
														$$ = createProcedureCallNode($1.indices[0], $3);
													}

Expression_list : Expression						{
														NodeList list = createNodeList($1);
														$$ = list;
													}
                | Expression_list ',' Expression	{
														NodeList list = combineNodeLists($1, createNodeList($3));
														$$ = list;
													}

Expression      : Simple_expression                           		{
                                                                  		$$ = $1;
                                                              		}
                | Simple_expression RELOP_GR Simple_expression   	{
																		checkTypes($1, $3, OP_RELOP_GR);
																		$$ = createExpressionNode($1, $3, OP_RELOP_GR);
                                                              		}
                | Simple_expression RELOP_GREQ Simple_expression   	{
																		checkTypes($1, $3, OP_RELOP_GREQ);
																		$$ = createExpressionNode($1, $3, OP_RELOP_GREQ);
                                                              		}
                | Simple_expression RELOP_SM Simple_expression   	{
																		checkTypes($1, $3, OP_RELOP_SM);
																		$$ = createExpressionNode($1, $3, OP_RELOP_SM);
                                                              		}
                | Simple_expression RELOP_SMEQ Simple_expression   	{
																		checkTypes($1, $3, OP_RELOP_SMEQ);
																		$$ = createExpressionNode($1, $3, OP_RELOP_SMEQ);
                                                              		}
                | Simple_expression RELOP_NOEQ Simple_expression   	{
																		checkTypes($1, $3, OP_RELOP_NOEQ);
																		$$ = createExpressionNode($1, $3, OP_RELOP_NOEQ);
                                                              		}
                | Simple_expression RELOP_EQ Simple_expression   	{
																		checkTypes($1, $3, OP_RELOP_EQ);
																		$$ = createExpressionNode($1, $3, OP_RELOP_EQ);
                                                              		}

Simple_expression   : Term                          {
                                                        $$ = $1;
                                                    }
                    | ADDOP_MIN Term                {
                                                        $$ = $2;		// TODO: Not ignore the addop
                                                    }
                    | ADDOP_ADD Term                {
                                                        $$ = $2;		// TODO: Not ignore the addop
                                                    }
                    | Simple_expression ADDOP_MIN Term  {
                                                        	checkTypes($1, $3, OP_ADDOP_MIN);
															$$ = createExpressionNode($1, $3, OP_ADDOP_MIN);
                                                    	}
                    | Simple_expression ADDOP_ADD Term  {
                                                        	checkTypes($1, $3, OP_ADDOP_ADD);
															$$ = createExpressionNode($1, $3, OP_ADDOP_ADD);
                                                    	}

Term            : Factor                        {
                                                    $$ = $1;
                                                }
                | Term R_MULOP_D Factor         {
													checkTypes($1, $3, OP_R_MULOP_D);
													$$ = createExpressionNode($1, $3, OP_R_MULOP_D);
                                                }
                | Term R_MULOP_M Factor         {
													checkTypes($1, $3, OP_R_MULOP_M);
													$$ = createExpressionNode($1, $3, OP_R_MULOP_M);
                                                }
                | Term I_MULOP_D Factor         {
													checkTypes($1, $3, OP_I_MULOP_D);
													$$ = createExpressionNode($1, $3, OP_I_MULOP_D);
                                                }
                | Term I_MULOP_M Factor         {
													checkTypes($1, $3, OP_I_MULOP_M);
													$$ = createExpressionNode($1, $3, OP_I_MULOP_M);
                                                }

Factor          : ID                            {
                                                    checkIfIdentifierIsDeclared($1.indices[0]);
                                                    checkIdentifierIdType($1.indices[0], TYPE_VARIABLE);
                                                    IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
                                                    VariableData *data = (VariableData *)entry->data;
                                                    $$ = createVariableNode($1.indices[0], *data->type);

                                                }
                | ID '(' Expression_list ')'    {
                                                    checkIfIdentifierIsDeclared($1.indices[0]);
                                                    checkIdentifierIdType($1.indices[0], TYPE_FUNCTION);
													checkParameterCountAndTypes($1.indices[0], $3, TYPE_FUNCTION);
                                                    IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
                                                    FunctionData *data = (FunctionData *)entry->data;
													$$ = createFunctionCallNode($1.indices[0], *data->returnType, $3);
												}
                | INUM                          {
													$$ = createIValueNode($1);
                                                }
                | RNUM                          {
                                                    $$ = createRValueNode($1);
                                                }
                | '(' Expression ')'            {
                                                    $$ = $2;
                                                }
                | ID '[' Simple_expression ']'  {
                                                    checkIfIdentifierIsDeclared($1.indices[0]);
                                                    checkIdentifierIdType($1.indices[0], TYPE_VARIABLE);
                                                    checkIdentifierSecondaryType($1.indices[0], TYPE_ARRAY);
													checkIfArrayIndexIsInteger($3);
                                                    IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
                                                    VariableData *data = (VariableData *)entry->data;
                                                    $$ = createArrayNode($1.indices[0], *data->type, $3);
													//printf("Array\n");
                                                }

%%
// ----------- CHECKING -----

// This function checks if the given type of the condition expression is boolean
void checkCondition(ASTNode *node){
	Type type = determineType(node);
	if(type.base != TYPE_BOOL){
		char *err;
		asprintf(&err, "conditions need to be booleans");
		errorMessage(err);
	}
}

// This function checks if the two types in an assignment will result in truncation
void checkAssignment(ASTNode *left, ASTNode *right){
	Type typeLeft = determineType(left);
	Type typeRight = determineType(right);
	if(typeLeft.base == TYPE_INTEGER && typeRight.base == TYPE_REAL){
		char *war;
        asprintf(&war, "assigning an real to an integer will result in truncation");
        warningMessage(war);
	}
}

/* This function checks two things:
	1. Is the correct amount of parameters given
	2. Are the given parameters of the right type
*/
void checkParameterCountAndTypes(unsigned id, NodeList arguments, IdType type){
	IdEntry *entry = lookupSymbol(&stack, id);
	ParameterList params;
	if(entry->idType != type)
		entry = findShadowedFunctionOrProcedure(&stack, id);

	if(type ==  TYPE_FUNCTION)
		params = *((FunctionData *)entry->data)->parameters;
	else
		params = *((ProcedureData *)entry->data)->parameters;

	if(params.numberOfParameters != arguments.n){
		char *err;
		asprintf(&err, "expected %d parameters but got %d instead", params.numberOfParameters, arguments.n);
		errorMessage(err);
	}

	for(int i = 0; i < params.numberOfParameters; i++){
		ASTNode *argument = arguments.nodes[i];
		Type argumentType = determineType(argument);
		if(params.parameters[i]->type->secondary != argumentType.secondary){
			char *err;
			asprintf(&err, "parameter %s of %s is of type %s %s but received %s %s",	retrieveFromStringTable(*(stack.strTab), params.parameters[i]->strtabIndex), retrieveFromStringTable(*(stack.strTab), id),
																						baseTypeString(params.parameters[i]->type->base), secondaryTypeString(params.parameters[i]->type->secondary),
																						baseTypeString(argumentType.base), secondaryTypeString(argumentType.secondary)
																				);
			errorMessage(err);
		}
		if(params.parameters[i]->type->base != argumentType.base){
			char *war;
			asprintf(&war, "parameter %s of %s is of type %s %s but received %s %s",	retrieveFromStringTable(*(stack.strTab), params.parameters[i]->strtabIndex), retrieveFromStringTable(*(stack.strTab), id),
																						baseTypeString(params.parameters[i]->type->base), secondaryTypeString(params.parameters[i]->type->secondary),
																						baseTypeString(argumentType.base), secondaryTypeString(argumentType.secondary)
																				);
			warningMessage(war);
		}
	}
}

// Checks for one index of an array if it is the right type
void checkIfArrayIndexIsInteger(ASTNode *node){
	Type type = determineType(node);
	if(type.base != TYPE_INTEGER){
		char *err;
		asprintf(&err, "array index should be an integer");
		errorMessage(err);
	}
}

// This method checks if all given indexes of an array are of the right type
void checkIfMultipleArrayIndicesAreAllIntegers(NodeList indices){
	for(int i =0; i < indices.n; i++){
		ASTNode *node = indices.nodes[i];
		checkIfArrayIndexIsInteger(node);
	}
}

void checkTypes(ASTNode *node1, ASTNode *node2, Operator operator){
	Type t1 = determineType(node1);
	Type t2 = determineType(node2);

  switch(operator){
	case OP_RELOP_GR :
  	case OP_RELOP_GREQ :
  	case OP_RELOP_SM :
  	case OP_RELOP_SMEQ :
  	case OP_RELOP_NOEQ :
  	case OP_RELOP_EQ : {
      if(t1.base != t1.base){
        char *war;
        asprintf(&war, "comparing integers with reals");
        warningMessage(war);
      }
	  return;
    }
	case OP_I_MULOP_D :
    case OP_I_MULOP_M : {
      if(t1.base == TYPE_REAL || t2.base == TYPE_REAL){
        char *war;
        asprintf(&war, "integer operation on real");
        warningMessage(war);
      }
      return;
    }
	case OP_R_MULOP_D :
    case OP_R_MULOP_M :
	case OP_ADDOP_ADD :
    case OP_ADDOP_MIN : return;
    default: { // SHOULD NEVER OCCUR
      char *err;
      asprintf(&err, "invalid binary token, something went very very very wrong...");
      errorMessage(err);
	  return;
    }
  }
}

// This method checks if the identifier is of the correct type, REAL OR INTEGER
void checkIdentifierSecondaryType(unsigned index, SecondaryType t){
  IdEntry *entry = lookupSymbol(&stack, index);
  VariableData *data = (VariableData *)entry->data;
  if(data->type->secondary != t){
    char *err;
    asprintf(&err, "variable %s is %s and not %s", retrieveFromStringTable(*(stack.strTab), index), secondaryTypeString(data->type->secondary), secondaryTypeString(t));
    errorMessage(err);
  }
}

// This method checks if the identifier is of the correct type, SCALAR OR ARRAY
void checkIdentifierIdType(unsigned index, IdType t){
  IdEntry *entry = lookupSymbol(&stack, index);
  if(entry->idType != t){
    IdEntry *shadow = findShadowedFunctionOrProcedure(&stack, index);     // Recursion
    if(shadow == NULL){
      char *err;
      asprintf(&err, "variable %s is %s and not %s", retrieveFromStringTable(*(stack.strTab), index), idTypeString(entry->idType), idTypeString(t));
      errorMessage(err);
    }
  }
}


// This method checks if the identifier is already declared
void checkIfIdentifierIsDeclared(unsigned index){
    IdEntry *entry = lookupSymbol(&stack, index);
    if(entry == NULL){
        char *err;
        asprintf(&err, "variable %s is not yet declared", retrieveFromStringTable(*(stack.strTab), index));
        errorMessage(err);
    }
}

// This method inserts a new entry in the symbol table, and reports if this is not possible
void insert(IdEntry entry){
    if(!insertSymbol(&stack, entry)){
        char *err;
        asprintf(&err, "variable %s is already declared\n", retrieveFromStringTable(*(stack.strTab), entry.strtabIndex));
        errorMessage(err);
    }
}

// ---------- DECLARING -------

void declareVariable(StrtabIndexList indentifiers, Type type){
    for(int i = indentifiers.numberOfIndices-1 ; i >= 0 ; i--){
        VariableData *data = safeMalloc(sizeof(VariableData *));

		data->type = safeMalloc(sizeof(Type));
		memcpy(data->type, &type, sizeof(Type));

        IdEntry newEntry = makeIdEntry(indentifiers.indices[i]);
        newEntry.data = data;
        newEntry.idType = TYPE_VARIABLE;

        insert(newEntry);
    }
}

void declareFunction(StrtabIndexList indentifiers, Type type, ParameterList parameters){
    FunctionData data;

	data.returnType = safeMalloc(sizeof(Type));
	memcpy(data.returnType, &type, sizeof(Type));

	data.parameters = safeMalloc(sizeof(ParameterList));
	memcpy(data.parameters, &parameters, sizeof(ParameterList));

    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = safeMalloc(sizeof(FunctionData));
	memcpy(newEntry.data, &data, sizeof(FunctionData));
    newEntry.idType = TYPE_FUNCTION;

    insert(newEntry);
}

void declareProcedure(StrtabIndexList indentifiers, ParameterList parameters){
    ProcedureData *data = safeMalloc(sizeof(ProcedureData *));
	data->parameters = safeMalloc(sizeof(ParameterList));
	memcpy(data->parameters, &parameters, sizeof(ParameterList));
    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
    newEntry.idType = TYPE_PROCEDURE;
	insert(newEntry);
}

void declareParametersLocallyAsVariables(ParameterList list){
    for(int i = 0 ; i < list.numberOfParameters ; i++){
        VariableData *data = safeMalloc(sizeof(VariableData *));

		data->type = list.parameters[i]->type;

        IdEntry newEntry = makeIdEntry(list.parameters[i]->strtabIndex);
        newEntry.data = data;
        newEntry.idType = TYPE_VARIABLE;
        insert(newEntry);
    }
}

void declareFunctionLocallyAsVariable(StrtabIndexList indentifiers, Type type){
    VariableData *data = safeMalloc(sizeof(VariableData *));
	data->type = safeMalloc(sizeof(Type));
	memcpy(data->type, &type, sizeof(Type));
    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
    newEntry.idType = TYPE_VARIABLE;
    insert(newEntry);
}

// ------------- ERRORS & WARNINGS -----------------------
int yyerror(char *errmsg) {
    char *err = "parse error";
    errorMessage(err);
    return 1;
}

void errorMessage(char *msg){
    fprintf(stderr, "\x1B[31m" "(%d) error : " "\x1B[0m" "%s\n", lineno, msg);
    // Yes, a parse error is a successful (meaningful) result
    freeStringTable(strTab);
    exit(EXIT_SUCCESS);
}

void warningMessage(char *msg){
    fprintf(stderr,"\x1B[35m" "(%d) warning : " "\x1B[0m" "%s\n", lineno, msg);
}

// ------------- MAIN --------------------------
int main(int argc, char **argv) {
    //yydebug = 1;
    strTab = newStringTable(0);
    stack = initSymbolStack(&strTab);
    yyparse();
    printf("\x1B[32m" "ACCEPTED\n" "\x1B[0m");
	generateIR(stdin, programNode);
    freeSymbolStack(&stack);
    freeStringTable(strTab);
    return 0;
}
