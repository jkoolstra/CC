
%{
    #include "IdEntry.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include "lex.yy.c"
    #include "StringTable.h"
    #include "SymbolStack.h"
    #include "common.h"

    // CHECKING
    void checkIfIdentifierIsDeclared(unsigned);
    void checkIfIdentifierIsOfType(unsigned, IdType);
    void checkIfIdentifierIsArray(unsigned index);
    Type checkTypes(Type, Type, enum yytokentype);

    StrtabIndexList combineIdentifiers(StrtabIndexList, StrtabIndexList);
    ParameterList createParameterList(StrtabIndexList list, Type t);
    ParameterList combineParameterLists(ParameterList listOne, ParameterList listTwo);

    void declareFunctionLocallyAsVariable(StrtabIndexList, Type type);
    void declareParametersLocallyAsVariables(ParameterList);

    void declareVariable(StrtabIndexList indentifiers, Type type);
    void declareFunction(StrtabIndexList indentifiers, Type type, ParameterList parameters);
    void declareProcedure(StrtabIndexList indentifiers, ParameterList parameters);

    int yyerror(char *errmsg);
    void errorMessage(char *msg);

    SymbolStack stack;
%}

%union{
    StrtabIndexList indexList;
    ParameterList parameterList;
    Type type;
}

%token PROGRAM FUNCTION PROCEDURE BEG END IF THEN ELSE WHILE DO
%token VAR ARRAY OF ARRSEP INTEGER REAL
%token ASSIGNOP RELOP ADDOP I_MULOP R_MULOP INUM RNUM ID

%type <indexList> Identifier_list
%type <parameterList> Parameter_list Arguments
%type <type> Standard_type Type Factor Term Expression Simple_expression

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
                                    $$ = $1;
                                    $$.secondary = TYPE_SINGLE;
                                }
                | ARRAY '[' INUM '.''.' INUM ']' OF Standard_type   {
                                                                        $$ = $9;
                                                                        $$.secondary = TYPE_ARRAY;
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
                                                        }
                | PROCEDURE
                    ID
                    Arguments ';'   {
                                        declareProcedure($2, $3);
                                        indent(&stack);
                                        declareParametersLocallyAsVariables($3);
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
                                                                    ParameterList secondList = createParameterList($3, $5);
                                                                    $$ = combineParameterLists($1, secondList);
                                                                }

Compound_statement  : BEG
                      Optional_statements
                      END

Optional_statements : Statement_list
                    | /* Empty */

Statement_list  : Statement
                | Statement_list ';' Statement

Statement       : Variable ASSIGNOP Expression { }
                | Procedure_statement
                | Compound_statement
                | IF Expression THEN Statement ELSE Statement
                | WHILE Expression DO Statement

Variable        : ID                          {
                                                  checkIfIdentifierIsDeclared($1.indices[0]);
                                                  checkIfIdentifierIsOfType($1.indices[0], TYPE_VARIABLE);
                                              }
                | ID '[' Expression_list ']'  {
                                                  checkIfIdentifierIsDeclared($1.indices[0]);
                                                  checkIfIdentifierIsOfType($1.indices[0], TYPE_VARIABLE);
                                                  checkIfIdentifierIsArray($1.indices[0]);
                                              }

Procedure_statement : ID                          { checkIfIdentifierIsDeclared($1.indices[0]); checkIfIdentifierIsOfType($1.indices[0], TYPE_PROCEDURE); }
                    | ID '(' Expression_list ')'  { checkIfIdentifierIsDeclared($1.indices[0]); checkIfIdentifierIsOfType($1.indices[0], TYPE_PROCEDURE); }

Expression_list : Expression
                | Expression_list ',' Expression

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
                                                    checkIfIdentifierIsOfType($1.indices[0], TYPE_VARIABLE);
                                                    // check dat het een scalar is
                                                    IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
                                                    VariableData *data = (VariableData *)entry->data;
                                                    $$ = data->type;

                                                }
                | ID '(' Expression_list ')'    {
                                                    checkIfIdentifierIsDeclared($1.indices[0]);
                                                    checkIfIdentifierIsOfType($1.indices[0], TYPE_FUNCTION);
                                                    IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
                                                    FunctionData *data = (FunctionData *)entry->data;
                                                    $$ = data->returnType;
                                                }
                | INUM                          {
                                                    $$.base = TYPE_INTEGER;
                                                    $$.secondary = TYPE_SINGLE;
                                                }
                | RNUM                          {
                                                    $$.base = TYPE_REAL;
                                                    $$.secondary = TYPE_SINGLE;
                                                }
                | '(' Expression ')'            {
                                                    $$ = $2;
                                                }
                | ID '[' Simple_expression ']'  {   // simple expression moet integer zijn
                                                    checkIfIdentifierIsDeclared($1.indices[0]);
                                                    checkIfIdentifierIsOfType($1.indices[0], TYPE_VARIABLE);
                                                    checkIfIdentifierIsArray($1.indices[0]);
                                                    IdEntry *entry = lookupSymbol(&stack,$1.indices[0]);
                                                    VariableData *data = (VariableData *)entry->data;
                                                    $$ = data->type;
                                                    $$.secondary = TYPE_SINGLE;
                                                }

%%
// ----------- CHECKING -----

Type checkTypes(Type t1, Type t2, enum yytokentype token){
  if(token == RELOP){
    if(t1.secondary == TYPE_ARRAY || t1.secondary == TYPE_ARRAY){
      char *err;
      asprintf(&err, "CANT COMPARE ARRAYS");
      errorMessage(err);
    }
    Type t;
    t.secondary = TYPE_SINGLE;
    t.base = TYPE_BOOL;
    return t;
  } else {
    if(t1.secondary == TYPE_ARRAY || t1.secondary == TYPE_ARRAY){
      char *err;
      asprintf(&err, "ARRAY ARITHMETICS IS NOT POSSIBLE");
      errorMessage(err);
    }
    if(t1.base == t2.base){ // SAME TYPE NO ISSUE
      return t1;
    }
    Type t;
    t.secondary = TYPE_SINGLE;
    t.base = TYPE_REAL;
    return t;
  }
}



void checkIfIdentifierIsArray(unsigned index){
  IdEntry *entry = lookupSymbol(&stack, index);
  VariableData *data = (VariableData *)entry->data;
  if(data->type.secondary != TYPE_ARRAY){
    char *err;
    asprintf(&err, "VARIABLE %s IS A SCALAR AND NOT AN ARRAY", retrieveFromStringTable(*(stack.strTab), index));
    errorMessage(err);
  }
}

void checkIfIdentifierIsOfType(unsigned index, IdType t){
  IdEntry *entry = lookupSymbol(&stack, index);
  if(entry->idType != t){
    IdEntry *shadow = findShadowedFunctionOrProcedure(&stack, index);     // Recursion
    if(shadow == NULL){
      char *err;
      asprintf(&err, "VARIABLE %s IS A %s AND NOT A %s", retrieveFromStringTable(*(stack.strTab), index), idTypeString(entry->idType), idTypeString(t));
      errorMessage(err);
    }
  }
}

void checkIfIdentifierIsDeclared(unsigned index){
    IdEntry *entry = lookupSymbol(&stack, index);
    if(entry == NULL){
        //printSymbolStack(&stack);
        char *err;
        asprintf(&err, "VARIABLE %s NOT YET DECLARED", retrieveFromStringTable(*(stack.strTab), index));
        errorMessage(err);
    }
}

// ---------- DECLARING -------

void insert(IdEntry entry){
    if(!insertSymbol(&stack, entry)){
        char *err;
        asprintf(&err, "VARIABLE %s ALREADY DECLARED\n", retrieveFromStringTable(*(stack.strTab), entry.strtabIndex));
        errorMessage(err);
    }
}

void declareVariable(StrtabIndexList indentifiers, Type type){
    //printf("declareVariable\n");
    for(int i = indentifiers.numberOfIndices-1 ; i >= 0 ; i--){
        VariableData *data = safeMalloc(sizeof(VariableData *));
        data->type = type;

        IdEntry newEntry = makeIdEntry(indentifiers.indices[i]);
        newEntry.data = data;
        newEntry.idType = TYPE_VARIABLE;

        insert(newEntry);
    }
    //printSymbolStack(&stack);
}

void declareParametersLocallyAsVariables(ParameterList list){
    //printf("declareParametersLocallyAsVariables : %d\n", list.numberOfParameters);
    for(int i = 0 ; i < list.numberOfParameters ; i++){
        VariableData *data = safeMalloc(sizeof(VariableData *));
        data->type = list.parameters[i].type;

        IdEntry newEntry = makeIdEntry(list.parameters[i].strtabIndex);
        newEntry.data = data;
        newEntry.idType = TYPE_VARIABLE;
        insert(newEntry);
    }
    //printSymbolStack(&stack);
}

void declareFunctionLocallyAsVariable(StrtabIndexList indentifiers, Type type){
    //printf("declareFunctionLocallyAsVariable\n");
    VariableData *data = safeMalloc(sizeof(VariableData *));
    data->type = type;

    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
    newEntry.idType = TYPE_VARIABLE;
    insert(newEntry);

    //printSymbolStack(&stack);
}

void declareFunction(StrtabIndexList indentifiers, Type type, ParameterList parameters){
    //printf("declareFunction : %d\n", parameters.numberOfParameters);
    //printf("Declaring function");
    FunctionData *data = safeMalloc(sizeof(FunctionData *));
    data->returnType = type;
    data->parameters = &parameters;

    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
    newEntry.idType = TYPE_FUNCTION;
    insert(newEntry);
}

void declareProcedure(StrtabIndexList indentifiers, ParameterList parameters){
    //printf("declareProcedure : %d\n", parameters.numberOfParameters);
    FunctionData *data = safeMalloc(sizeof(ProcedureData *));
    data->parameters = &parameters;

    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
    newEntry.idType = TYPE_PROCEDURE;
    insert(newEntry);
    //printSymbolStack(&stack);
}

ParameterList createParameterList(StrtabIndexList list, Type t){
    ParameterList newList; // = safeMalloc(sizeof(ParameterList));
    newList.numberOfParameters = list.numberOfIndices;
    newList.parameters = safeMalloc(list.numberOfIndices * sizeof(ParameterData));

    for(int i =0 ; i < list.numberOfIndices; i++){
        ParameterData data; // = safeMalloc(sizeof(ParameterData));
        data.strtabIndex = list.indices[i];
        data.type = t;

        newList.parameters[i] = data;
    }
    return newList;
}

ParameterList combineParameterLists(ParameterList listOne, ParameterList listTwo){
    ParameterList newList;
    newList.numberOfParameters = listOne.numberOfParameters + listTwo.numberOfParameters;
    newList.parameters = safeMalloc(newList.numberOfParameters * sizeof(ParameterData));
    int i;
    int j;
    for(i =0 ; i < listOne.numberOfParameters; i++){
        newList.parameters[i] = listOne.parameters[i];
    }
    for(j =0 ; j < listTwo.numberOfParameters; j++){
        newList.parameters[j+i] = listTwo.parameters[j];
    }
    return newList;
}

StrtabIndexList combineIdentifiers(StrtabIndexList listOne, StrtabIndexList listTwo){
    StrtabIndexList newList;
    newList.numberOfIndices = listOne.numberOfIndices + listTwo.numberOfIndices;
    newList.indices = safeMalloc(newList.numberOfIndices * sizeof(unsigned));
    int i;
    int j;
    for(i =0 ; i < listOne.numberOfIndices; i++){
        newList.indices[i] = listOne.indices[i];
    }
    for(j =0 ; j < listTwo.numberOfIndices; j++){
        newList.indices[j+i] = listTwo.indices[j];
    }
    return newList;
}


// ------------- ERRORS -----------------------
int yyerror(char *errmsg) {
    char *err = "PARSE ERROR";
    errorMessage(err);
    return 1;
}

void errorMessage(char *msg){
    fprintf(stderr, "(%d) %s\n", lineno, msg);
    // Yes, a parse error is a successful (meaningful) result
    freeStringTable(strTab);
    exit(EXIT_SUCCESS);
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
