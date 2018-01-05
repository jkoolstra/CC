
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
    void declareIdentifiers(StrtabIndexList, Type, IdType);
    Type makeEmptyType();

    SymbolStack stack;
%}

%union{
    StrtabIndexList indexList;
    Type type;
}

%token PROGRAM FUNCTION PROCEDURE BEG END IF THEN ELSE WHILE DO
%token VAR ARRAY OF ARRSEP INTEGER REAL
%token ASSIGNOP RELOP ADDOP MULOP INUM RNUM ID

%type <indexList> Identifier_list
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
            '.' { printf("DECLARING PROGRAM\n"); declareIdentifiers($2, makeEmptyType(), TYPE_PROGRAM); }

Identifier_list : ID { $$ = $1; }
                | Identifier_list ',' ID { $$ = combineIdentifiers($1, $3);}

Declarations    : Declarations VAR Identifier_list ':' Type ';' { declareIdentifiers($3, $5, TYPE_VARIABLE); }
                | /* Empty */


Type            : Standard_type { $$ = $1;  $$.valueType.base = TYPE_SINGLE; }
                | ARRAY '[' INUM '.''.' INUM ']' OF Standard_type { $$ = $9; $$.valueType.base = TYPE_ARRAY;  }

Standard_type   : INTEGER { $$.valueType.secondary = TYPE_INTEGER ; }
                | REAL { $$.valueType.secondary = TYPE_REAL ; }

Subprogram_declarations : Subprogram_declarations Subprogram_declaration ';'
                        | /* Empty */

Subprogram_declaration  : Subprogram_head {indent(&stack);}
                            Declarations 
                            Compound_statement { outdent(&stack);}

Subprogram_head : FUNCTION 
                    ID 
                    Arguments ':' Standard_type ';' { $5.valueType.base = TYPE_SINGLE; declareIdentifiers($2, $5, TYPE_FUNCTION);}
                | PROCEDURE 
                    ID 
                    Arguments ';' { declareIdentifiers($2, makeEmptyType(), TYPE_PROCEDURE);}

Arguments       : '(' Parameter_list ')' 
                | /* Empty */

Parameter_list  : Identifier_list ':' Type { declareIdentifiers($1, $3, TYPE_PARAMETER); }
                | Parameter_list ';' Identifier_list ':' Type { declareIdentifiers($3, $5, TYPE_PARAMETER); }

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

void declareIdentifiers(StrtabIndexList indentifiers, Type type, IdType idType){
    for(int i = indentifiers.numberOfIndices-1 ; i >= 0 ; i--){
        IdEntry newEntry = makeIdEntry(indentifiers.indices[i]);
        newEntry.type = type;
        newEntry.type.idType = idType;
        insertSymbol(&stack, newEntry);
    }
}

Type makeEmptyType(){
    Type t;
    t.idType = NO_ID_TYPE;
    ValueType vt;
    vt.base = NO_BASE_TYPE;
    vt.secondary = NO_SECONDARY_TYPE;
    t.valueType = vt;

    return t;
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















