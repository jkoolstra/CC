
#ifndef _PARSER_Y_H
#define _PARSER_Y_H
#include <stdio.h>
#include "AST.h"
#include "StringTable.h"

#define YYSTYPE ASTNode*

#ifdef _PARSER_C
 int yylex(void);
 int yyerror(char*);

 static void cleanup(void);

 StringTable strTab;
 AST ast = NULL;
#else
 extern StringTable strTab;
 extern AST ast;
#endif // #ifdef _PARSER_C

#endif // #ifndef _PARSER_Y_H
