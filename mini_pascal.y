
%{
    #include "IdEntry.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include "lex.yy.c"
    #include "StringTable.h"
    #include "SymbolStack.h"
    #include "common.h"

    int yyerror(char *errmsg);
    StrtabIndexList combineIdentifiers(StrtabIndexList, StrtabIndexList);
    ParameterList createParameterList(StrtabIndexList list, Type t);
    ParameterList combineParameterLists(ParameterList listOne, ParameterList listTwo);

    void declareFunctionLocally(StrtabIndexList, Type type);
    void declareParametersLocally(ParameterList);

    void declareVariable(StrtabIndexList indentifiers, Type type);
    void declareFunction(StrtabIndexList indentifiers, Type type, ParameterList parameters);
    void declareProcedure(StrtabIndexList indentifiers, ParameterList parameters);
    //void declareIdentifiers(StrtabIndexList, Type, IdType);
    Type makeEmptyType();

    SymbolStack stack;
%}

%union{
    StrtabIndexList indexList;
    ParameterList parameterList;
    Type type;
}

%token PROGRAM FUNCTION PROCEDURE BEG END IF THEN ELSE WHILE DO
%token VAR ARRAY OF ARRSEP INTEGER REAL
%token ASSIGNOP RELOP ADDOP MULOP INUM RNUM ID

%type <indexList> Identifier_list 
%type <parameterList> Parameter_list Arguments
%type <type> Standard_type Type

%type <indexList> ID


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
                                    $$.base = TYPE_SINGLE; 
                                }
                | ARRAY '[' INUM '.''.' INUM ']' OF Standard_type   { 
                                                                        $$ = $9; 
                                                                        $$.base = TYPE_ARRAY;  
                                                                    }

Standard_type   : INTEGER   { 
                                $$.secondary = TYPE_INTEGER ; 
                            }
                | REAL      { 
                                $$.secondary = TYPE_REAL ; 
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
                                                            declareFunctionLocally($2, $5);
                                                            declareParametersLocally($3);
                                                        }
                | PROCEDURE 
                    ID 
                    Arguments ';'   { 
                                        declareProcedure($2, $3);
                                        indent(&stack);
                                        declareParametersLocally($3);
                                    }

Arguments       : '(' Parameter_list ')'    {
                                                $$ = $2;
                                            }
                | /* Empty */

Parameter_list  : Identifier_list ':' Type  {   
                                                $$ = createParameterList($1, $3);
                                                //declareParameters($1, $3); 
                                            }
                | Parameter_list ';' Identifier_list ':' Type   { 
                                                                    ParameterList secondList = createParameterList($3, $5);
                                                                    $$ = combineParameterLists($1, secondList);
                                                                    //declareParameters($3, $5); 
                                                                }

Compound_statement  : BEG
                      Optional_statements
                      END

Optional_statements : Statement_list
                    | /* Empty */

Statement_list  : Statement
                | Statement_list ';' Statement

Statement       : Variable ASSIGNOP Expression
                | Procedure_statement
                | Compound_statement
                | IF Expression THEN Statement ELSE Statement
                | WHILE Expression DO Statement

Variable        : ID 
                | ID '[' Expression_list ']'

Procedure_statement : ID
                    | ID '(' Expression_list ')'

Expression_list : Expression
                | Expression_list ',' Expression

Expression      : Simple_expression
                | Simple_expression RELOP Simple_expression

Simple_expression   : Term
                    | ADDOP Term
                    | Simple_expression ADDOP Term

Term            : Factor
                | Term MULOP Factor

Factor          : ID
                | ID '(' Expression_list ')'
                | INUM
                | RNUM
                | '(' Expression ')'
                | ID '[' Simple_expression ']'

%%

void declareVariable(StrtabIndexList indentifiers, Type type){
    for(int i = indentifiers.numberOfIndices-1 ; i >= 0 ; i--){
        VariableData *data = safeMalloc(sizeof(VariableData *));
        data->type = type;

        IdEntry newEntry = makeIdEntry(indentifiers.indices[i]);
        newEntry.data = data;
        newEntry.idType = TYPE_VARIABLE;
        insertSymbol(&stack, newEntry);
    }
    //printSymbolStack(&stack);
}

void declareParametersLocally(ParameterList list){
    for(int i = 0 ; i < list.numberOfParameters ; i++){
        VariableData data;
        data.type = list.parameters[i].type; 

        IdEntry newEntry = makeIdEntry(list.parameters[i].strtabIndex);
        newEntry.data = &data;
        newEntry.idType = TYPE_VARIABLE;
        insertSymbol(&stack, newEntry);
    }
    printSymbolStack(&stack);
}

void declareFunctionLocally(StrtabIndexList indentifiers, Type type){
    VariableData data;
    data.type = type; 
        
    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = &data;
    newEntry.idType = TYPE_VARIABLE;
    insertSymbol(&stack, newEntry);

    printSymbolStack(&stack);
}

void declareFunction(StrtabIndexList indentifiers, Type type, ParameterList parameters){
    //printf("Declaring function");
    FunctionData *data = safeMalloc(sizeof(FunctionData *));
    data->returnType = type;
    data->parameters = &parameters;

    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
    newEntry.idType = TYPE_FUNCTION;
    insertSymbol(&stack, newEntry);
    //printSymbolStack(&stack);
}

void declareProcedure(StrtabIndexList indentifiers, ParameterList parameters){
    FunctionData *data = safeMalloc(sizeof(ProcedureData *));
    data->parameters = &parameters;

    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
    newEntry.idType = TYPE_FUNCTION;
    insertSymbol(&stack, newEntry);
    //printSymbolStack(&stack);
}

/*void declareIdentifiers(StrtabIndexList indentifiers, Type type, IdType idType){
    for(int i = indentifiers.numberOfIndices-1 ; i >= 0 ; i--){
        IdEntry newEntry = makeIdEntry(indentifiers.indices[i]);
        newEntry.type = type;
        newEntry.type.idType = idType;
        insertSymbol(&stack, newEntry);
    }
}*/

ParameterList createParameterList(StrtabIndexList list, Type t){
    ParameterList newList; // = safeMalloc(sizeof(ParameterList));
    newList.numberOfParameters = 1;
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

int yyerror(char *errmsg) {
    fprintf(stderr, "PARSE ERROR (%d)\n", lineno);
    // Yes, a parse error is a successful (meaningful) result
    freeStringTable(strTab);
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    //yydebug = 1;
    strTab = newStringTable(0);
    stack = initSymbolStack(&strTab);
    yyparse();
    printf("ACCEPTED\n");
    //printStringTable(strTab);
    printSymbolStack(&stack);
    freeStringTable(strTab);
    return 0;
}















