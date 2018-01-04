
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "lex.yy.c"
    #include "StringTable.h"
    #include "SymbolStack.h"

    int yyerror(char *errmsg);
    SymbolStack stack;
%}

%union{
    unsigned strtabindex;
}

%token PROGRAM FUNCTION PROCEDURE BEG END IF THEN ELSE WHILE DO
%token VAR ARRAY OF ARRSEP INTEGER REAL
%token ASSIGNOP RELOP ADDOP MULOP ID INUM RNUM

%start Program

%%  /****** grammar rules section ********/

Program         : PROGRAM 
                    ID {insertSymbol(&stack ,yylval.strtabindex, makeIdEntry(yylval.strtabindex, TYPE_PROGRAM));}
                    '(' Identifier_list ')' ';' 
                    Declarations
                    Subprogram_declarations
                    Compound_statement
                    '.' 

Identifier_list : ID {insertSymbol(&stack ,yylval.strtabindex, makeIdEntry(yylval.strtabindex, TYPE_VARIABLE));}
                | Identifier_list ',' ID {insertSymbol(&stack ,yylval.strtabindex, makeIdEntry(yylval.strtabindex, TYPE_VARIABLE));}

Declarations    : Declarations VAR Identifier_list ':' Type ';'
                | /* Empty */


Type            : Standard_type
                | ARRAY '[' INUM ARRSEP INUM ']' OF Standard_type

Standard_type   : INTEGER
                | REAL

Subprogram_declarations : Subprogram_declarations Subprogram_declaration ';'
                        | /* Empty */

Subprogram_declaration  : Subprogram_head {indent(&stack);}
                            Declarations 
                            Compound_statement { outdent(&stack);}

Subprogram_head : FUNCTION 
                    ID {insertSymbol(&stack ,yylval.strtabindex, makeIdEntry(yylval.strtabindex, TYPE_FUNCTION));}
                    Arguments ':' Standard_type ';'
                | PROCEDURE 
                    ID {insertSymbol(&stack ,yylval.strtabindex, makeIdEntry(yylval.strtabindex, TYPE_PROCEDURE));}
                    Arguments ';'

Arguments       : '(' Parameter_list ')'
                | /* Empty */

Parameter_list  : Identifier_list ':' Type
                | Parameter_list ';' Identifier_list ':' Type

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















