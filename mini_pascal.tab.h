/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     FUNCTION = 259,
     PROCEDURE = 260,
     BEG = 261,
     END = 262,
     IF = 263,
     THEN = 264,
     ELSE = 265,
     WHILE = 266,
     DO = 267,
     VAR = 268,
     ARRAY = 269,
     OF = 270,
     ARRSEP = 271,
     INTEGER = 272,
     REAL = 273,
     ASSIGNOP = 274,
     RELOP_GR = 275,
     RELOP_GREQ = 276,
     RELOP_SM = 277,
     RELOP_SMEQ = 278,
     RELOP_NOEQ = 279,
     RELOP_EQ = 280,
     ADDOP_MIN = 281,
     ADDOP_ADD = 282,
     I_MULOP_M = 283,
     I_MULOP_D = 284,
     R_MULOP_M = 285,
     R_MULOP_D = 286,
     INUM = 287,
     RNUM = 288,
     ID = 289,
     READLN = 290,
     WRITELN = 291
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define FUNCTION 259
#define PROCEDURE 260
#define BEG 261
#define END 262
#define IF 263
#define THEN 264
#define ELSE 265
#define WHILE 266
#define DO 267
#define VAR 268
#define ARRAY 269
#define OF 270
#define ARRSEP 271
#define INTEGER 272
#define REAL 273
#define ASSIGNOP 274
#define RELOP_GR 275
#define RELOP_GREQ 276
#define RELOP_SM 277
#define RELOP_SMEQ 278
#define RELOP_NOEQ 279
#define RELOP_EQ 280
#define ADDOP_MIN 281
#define ADDOP_ADD 282
#define I_MULOP_M 283
#define I_MULOP_D 284
#define R_MULOP_M 285
#define R_MULOP_D 286
#define INUM 287
#define RNUM 288
#define ID 289
#define READLN 290
#define WRITELN 291




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 41 "mini_pascal.y"
{
	int iValue;
	float rValue;
	ASTNode *node;
	NodeList nodeList;

    StrtabIndexList indexList;
    ParameterList parameterList;
    Type type;
    TypeList typeList;
}
/* Line 1529 of yacc.c.  */
#line 133 "mini_pascal.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

