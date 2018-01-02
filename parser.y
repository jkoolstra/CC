
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "StringTable.h"
    #include "AST.h"

    int yylex(void);
    int yyerror(char*);
    extern int lineno;

    void cleanup(void);

    StringTable strTab;

    #define YYSTYPE ASTNode*
%}

%token TOK_INVALID
%token TOK_NEWLINE
%token TOK_DO TOK_FUNCTION TOK_PROGRAM TOK_PROCEDURE TOK_VAR TOK_INTEGER TOK_REAL
  TOK_ARRAY TOK_OF TOK_IF TOK_THEN TOK_ELSE TOK_WHILE TOK_BEGIN TOK_END
%token TOK_ID TOK_NUM TOK_ASSIGNOP TOK_RELOP TOK_ADDOP TOK_MULOP

%%

program :
        TOK_PROGRAM TOK_ID '(' identifier_list ')' ';'
        declarations
        subprogram_declarations
        compound_statement
        '.'
;

identifier_list :
        TOK_ID
    |
        identifier_list ',' TOK_ID
; 
        
declarations :
        declarations TOK_VAR identifier_list ':' type ';'
    |
        /* empty */
;

type :
        standard_type
    |
        TOK_ARRAY '[' TOK_NUM '.' '.' TOK_NUM ']' TOK_OF standard_type
;

standard_type :
        TOK_INTEGER
    |
        TOK_REAL
;

subprogram_declarations :
        subprogram_declarations subprogram_declaration ';'
    |
        /* empty */
;

subprogram_declaration :
        subprogram_head declarations compound_statement
;

subprogram_head :
        TOK_FUNCTION TOK_ID arguments ':' standard_type ';'
    |
        TOK_PROCEDURE TOK_ID arguments ';'
;

arguments :
        '(' parameter_list ')'
    |
        /* empty */
;

parameter_list :
        identifier_list ':' type
    |
        parameter_list ';' identifier_list ':' type
;

compound_statement :
        TOK_BEGIN optional_statements TOK_END
;

optional_statements :
        statement_list
    |
        /* empty */
;

statement_list :
        statement
    |
        statement_list ';' statement
;

statement :
        variable TOK_ASSIGNOP expression
    |
        procedure_statement
    |
        compound_statement
    |
        TOK_IF expression TOK_THEN statement TOK_ELSE statement
    |
        TOK_WHILE expression TOK_DO statement
;

variable :
        TOK_ID
    |
        TOK_ID '[' expression ']'
;

procedure_statement :
        TOK_ID
    |
        TOK_ID '(' expression_list ')'
;

expression_list :
        expression
    |
        expression_list ',' expression
;

expression :
        simple_expression
    |
        simple_expression TOK_RELOP simple_expression
;

simple_expression :
        term
    |
        sign term
    |
        simple_expression TOK_ADDOP term
;

term :
        factor
    |
        term TOK_MULOP factor
;

factor :
        simple_factor
    |
        sign simple_factor
;

simple_factor :
        TOK_ID
    |
        TOK_ID '(' expression_list ')'
    |
        TOK_ID '[' expression ']'
    |
        TOK_NUM { $$ = yylval; }
    |
        '(' expression ')'
;

sign :
        TOK_ADDOP
;

%%

int yyerror(char *errmsg) {
    fprintf(stderr, "PARSE ERROR (%d)\n", lineno);
    // Yes, a parse error is a successful (meaningful) result
    cleanup();
    exit(EXIT_SUCCESS);
}

int main(void) {
    //yydebug = 1;
    strTab = newStringTable(0);
    yyparse();
    printf("ACCEPTED\n");
    cleanup();
    return 0;
}

void cleanup(void) {
    freeStringTable(strTab);
}















