
#ifndef _PARSER_L_H
#define _PARSER_L_H
#include <stdio.h>

#ifdef _PARSER_L
 // Mark the line number of yyin
 int lineno = 1;
#else
 extern FILE* yyin;
 extern int lineno;
#endif // #ifdef _PARSER_L

#endif // #ifndef _PARSER_L_H
