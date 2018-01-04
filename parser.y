
%{
    #define _PARSER_C
    #include "parser.y.h"
    #include "parser.l.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include "StringTable.h"
    #include "AST.h"
%}

%token TOK_INVALID
%token TOK_NEWLINE
%token TOK_DO TOK_FUNCTION TOK_PROGRAM TOK_PROCEDURE TOK_VAR TOK_INTEGER TOK_REAL
  TOK_ARRAY TOK_OF TOK_IF TOK_THEN TOK_ELSE TOK_WHILE TOK_BEGIN TOK_END
%token TOK_ID TOK_NUM TOK_ASSIGNOP TOK_RELOP TOK_ADDOP TOK_MULOP

%%

parser_start:
    program
    { ast = $1;
    }
;

program :
        TOK_PROGRAM id '(' identifier_list ')' ';'
        declarations
        subprogram_declarations
        compound_statement
        '.'
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_PROGRAM),
              NO_SEMANTIC_VALUE, 5, $2, $4, $7, $8, $9);
        }
;

identifier_list :
        id
    |
        identifier_list ',' id
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_ID_LIST),
              NO_SEMANTIC_VALUE, 2, $1, $3);
        }
; 
        
declarations :
        declarations TOK_VAR identifier_list ':' type ';'
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_DECL_LIST),
              NO_SEMANTIC_VALUE, 3, $1, $3, $5);
        }
    |
        /* empty */ { $$ = NULL; }
;

type :
        standard_type
    |
        TOK_ARRAY '[' num '.' '.' num ']' TOK_OF standard_type
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_DECL_ARRAY_TYPE),
              NO_SEMANTIC_VALUE, 3, $3, $6, $9);
        }
;

standard_type :
        TOK_INTEGER
        {   $$ = buildASTNode(TOKEN_NODE, token(TOK_INTEGER),
              NO_SEMANTIC_VALUE, 0);
        }
    |
        TOK_REAL
        {   $$ = buildASTNode(TOKEN_NODE, token(TOK_REAL),
              NO_SEMANTIC_VALUE, 0);
        }
;

subprogram_declarations :
        subprogram_declarations subprogram_declaration ';'
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_SUBPROGRAM_LIST),
              NO_SEMANTIC_VALUE, 2, $1, $2);
        }
    |
        /* empty */ { $$ = NULL; }
;

subprogram_declaration :
        subprogram_head declarations compound_statement
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_SUBPROGRAM),
              NO_SEMANTIC_VALUE, 3, $1, $2, $3);
        }
;

subprogram_head :
        TOK_FUNCTION id arguments ':' standard_type ';'
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_FUNCTION),
              NO_SEMANTIC_VALUE, 3, $2, $3, $5);
        }
    |
        TOK_PROCEDURE id arguments ';'
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_FUNCTION),
              NO_SEMANTIC_VALUE, 2, $2, $3);
        }
;

arguments :
        '(' parameter_list ')' { $$ = $2; }
    |
        /* empty */ { $$ = NULL; }
;

parameter_list :
        identifier_list ':' type
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_PARAMETER_LIST),
              NO_SEMANTIC_VALUE, 2, $1, $3);
        }
    |
        parameter_list ';' identifier_list ':' type
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_PARAMETER_LIST),
              NO_SEMANTIC_VALUE, 3, $1, $3, $5);
        }
;

compound_statement :
        TOK_BEGIN optional_statements TOK_END { $$ = $2; }
;

optional_statements :
        statement_list
    |
        /* empty */ { $$ = NULL; }
;

statement_list :
        statement
    |
        statement_list ';' statement
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_STATEMENT_LIST),
              NO_SEMANTIC_VALUE, 2, $1, $3);
        }
;

statement :
        variable assign expression
        {   $2->child[0] = $1;
            $2->child[1] = $3;
            $$ = $2;
        }
    |
        procedure_statement
    |
        compound_statement
    |
        TOK_IF expression TOK_THEN statement TOK_ELSE statement
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_IF),
              NO_SEMANTIC_VALUE, 3, $2, $4, $6);
        }
    |
        TOK_WHILE expression TOK_DO statement
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_WHILE),
              NO_SEMANTIC_VALUE, 2, $2, $4);
        }
;

variable :
        id
    |
        id '[' expression ']'
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_INLINE_ARRAY_ELEMENT),
              NO_SEMANTIC_VALUE, 2, $1, $3);
        }
;

procedure_statement :
        id
    |
        id '(' expression_list ')'
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_FUNCTION_CALL),
              NO_SEMANTIC_VALUE, 2, $1, $3);
        }
;

expression_list :
        expression
    |
        expression_list ',' expression
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_EXPRESSION_LIST),
              NO_SEMANTIC_VALUE, 2, $1, $3);
        }
;

expression :
        simple_expression
    |
        simple_expression rel simple_expression
        {   $2->child[0] = $1;
            $2->child[1] = $3;
            $$ = $2;
        }
;

simple_expression :
        term
    |
        sign term
        {   $1->child[0] = $2;
            $$ = $1;
        }
    |
        simple_expression add term
        {   $2->child[0] = $1;
            $2->child[1] = $3;
            $$ = $2;
        }
;

term :
        factor
    |
        term mul factor
        {   $2->child[0] = $1;
            $2->child[1] = $3;
            $$ = $2;
        }
;

factor :
        simple_factor
    |
        sign simple_factor
        {   $1->child[0] = $2;
            $$ = $1;
        }
;

simple_factor :
        id
    |
        id '(' expression_list ')'
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_INLINE_FUNCTION_CALL),
              NO_SEMANTIC_VALUE, 2, $1, $3);
        }
    |
        id '[' expression ']'
        {   $$ = buildASTNode(SYNTAX_NODE, syntax(SYNTAX_INLINE_ARRAY_ELEMENT),
              NO_SEMANTIC_VALUE, 2, $1, $3);
        }
    |
        num
    |
        '(' expression ')' { $$ = $2; }
;

id :
        TOK_ID { $$ = yylval; }
;

num :
        TOK_NUM { $$ = yylval; }
;

rel :
        TOK_RELOP { $$ = yylval; }
;

assign :
        TOK_ASSIGNOP { $$ = yylval; }
;

mul :
        TOK_MULOP { $$ = yylval; }
;

add :
        TOK_ADDOP
        {   yylval->nChildren = 2; // used as binary operator
            $$ = yylval;
        }
;

sign :
        TOK_ADDOP
        {   yylval->nChildren = 1; // used as unary operator
            $$ = yylval;
        }
;

%%

int yyerror(char *errmsg) {
    fprintf(stderr, "PARSE ERROR (%d)\n", lineno);
    // Yes, a parse error is a successful (meaningful) result
    cleanup();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    //yydebug = 1;
    ++argv, --argc; // skip over the program name
    if (argc == 1) {
        FILE *f = fopen(argv[0], "r");
        if (f == NULL) {
            fprintf(stderr, "Fatal error: fopen() failed on %s\n", argv[1]);
        }
        yyin = f;
    } else if (argc > 1) {
        printf("Usage: parser FILE, or parser < FILE\n");
        exit(EXIT_FAILURE);
    }
    strTab = newStringTable(0);
    yyparse();
    printf("ACCEPTED\n");
    cleanup();
    return 0;
}

static void cleanup(void) {
    freeStringTable(strTab);
    freeAST(ast);
}















