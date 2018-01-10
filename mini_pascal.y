
%{
    #include "IdEntry.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include "lex.yy.c"
    #include "StringTable.h"
    #include "SymbolStack.h"
    #include "common.h"

    // CHECKING
	void checkCondition(Type);
	void checkAssignment(Type, Type);
    void checkIfIdentifierIsDeclared(unsigned);
    void checkIdentifierIdType(unsigned, IdType);
    void checkIdentifierSecondaryType(unsigned, SecondaryType);
	void checkIfArrayIndexIsInteger(Type);
	void checkIfMultipleArrayIndicesAreAllIntegers(TypeList types);
	void checkParameterCountAndTypes(unsigned id, TypeList list, IdType type);
    Type checkTypes(Type, Type, enum yytokentype);

    void declareFunctionLocallyAsVariable(StrtabIndexList, Type type);
    void declareParametersLocallyAsVariables(ParameterList);

    void declareVariable(StrtabIndexList, Type);
    void declareFunction(StrtabIndexList, Type, ParameterList);
    void declareProcedure(StrtabIndexList, ParameterList);

    int yyerror(char *errmsg);
    void errorMessage(char *msg);
    void warningMessage(char *msg);

    SymbolStack stack;
%}

%union{
    StrtabIndexList indexList;
    ParameterList parameterList;
    Type type;
    TypeList typeList;
}

%token PROGRAM FUNCTION PROCEDURE BEG END IF THEN ELSE WHILE DO
%token VAR ARRAY OF ARRSEP INTEGER REAL
%token ASSIGNOP RELOP ADDOP I_MULOP R_MULOP INUM RNUM ID

%type <indexList> Identifier_list
%type <parameterList> Parameter_list Arguments
%type <type> Standard_type Type Factor Term Expression Simple_expression Variable
%type <typeList> Expression_list

%type <indexList> ID INUM RNUM


%start Program

%%  /****** grammar rules section ********/

Program : PROGRAM
            ID
            '(' Identifier_list ')' ';'
            Declarations
            Subprogram_declarations
            Compound_statement
            '.' {
                    //declareIdentifiers($2, makeEmptyType(), TYPE_PROGRAM);
                }

Identifier_list : ID { $$ = $1; }
                | Identifier_list ',' ID    {
                                                $$ = combineIdentifiers($1, $3);
                                            }

Declarations    : Declarations VAR Identifier_list ':' Type ';' {
                                                                    declareVariable($3, $5);
                                                                }
                | /* Empty */


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
															//printSymbolStack(&stack);
                                                        }
                | PROCEDURE
                    ID
                    Arguments ';'   {
                                        declareProcedure($2, $3);
                                        indent(&stack);
                                        declareParametersLocallyAsVariables($3);
										//printSymbolStack(&stack);
                                    }

Arguments       : '(' Parameter_list ')'    {
												//printf("%d\n", $2->parameters[0].strtabIndex);
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
                                                                    appendParameterLists(&$1, $3, $5);
																	$$ = $1;

																}

Compound_statement  : BEG
                      Optional_statements
                      END

Optional_statements : Statement_list
                    | /* Empty */

Statement_list  : Statement
                | Statement_list ';' Statement

Statement       : Variable ASSIGNOP Expression 	{
	 												checkAssignment($1, $3);
												}
                | Procedure_statement
                | Compound_statement
                | IF Expression THEN Statement ELSE Statement	{
																	checkCondition($2);
																}
                | WHILE Expression DO Statement					{
																	checkCondition($2);
																}

Variable        : ID                          {
                                                  checkIfIdentifierIsDeclared($1.indices[0]);
                                                  checkIdentifierIdType($1.indices[0], TYPE_VARIABLE);
												  checkIdentifierSecondaryType($1.indices[0], TYPE_SCALAR);
												  IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
												  VariableData *data = (VariableData *)entry->data;
												  $$ = *data->type;
                                              }
                | ID '[' Expression_list ']'  {
                                                  checkIfIdentifierIsDeclared($1.indices[0]);
                                                  checkIdentifierIdType($1.indices[0], TYPE_VARIABLE);
                                                  checkIdentifierSecondaryType($1.indices[0], TYPE_ARRAY);
												  checkIfMultipleArrayIndicesAreAllIntegers($3);
												  IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
												  VariableData *data = (VariableData *)entry->data;
												  $$ = *data->type;
												  $$.secondary = TYPE_SCALAR;
                                              }

Procedure_statement : ID                        {
													checkIfIdentifierIsDeclared($1.indices[0]);
													checkIdentifierIdType($1.indices[0], TYPE_PROCEDURE);
												}
                    | ID '(' Expression_list ')'  	{
														checkIfIdentifierIsDeclared($1.indices[0]);
														checkIdentifierIdType($1.indices[0], TYPE_PROCEDURE);
														checkParameterCountAndTypes($1.indices[0], $3, TYPE_PROCEDURE);
													}

Expression_list : Expression						{
														$$ = createTypeList($1);
													}
                | Expression_list ',' Expression	{
														appendToTypeLists(&$1, $3);
														$$ = $1;
													}

Expression      : Simple_expression                           {
                                                                  $$ = $1;
                                                              }
                | Simple_expression RELOP Simple_expression   {
                                                                  $$ = checkTypes($1, $3, RELOP);
                                                              }

Simple_expression   : Term                          {
                                                        $$ = $1;
                                                    }
                    | ADDOP Term                    {
                                                        $$ = $2;
                                                    }
                    | Simple_expression ADDOP Term  {
                                                        $$ = checkTypes($1, $3, ADDOP);
                                                    }

Term            : Factor                        {
                                                    $$ = $1;
                                                }
                | Term R_MULOP Factor             {
                                                    $$ = checkTypes($1, $3, R_MULOP);
                                                }
                | Term I_MULOP Factor             {
                                                    $$ = checkTypes($1, $3, I_MULOP);
                                                }

Factor          : ID                            {
                                                    checkIfIdentifierIsDeclared($1.indices[0]);
                                                    checkIdentifierIdType($1.indices[0], TYPE_VARIABLE);
                                                    checkIdentifierSecondaryType($1.indices[0], TYPE_SCALAR);
                                                    IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
                                                    VariableData *data = (VariableData *)entry->data;
                                                    $$ = *data->type;

                                                }
                | ID '(' Expression_list ')'    {
                                                    checkIfIdentifierIsDeclared($1.indices[0]);
                                                    checkIdentifierIdType($1.indices[0], TYPE_FUNCTION);
													checkParameterCountAndTypes($1.indices[0], $3, TYPE_FUNCTION);
                                                    IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
                                                    FunctionData *data = (FunctionData *)entry->data;
                                                    $$ = *data->returnType;
                                                }
                | INUM                          {
                                                    $$.base = TYPE_INTEGER;
                                                    $$.secondary = TYPE_SCALAR;
                                                }
                | RNUM                          {
                                                    $$.base = TYPE_REAL;
                                                    $$.secondary = TYPE_SCALAR;
                                                }
                | '(' Expression ')'            {
                                                    $$ = $2;
                                                }
                | ID '[' Simple_expression ']'  {   // simple expression moet integer zijn
                                                    checkIfIdentifierIsDeclared($1.indices[0]);
                                                    checkIdentifierIdType($1.indices[0], TYPE_VARIABLE);
                                                    checkIdentifierSecondaryType($1.indices[0], TYPE_ARRAY);
													checkIfArrayIndexIsInteger($3);
                                                    IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
                                                    VariableData *data = (VariableData *)entry->data;
                                                    $$ = *data->type;
                                                    $$.secondary = TYPE_SCALAR;
                                                }

%%
// ----------- CHECKING -----

void checkCondition(Type t1){
	if(t1.base != TYPE_BOOL){
		char *err;
		asprintf(&err, "conditions need to be booleans");
		errorMessage(err);
	}
}

void checkAssignment(Type t1, Type t2){
	if(t1.base == TYPE_INTEGER && t2.base == TYPE_REAL){
		char *war;
        asprintf(&war, "assigning an real to an integer will result in truncation");
        warningMessage(war);
	}
}

void checkParameterCountAndTypes(unsigned id, TypeList list, IdType type){
	//printSymbolStack(&stack);
	IdEntry *entry = lookupSymbol(&stack, id);
	ParameterList params;
	if(entry->idType != type)
		entry = findShadowedFunctionOrProcedure(&stack, id);

	if(type ==  TYPE_FUNCTION)
		params = *((FunctionData *)entry->data)->parameters;
	else
		params = *((ProcedureData *)entry->data)->parameters;

	//printf("expected %d parameters but got %d instead\n", params.numberOfParameters, list.numberOfTypes);
	if(params.numberOfParameters != list.numberOfTypes){
		char *err;
		asprintf(&err, "expected %d parameters but got %d instead", params.numberOfParameters, list.numberOfTypes);
		errorMessage(err);
	}

	for(int i = 0; i < params.numberOfParameters; i++){
		if(params.parameters[i]->type->secondary != list.types[i]->secondary){
			char *err;
			asprintf(&err, "parameter %s of %s is of type %s %s but received %s %s",	retrieveFromStringTable(*(stack.strTab), params.parameters[i]->strtabIndex), retrieveFromStringTable(*(stack.strTab), id),
																						baseTypeString(params.parameters[i]->type->base), secondaryTypeString(params.parameters[i]->type->secondary),
																						baseTypeString(list.types[i]->base), secondaryTypeString(list.types[i]->secondary)
																				);
			errorMessage(err);
		}
		if(params.parameters[i]->type->base != list.types[i]->base){
			char *war;
			asprintf(&war, "parameter %s of %s is of type %s %s but received %s %s",	retrieveFromStringTable(*(stack.strTab), params.parameters[i]->strtabIndex), retrieveFromStringTable(*(stack.strTab), id),
																						baseTypeString(params.parameters[i]->type->base), secondaryTypeString(params.parameters[i]->type->secondary),
																						baseTypeString(list.types[i]->base), secondaryTypeString(list.types[i]->secondary)
																				);
			warningMessage(war);
		}
	}
}

void checkIfArrayIndexIsInteger(Type type){
	if(type.base != TYPE_INTEGER){
		char *err;
		asprintf(&err, "array index should be an integer");
		errorMessage(err);
	}
}

void checkIfMultipleArrayIndicesAreAllIntegers(TypeList types){
	for(int i =0; i < types.numberOfTypes; i++){
		checkIfArrayIndexIsInteger(*types.types[i]);
	}
}

Type checkTypes(Type t1, Type t2, enum yytokentype token){
  switch(token){
    case RELOP : {
      if(t1.base != t1.base){
        char *war;
        asprintf(&war, "comparing integers with reals");
        warningMessage(war);
      }
      return makeType(TYPE_BOOL, TYPE_SCALAR);
    }
    case I_MULOP : {
      if(t1.base == TYPE_REAL || t2.base == TYPE_REAL){
        char *err;
        asprintf(&err, "integer operation on real");
        errorMessage(err);
      }
      return makeType(TYPE_INTEGER, TYPE_SCALAR);
    }
    case R_MULOP : {
      return makeType(TYPE_REAL, TYPE_SCALAR);
    }
    case ADDOP : {
      if(t1.base == t2.base){ // SAME TYPE NO ISSUE
        return t1;
      }
      return makeType(TYPE_REAL, TYPE_SCALAR);
    }
    default: { // SHOULD NEVER OCCUR
      char *err;
      asprintf(&err, "invalid binary token, something went very very very wrong...");
      errorMessage(err);
	  return makeType(TYPE_REAL, TYPE_SCALAR);	// stops warning;
    }
  }
}

void checkIdentifierSecondaryType(unsigned index, SecondaryType t){
  IdEntry *entry = lookupSymbol(&stack, index);
  VariableData *data = (VariableData *)entry->data;
  if(data->type->secondary != t){
    char *err;
    asprintf(&err, "variable %s is %s and not %s", retrieveFromStringTable(*(stack.strTab), index), secondaryTypeString(data->type->secondary), secondaryTypeString(t));
    errorMessage(err);
  }
}

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

void checkIfIdentifierIsDeclared(unsigned index){
    IdEntry *entry = lookupSymbol(&stack, index);
    if(entry == NULL){
        //printSymbolStack(&stack);
        char *err;
        asprintf(&err, "variable %s is not yet declared", retrieveFromStringTable(*(stack.strTab), index));
        errorMessage(err);
    }
}

// ---------- DECLARING -------

void insert(IdEntry entry){
    if(!insertSymbol(&stack, entry)){
        char *err;
        asprintf(&err, "variable %s is already declared\n", retrieveFromStringTable(*(stack.strTab), entry.strtabIndex));
        errorMessage(err);
    }
}

void declareVariable(StrtabIndexList indentifiers, Type type){
    //printf("declareVariable\n");
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
    FunctionData *data = safeMalloc(sizeof(FunctionData *));

	data->returnType = safeMalloc(sizeof(Type));
	memcpy(data->returnType, &type, sizeof(Type));

	data->parameters = safeMalloc(sizeof(ParameterList));
	memcpy(data->parameters, &parameters, sizeof(ParameterList));

    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
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
    //printf("declareParametersLocallyAsVariables : %d\n", list.numberOfParameters);
    for(int i = 0 ; i < list.numberOfParameters ; i++){
		//printf("base: %s -> secondary : %s \n", baseTypeString(list.parameters[i].type.base), secondaryTypeString(list.parameters[i].type.secondary));
        VariableData *data = safeMalloc(sizeof(VariableData *));

		data->type = list.parameters[i]->type;/*safeMalloc(sizeof(Type));
		memcpy(data->type, &list.parameters[i]->type, sizeof(Type));*/

        IdEntry newEntry = makeIdEntry(list.parameters[i]->strtabIndex);
        newEntry.data = data;
        newEntry.idType = TYPE_VARIABLE;
		//printEntry(newEntry, *stack.strTab);
        insert(newEntry);
    }
	//printSymbolStack(&stack);
	//printSymbolStack(&stack);
}

void declareFunctionLocallyAsVariable(StrtabIndexList indentifiers, Type type){
	//printSymbolStack(&stack);
    VariableData *data = safeMalloc(sizeof(VariableData *));
	//printf("base: %s -> secondary : %s \n", baseTypeString(type.base), secondaryTypeString(type.secondary));
	data->type = safeMalloc(sizeof(Type));
	memcpy(data->type, &type, sizeof(Type));
	//printf("base: %s -> secondary : %s \n", baseTypeString(data->type.base), secondaryTypeString(data->type.secondary));

    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
    newEntry.idType = TYPE_VARIABLE;
	//printEntry(newEntry, *stack.strTab);
    insert(newEntry);
	//printSymbolStack(&stack);
    //printSymbolStack(&stack);
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
    printf("ACCEPTED\n");
    //printStringTable(strTab);
    //printSymbolStack(&stack);
    freeStringTable(strTab);
    return 0;
}
