/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 2 "mini_pascal.y"

	//#include "tokens.h"
	#include "IRGenerator.h"
    #include "IdEntry.h"
	#include "AST.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include "lex.yy.c"
    #include "StringTable.h"
    #include "SymbolStack.h"
    #include "common.h"

    // CHECKING
	void checkCondition(ASTNode*);
	void checkAssignment(ASTNode*, ASTNode*);
    void checkIfIdentifierIsDeclared(unsigned);
    void checkIdentifierIdType(unsigned, IdType);
    void checkIdentifierSecondaryType(unsigned, SecondaryType);
	void checkIfArrayIndexIsInteger(ASTNode*);
	void checkIfMultipleArrayIndicesAreAllIntegers(NodeList);			//TODO: ADD this functionality back
	void checkParameterCountAndTypes(unsigned id, NodeList list, IdType type);
    void checkTypes(ASTNode*, ASTNode*, Operator);

	// DECLARING
    void declareFunctionLocallyAsVariable(unsigned, Type type);
    void declareParametersLocallyAsVariables(ParameterList);
    void declareVariable(StrtabIndexList, Type);
    void declareFunction(unsigned, Type, ParameterList);
    void declareProcedure(unsigned, ParameterList);

	// ERROR HANDLING
    int yyerror(char *errmsg);
    void errorMessage(char *msg);
    void warningMessage(char *msg);

    SymbolStack stack;
	ASTNode *programNode;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 41 "mini_pascal.y"
{
	int iValue;
	float rValue;
	ASTNode *node;
	NodeList nodeList;

	unsigned index;
    StrtabIndexList indexList;
    ParameterList parameterList;
    Type type;
    TypeList typeList;
}
/* Line 193 of yacc.c.  */
#line 220 "mini_pascal.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 233 "mini_pascal.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   144

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNRULES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    38,     2,     2,    41,     2,    40,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,    39,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    44,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,    14,    16,    20,    27,    28,    30,    40,
      42,    44,    48,    49,    53,    60,    65,    69,    70,    74,
      80,    84,    86,    87,    89,    93,    97,    99,   101,   108,
     113,   118,   123,   125,   130,   132,   137,   139,   143,   145,
     149,   153,   157,   161,   165,   169,   171,   174,   177,   181,
     185,   187,   191,   195,   199,   203,   205,   210,   212,   214,
     218,   220,   224,   226
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,     3,    34,    37,    47,    38,    39,    48,
      51,    56,    40,    -1,    34,    -1,    47,    41,    34,    -1,
      48,    13,    47,    42,    49,    39,    -1,    -1,    50,    -1,
      14,    43,    32,    40,    40,    32,    44,    15,    50,    -1,
      17,    -1,    18,    -1,    51,    52,    39,    -1,    -1,    53,
      48,    56,    -1,     4,    34,    54,    42,    50,    39,    -1,
       5,    34,    54,    39,    -1,    37,    55,    38,    -1,    -1,
      47,    42,    49,    -1,    55,    39,    47,    42,    49,    -1,
       6,    57,     7,    -1,    58,    -1,    -1,    59,    -1,    58,
      39,    59,    -1,    60,    19,    63,    -1,    61,    -1,    56,
      -1,     8,    63,     9,    59,    10,    59,    -1,    11,    63,
      12,    59,    -1,    35,    37,    67,    38,    -1,    36,    37,
      62,    38,    -1,    34,    -1,    34,    43,    62,    44,    -1,
      34,    -1,    34,    37,    62,    38,    -1,    63,    -1,    62,
      41,    63,    -1,    64,    -1,    64,    20,    64,    -1,    64,
      21,    64,    -1,    64,    22,    64,    -1,    64,    23,    64,
      -1,    64,    24,    64,    -1,    64,    25,    64,    -1,    65,
      -1,    26,    65,    -1,    27,    65,    -1,    64,    26,    65,
      -1,    64,    27,    65,    -1,    66,    -1,    65,    31,    66,
      -1,    65,    30,    66,    -1,    65,    29,    66,    -1,    65,
      28,    66,    -1,    68,    -1,    34,    37,    62,    38,    -1,
      32,    -1,    33,    -1,    37,    63,    38,    -1,    68,    -1,
      67,    41,    68,    -1,    34,    -1,    34,    43,    64,    44,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    81,    81,    91,    94,    98,   109,   114,   117,   121,
     124,   128,   129,   131,   137,   145,   153,   156,   162,   165,
     172,   176,   177,   179,   183,   188,   192,   195,   198,   202,
     206,   209,   213,   221,   231,   236,   243,   247,   252,   255,
     259,   263,   267,   271,   275,   280,   283,   287,   291,   295,
     300,   303,   307,   311,   315,   320,   321,   329,   332,   335,
     339,   343,   348,   355
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "FUNCTION", "PROCEDURE",
  "BEG", "END", "IF", "THEN", "ELSE", "WHILE", "DO", "VAR", "ARRAY", "OF",
  "ARRSEP", "INTEGER", "REAL", "ASSIGNOP", "RELOP_GR", "RELOP_GREQ",
  "RELOP_SM", "RELOP_SMEQ", "RELOP_NOEQ", "RELOP_EQ", "ADDOP_MIN",
  "ADDOP_ADD", "I_MULOP_M", "I_MULOP_D", "R_MULOP_M", "R_MULOP_D", "INUM",
  "RNUM", "ID", "READLN", "WRITELN", "'('", "')'", "';'", "'.'", "','",
  "':'", "'['", "']'", "$accept", "Program", "Identifier_list",
  "Declarations", "Type", "Standard_type", "Subprogram_declarations",
  "Subprogram_declaration", "Subprogram_head", "Arguments",
  "Parameter_list", "Compound_statement", "Optional_statements",
  "Statement_list", "Statement", "Variable", "Procedure_statement",
  "Expression_list", "Expression", "Simple_expression", "Term", "Factor",
  "Variable_factor_list", "Variable_factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    40,    41,    59,
      46,    44,    58,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    53,    53,    54,    54,    55,    55,
      56,    57,    57,    58,    58,    59,    59,    59,    59,    59,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      63,    63,    63,    63,    63,    64,    64,    64,    64,    64,
      65,    65,    65,    65,    65,    66,    66,    66,    66,    66,
      67,    67,    68,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,    10,     1,     3,     6,     0,     1,     9,     1,
       1,     3,     0,     3,     6,     4,     3,     0,     3,     5,
       3,     1,     0,     1,     3,     3,     1,     1,     6,     4,
       4,     4,     1,     4,     1,     4,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     1,     2,     2,     3,     3,
       1,     3,     3,     3,     3,     1,     4,     1,     1,     3,
       1,     3,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     3,     0,     0,     0,
       6,     4,    12,     0,     0,     0,     0,     0,    22,     0,
       6,     0,     0,    17,    17,     0,     0,    34,     0,     0,
      27,     0,    21,    23,     0,    26,    11,     0,     2,     0,
       9,    10,     0,     7,     0,     0,     0,     0,     0,    57,
      58,    62,     0,     0,    38,    45,    50,    55,     0,     0,
       0,     0,     0,    20,     0,     0,    13,     0,     5,     0,
       0,     0,    15,    46,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,    62,     0,    60,     0,    24,
      25,     0,     0,    16,     0,     0,     0,     0,    59,     0,
      39,    40,    41,    42,    43,    44,    48,    49,    54,    53,
      52,    51,    29,    35,     0,    33,    30,     0,    31,     0,
      18,     0,    14,    56,    63,     0,    37,    61,     0,     0,
      28,     0,    19,     0,     0,     8
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,    12,    42,    43,    14,    19,    20,    45,
      70,    30,    31,    32,    33,    34,    35,    92,    93,    54,
      55,    56,    96,    57
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -94
static const yytype_int8 yypact[] =
{
       9,    -9,    30,    -3,   -94,     7,   -94,    31,     4,    23,
     -94,   -94,    55,     7,   102,    32,    56,    83,     2,    46,
     -94,    78,     3,    82,    82,    21,    21,    -8,    84,    85,
     -94,    89,    81,   -94,   104,   -94,   -94,    10,   -94,    86,
     -94,   -94,    88,   -94,     7,    90,    91,    33,    33,   -94,
     -94,   -15,    21,   115,    57,    58,   -94,   -94,   113,    21,
      21,    92,    21,   -94,     2,    21,   -94,    96,   -94,    62,
      71,    94,   -94,    58,    58,    21,    21,    93,     2,    21,
      21,    21,    21,    21,    21,    33,    33,    33,    33,    33,
      33,     2,    53,   -94,    51,    95,    59,   -94,    60,   -94,
     -94,    97,     3,   -94,     7,   100,    64,   -12,   -94,   123,
      87,    87,    87,    87,    87,    87,    58,    58,   -94,   -94,
     -94,   -94,   -94,   -94,    21,   -94,   -94,    92,   -94,   101,
     -94,    74,   -94,   -94,   -94,     2,   -94,   -94,   103,     3,
     -94,    98,   -94,   119,    94,   -94
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -94,   -94,   -11,   116,   -93,   -68,   -94,   -94,   -94,   120,
     -94,     5,   -94,   -94,   -60,   -94,   -94,   -36,   -25,   -20,
     -41,   -38,   -94,   -56
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -33
static const yytype_int16 yytable[] =
{
      53,    58,    15,   105,    99,    97,    73,    74,    18,   130,
      25,   -32,     1,    26,    85,    86,    18,    39,   109,    21,
      40,    41,    75,    13,    94,     3,    98,    77,    76,    59,
       4,   122,   134,    69,     5,    60,    27,    28,    29,   106,
     100,     6,    66,    10,   116,   117,   142,    47,    48,   118,
     119,   120,   121,    49,    50,    51,   107,    11,    52,   110,
     111,   112,   113,   114,   115,    49,    50,    51,    13,     8,
      52,   137,     9,     9,    22,   140,   145,    79,    80,    81,
      82,    83,    84,    85,    86,    36,    87,    88,    89,    90,
      23,   123,   124,   131,   124,   125,    63,   126,   128,   136,
     127,   124,   133,     9,   102,   124,    16,    17,    18,   103,
     104,    40,    41,    85,    86,     9,   139,    24,    38,    44,
      64,    61,    62,    65,    78,    91,    95,    68,   101,    67,
      72,   108,    71,   135,   144,   141,    37,   129,    76,   132,
       0,   138,   143,     0,    46
};

static const yytype_int16 yycheck[] =
{
      25,    26,    13,    71,    64,    61,    47,    48,     6,   102,
       8,    19,     3,    11,    26,    27,     6,    14,    78,    14,
      17,    18,    37,    13,    60,    34,    62,    52,    43,    37,
       0,    91,    44,    44,    37,    43,    34,    35,    36,    75,
      65,    34,    37,    39,    85,    86,   139,    26,    27,    87,
      88,    89,    90,    32,    33,    34,    76,    34,    37,    79,
      80,    81,    82,    83,    84,    32,    33,    34,    13,    38,
      37,   127,    41,    41,    42,   135,   144,    20,    21,    22,
      23,    24,    25,    26,    27,    39,    28,    29,    30,    31,
      34,    38,    41,   104,    41,    44,     7,    38,    38,   124,
      41,    41,    38,    41,    42,    41,     4,     5,     6,    38,
      39,    17,    18,    26,    27,    41,    42,    34,    40,    37,
      39,    37,    37,    19,     9,    12,    34,    39,    32,    43,
      39,    38,    42,    10,    15,    32,    20,    40,    43,    39,
      -1,    40,    44,    -1,    24
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    46,    34,     0,    37,    34,    47,    38,    41,
      39,    34,    48,    13,    51,    47,     4,     5,     6,    52,
      53,    56,    42,    34,    34,     8,    11,    34,    35,    36,
      56,    57,    58,    59,    60,    61,    39,    48,    40,    14,
      17,    18,    49,    50,    37,    54,    54,    26,    27,    32,
      33,    34,    37,    63,    64,    65,    66,    68,    63,    37,
      43,    37,    37,     7,    39,    19,    56,    43,    39,    47,
      55,    42,    39,    65,    65,    37,    43,    63,     9,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    12,    62,    63,    62,    34,    67,    68,    62,    59,
      63,    32,    42,    38,    39,    50,    62,    64,    38,    59,
      64,    64,    64,    64,    64,    64,    65,    65,    66,    66,
      66,    66,    59,    38,    41,    44,    38,    41,    38,    40,
      49,    47,    39,    38,    44,    10,    63,    68,    40,    42,
      59,    32,    49,    44,    15,    50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 87 "mini_pascal.y"
    {
												programNode = createProgramNode((yyvsp[(2) - (10)].index), (yyvsp[(7) - (10)].nodeList), (yyvsp[(9) - (10)].node));
											;}
    break;

  case 3:
#line 91 "mini_pascal.y"
    {
												(yyval.indexList) = createStrtabIndexList((yyvsp[(1) - (1)].index));
											;}
    break;

  case 4:
#line 94 "mini_pascal.y"
    {
                                                (yyval.indexList) = combineIdentifiers((yyvsp[(1) - (3)].indexList), createStrtabIndexList((yyvsp[(3) - (3)].index)));
                                            ;}
    break;

  case 5:
#line 98 "mini_pascal.y"
    {
                                                                    declareVariable((yyvsp[(3) - (6)].indexList), (yyvsp[(5) - (6)].type));
																	NodeList combined = (yyvsp[(1) - (6)].nodeList);
																	for(int i = 0; i < (yyvsp[(3) - (6)].indexList).numberOfIndices ; i++){
																		ASTNode *declaration = createDeclarationNode((yyvsp[(3) - (6)].indexList).indices[i], (yyvsp[(5) - (6)].type));
																		NodeList declarations = createNodeList(declaration);
																		combined = combineNodeLists(combined, declarations);
																	}
																	(yyval.nodeList) = combined;
																	free((yyvsp[(3) - (6)].indexList).indices);
                                                                ;}
    break;

  case 6:
#line 109 "mini_pascal.y"
    {
																	(yyval.nodeList) = createEmptyNodeList();
																;}
    break;

  case 7:
#line 114 "mini_pascal.y"
    {
                                    (yyval.type) = makeType((yyvsp[(1) - (1)].type).base, TYPE_SCALAR, 0, 0);
                                ;}
    break;

  case 8:
#line 117 "mini_pascal.y"
    {
                                                                        (yyval.type) = makeType((yyvsp[(9) - (9)].type).base, TYPE_ARRAY, (yyvsp[(3) - (9)].iValue), (yyvsp[(6) - (9)].iValue));
                                                                    ;}
    break;

  case 9:
#line 121 "mini_pascal.y"
    {
                                (yyval.type).base = TYPE_INTEGER ;
                            ;}
    break;

  case 10:
#line 124 "mini_pascal.y"
    {
                                (yyval.type).base = TYPE_REAL ;
                            ;}
    break;

  case 13:
#line 133 "mini_pascal.y"
    {
                                                    outdent(&stack);
                                                ;}
    break;

  case 14:
#line 139 "mini_pascal.y"
    {
                                                            declareFunction((yyvsp[(2) - (6)].index), (yyvsp[(5) - (6)].type), (yyvsp[(3) - (6)].parameterList));
                                                            indent(&stack);
                                                            declareFunctionLocallyAsVariable((yyvsp[(2) - (6)].index), (yyvsp[(5) - (6)].type));
                                                            declareParametersLocallyAsVariables((yyvsp[(3) - (6)].parameterList));
                                                        ;}
    break;

  case 15:
#line 147 "mini_pascal.y"
    {
                                        declareProcedure((yyvsp[(2) - (4)].index), (yyvsp[(3) - (4)].parameterList));
                                        indent(&stack);
                                        declareParametersLocallyAsVariables((yyvsp[(3) - (4)].parameterList));
                                    ;}
    break;

  case 16:
#line 153 "mini_pascal.y"
    {
                                                (yyval.parameterList) = (yyvsp[(2) - (3)].parameterList);
                                            ;}
    break;

  case 17:
#line 156 "mini_pascal.y"
    {
                                                ParameterList list;
                                                list.numberOfParameters = 0;
                                                (yyval.parameterList) = list;
                                            ;}
    break;

  case 18:
#line 162 "mini_pascal.y"
    {
                                                (yyval.parameterList) = createParameterList((yyvsp[(1) - (3)].indexList), (yyvsp[(3) - (3)].type));
                                            ;}
    break;

  case 19:
#line 165 "mini_pascal.y"
    {
																	ParameterList l = createParameterList((yyvsp[(3) - (5)].indexList), (yyvsp[(5) - (5)].type));
																	(yyval.parameterList) = combineParameterLists((yyvsp[(1) - (5)].parameterList), l);
																;}
    break;

  case 20:
#line 174 "mini_pascal.y"
    { (yyval.node) = createCompoundStatementNode((yyvsp[(2) - (3)].nodeList));;}
    break;

  case 21:
#line 176 "mini_pascal.y"
    { (yyval.nodeList) = (yyvsp[(1) - (1)].nodeList);;}
    break;

  case 22:
#line 177 "mini_pascal.y"
    { (yyval.nodeList) = createEmptyNodeList();;}
    break;

  case 23:
#line 179 "mini_pascal.y"
    {
														NodeList list = createNodeList((yyvsp[(1) - (1)].node));
														(yyval.nodeList) = list;
													;}
    break;

  case 24:
#line 183 "mini_pascal.y"
    {
														NodeList list = combineNodeLists((yyvsp[(1) - (3)].nodeList), createNodeList((yyvsp[(3) - (3)].node)));
														(yyval.nodeList) = list;
													;}
    break;

  case 25:
#line 188 "mini_pascal.y"
    {
	 												checkAssignment((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
													(yyval.node) = createAssignmentNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
												;}
    break;

  case 26:
#line 192 "mini_pascal.y"
    {
																	(yyval.node) = (yyvsp[(1) - (1)].node);
																;}
    break;

  case 27:
#line 195 "mini_pascal.y"
    {
																	(yyval.node) = (yyvsp[(1) - (1)].node);
																;}
    break;

  case 28:
#line 198 "mini_pascal.y"
    {
																	checkCondition((yyvsp[(2) - (6)].node));
																	(yyval.node) = createIfElseNode((yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node), (yyvsp[(6) - (6)].node));
																;}
    break;

  case 29:
#line 202 "mini_pascal.y"
    {
																	checkCondition((yyvsp[(2) - (4)].node));
																	(yyval.node) = createWhileNode((yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
																;}
    break;

  case 30:
#line 206 "mini_pascal.y"
    {
																	(yyval.node) = createReadLnNode((yyvsp[(3) - (4)].nodeList));
																;}
    break;

  case 31:
#line 209 "mini_pascal.y"
    {
																	(yyval.node) = createWriteLnNode((yyvsp[(3) - (4)].nodeList));
																;}
    break;

  case 32:
#line 213 "mini_pascal.y"
    {
                                                  checkIfIdentifierIsDeclared((yyvsp[(1) - (1)].index));
                                                  checkIdentifierIdType((yyvsp[(1) - (1)].index), TYPE_VARIABLE);
												  checkIdentifierSecondaryType((yyvsp[(1) - (1)].index), TYPE_SCALAR);
												  IdEntry *entry = lookupSymbol(&stack,(yyvsp[(1) - (1)].index));
												  VariableData *data = (VariableData *)entry->data;
												  (yyval.node) = createVariableNode((yyvsp[(1) - (1)].index), data->type);
                                              ;}
    break;

  case 33:
#line 221 "mini_pascal.y"
    {
                                                  checkIfIdentifierIsDeclared((yyvsp[(1) - (4)].index));
                                                  checkIdentifierIdType((yyvsp[(1) - (4)].index), TYPE_VARIABLE);
                                                  checkIdentifierSecondaryType((yyvsp[(1) - (4)].index), TYPE_ARRAY);
												  checkIfMultipleArrayIndicesAreAllIntegers((yyvsp[(3) - (4)].nodeList));
												  IdEntry *entry = lookupSymbol(&stack,(yyvsp[(1) - (4)].index));
												  VariableData *data = (VariableData *)entry->data;
												  (yyval.node) = createArrayVariableNode((yyvsp[(1) - (4)].index), data->type, (yyvsp[(3) - (4)].nodeList));
                                              ;}
    break;

  case 34:
#line 231 "mini_pascal.y"
    {
													checkIfIdentifierIsDeclared((yyvsp[(1) - (1)].index));
													checkIdentifierIdType((yyvsp[(1) - (1)].index), TYPE_PROCEDURE);
													(yyval.node) = createProcedureCallNode((yyvsp[(1) - (1)].index), createEmptyNodeList());
												;}
    break;

  case 35:
#line 236 "mini_pascal.y"
    {
														checkIfIdentifierIsDeclared((yyvsp[(1) - (4)].index));
														checkIdentifierIdType((yyvsp[(1) - (4)].index), TYPE_PROCEDURE);
														checkParameterCountAndTypes((yyvsp[(1) - (4)].index), (yyvsp[(3) - (4)].nodeList), TYPE_PROCEDURE);
														(yyval.node) = createProcedureCallNode((yyvsp[(1) - (4)].index), (yyvsp[(3) - (4)].nodeList));
													;}
    break;

  case 36:
#line 243 "mini_pascal.y"
    {
														NodeList list = createNodeList((yyvsp[(1) - (1)].node));
														(yyval.nodeList) = list;
													;}
    break;

  case 37:
#line 247 "mini_pascal.y"
    {
														NodeList list = combineNodeLists((yyvsp[(1) - (3)].nodeList), createNodeList((yyvsp[(3) - (3)].node)));
														(yyval.nodeList) = list;
													;}
    break;

  case 38:
#line 252 "mini_pascal.y"
    {
                                                                  		(yyval.node) = (yyvsp[(1) - (1)].node);
                                                              		;}
    break;

  case 39:
#line 255 "mini_pascal.y"
    {
																		checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_GR);
																		(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_GR);
                                                              		;}
    break;

  case 40:
#line 259 "mini_pascal.y"
    {
																		checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_GREQ);
																		(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_GREQ);
                                                              		;}
    break;

  case 41:
#line 263 "mini_pascal.y"
    {
																		checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_SM);
																		(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_SM);
                                                              		;}
    break;

  case 42:
#line 267 "mini_pascal.y"
    {
																		checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_SMEQ);
																		(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_SMEQ);
                                                              		;}
    break;

  case 43:
#line 271 "mini_pascal.y"
    {
																		checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_NOEQ);
																		(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_NOEQ);
                                                              		;}
    break;

  case 44:
#line 275 "mini_pascal.y"
    {
																		checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_EQ);
																		(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_RELOP_EQ);
                                                              		;}
    break;

  case 45:
#line 280 "mini_pascal.y"
    {
                                                        (yyval.node) = (yyvsp[(1) - (1)].node);
                                                    ;}
    break;

  case 46:
#line 283 "mini_pascal.y"
    { 	// + x  == ( 1 * x )
														ASTNode *plus = createIValueNode(1);
                                                        (yyval.node) = createExpressionNode(plus, (yyvsp[(2) - (2)].node), OP_I_MULOP_M);
                                                    ;}
    break;

  case 47:
#line 287 "mini_pascal.y"
    {   // - x  == ( -1 * x
														ASTNode *minus = createIValueNode(-1);
                                                        (yyval.node) = createExpressionNode(minus, (yyvsp[(2) - (2)].node), OP_I_MULOP_M);
                                                    ;}
    break;

  case 48:
#line 291 "mini_pascal.y"
    {
                                                        	checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_ADDOP_MIN);
															(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_ADDOP_MIN);
                                                    	;}
    break;

  case 49:
#line 295 "mini_pascal.y"
    {
                                                        	checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_ADDOP_ADD);
															(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_ADDOP_ADD);
                                                    	;}
    break;

  case 50:
#line 300 "mini_pascal.y"
    {
                                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                                ;}
    break;

  case 51:
#line 303 "mini_pascal.y"
    {
													checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_R_MULOP_D);
													(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_R_MULOP_D);
                                                ;}
    break;

  case 52:
#line 307 "mini_pascal.y"
    {
													checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_R_MULOP_M);
													(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_R_MULOP_M);
                                                ;}
    break;

  case 53:
#line 311 "mini_pascal.y"
    {
													checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_I_MULOP_D);
													(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_I_MULOP_D);
                                                ;}
    break;

  case 54:
#line 315 "mini_pascal.y"
    {
													checkTypes((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_I_MULOP_M);
													(yyval.node) = createExpressionNode((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), OP_I_MULOP_M);
                                                ;}
    break;

  case 55:
#line 320 "mini_pascal.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 56:
#line 321 "mini_pascal.y"
    {
                                                    checkIfIdentifierIsDeclared((yyvsp[(1) - (4)].index));
                                                    checkIdentifierIdType((yyvsp[(1) - (4)].index), TYPE_FUNCTION);
													checkParameterCountAndTypes((yyvsp[(1) - (4)].index), (yyvsp[(3) - (4)].nodeList), TYPE_FUNCTION);
                                                    IdEntry *entry = lookupSymbol(&stack,(yyvsp[(1) - (4)].index));
                                                    FunctionData *data = (FunctionData *)entry->data;
													(yyval.node) = createFunctionCallNode((yyvsp[(1) - (4)].index), data->returnType, (yyvsp[(3) - (4)].nodeList));
												;}
    break;

  case 57:
#line 329 "mini_pascal.y"
    {
													(yyval.node) = createIValueNode((yyvsp[(1) - (1)].iValue));
                                                ;}
    break;

  case 58:
#line 332 "mini_pascal.y"
    {
                                                    (yyval.node) = createRValueNode((yyvsp[(1) - (1)].rValue));
                                                ;}
    break;

  case 59:
#line 335 "mini_pascal.y"
    {
                                                    (yyval.node) = (yyvsp[(2) - (3)].node);
                                                ;}
    break;

  case 60:
#line 339 "mini_pascal.y"
    {
																		NodeList list = createNodeList((yyvsp[(1) - (1)].node));
																		(yyval.nodeList) = list;
																	;}
    break;

  case 61:
#line 343 "mini_pascal.y"
    {
																		NodeList list = combineNodeLists((yyvsp[(1) - (3)].nodeList), createNodeList((yyvsp[(3) - (3)].node)));
																		(yyval.nodeList) = list;
																	;}
    break;

  case 62:
#line 348 "mini_pascal.y"
    {
                                                    checkIfIdentifierIsDeclared((yyvsp[(1) - (1)].index));
                                                    checkIdentifierIdType((yyvsp[(1) - (1)].index), TYPE_VARIABLE);
                                                    IdEntry *entry = lookupSymbol(&stack,(yyvsp[(1) - (1)].index));
                                                    VariableData *data = (VariableData *)entry->data;
                                                    (yyval.node) = createVariableNode((yyvsp[(1) - (1)].index), data->type);
                								;}
    break;

  case 63:
#line 355 "mini_pascal.y"
    {
                                                    checkIfIdentifierIsDeclared((yyvsp[(1) - (4)].index));
                                                    checkIdentifierIdType((yyvsp[(1) - (4)].index), TYPE_VARIABLE);
                                                    checkIdentifierSecondaryType((yyvsp[(1) - (4)].index), TYPE_ARRAY);
													checkIfArrayIndexIsInteger((yyvsp[(3) - (4)].node));
                                                    IdEntry *entry = lookupSymbol(&stack,(yyvsp[(1) - (4)].index));
                                                    VariableData *data = (VariableData *)entry->data;
                                                    (yyval.node) = createArrayNode((yyvsp[(1) - (4)].index), data->type, (yyvsp[(3) - (4)].node));
                                                ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2034 "mini_pascal.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 365 "mini_pascal.y"

// ----------- CHECKING -----

// This function checks if the given type of the condition expression is boolean
void checkCondition(ASTNode *node){
	Type type = determineType(node);
	if(type.base != TYPE_BOOL){
		char *err;
		asprintf(&err, "conditions need to be booleans");
		errorMessage(err);
	}
}

// This function checks if the two types in an assignment will result in truncation
void checkAssignment(ASTNode *left, ASTNode *right){
	Type typeLeft = determineType(left);
	Type typeRight = determineType(right);
	if(typeLeft.base == TYPE_INTEGER && typeRight.base == TYPE_REAL){
		char *war;
        asprintf(&war, "assigning an real to an integer will result in truncation");
        warningMessage(war);
	}
}

/* This function checks two things:
	1. Is the correct amount of parameters given
	2. Are the given parameters of the right type
*/
void checkParameterCountAndTypes(unsigned id, NodeList arguments, IdType type){
	IdEntry *entry = lookupSymbol(&stack, id);
	ParameterList params;
	if(entry->idType != type)
		entry = findShadowedFunctionOrProcedure(&stack, id);

	if(type ==  TYPE_FUNCTION)
		params = ((FunctionData *)entry->data)->parameters;
	else
		params = ((ProcedureData *)entry->data)->parameters;

	if(params.numberOfParameters != arguments.n){
		char *err;
		asprintf(&err, "expected %d parameters but got %d instead", params.numberOfParameters, arguments.n);
		errorMessage(err);
	}

	for(int i = 0; i < params.numberOfParameters; i++){
		ASTNode *argument = arguments.nodes[i];
		Type argumentType = determineType(argument);
		if(params.parameters[i]->type.secondary != argumentType.secondary){
			char *err;
			asprintf(&err, "parameter %s of %s is of type %s %s but received %s %s",	retrieveFromStringTable(*(stack.strTab), params.parameters[i]->strtabIndex), retrieveFromStringTable(*(stack.strTab), id),
																						baseTypeString(params.parameters[i]->type.base), secondaryTypeString(params.parameters[i]->type.secondary),
																						baseTypeString(argumentType.base), secondaryTypeString(argumentType.secondary)
																				);
			errorMessage(err);
		}
		if(params.parameters[i]->type.base != argumentType.base){
			char *war;
			asprintf(&war, "parameter %s of %s is of type %s %s but received %s %s",	retrieveFromStringTable(*(stack.strTab), params.parameters[i]->strtabIndex), retrieveFromStringTable(*(stack.strTab), id),
																						baseTypeString(params.parameters[i]->type.base), secondaryTypeString(params.parameters[i]->type.secondary),
																						baseTypeString(argumentType.base), secondaryTypeString(argumentType.secondary)
																				);
			warningMessage(war);
		}
	}
}

// Checks for one index of an array if it is the right type
void checkIfArrayIndexIsInteger(ASTNode *node){
	Type type = determineType(node);
	if(type.base != TYPE_INTEGER){
		char *err;
		asprintf(&err, "array index should be an integer");
		errorMessage(err);
	}
}

// This method checks if all given indexes of an array are of the right type
void checkIfMultipleArrayIndicesAreAllIntegers(NodeList indices){
	for(int i =0; i < indices.n; i++){
		ASTNode *node = indices.nodes[i];
		checkIfArrayIndexIsInteger(node);
	}
}

void checkTypes(ASTNode *node1, ASTNode *node2, Operator operator){
	Type t1 = determineType(node1);
	Type t2 = determineType(node2);

  switch(operator){
	case OP_RELOP_GR :
  	case OP_RELOP_GREQ :
  	case OP_RELOP_SM :
  	case OP_RELOP_SMEQ :
  	case OP_RELOP_NOEQ :
  	case OP_RELOP_EQ : {
      if(t1.base != t2.base){
        char *war;
        asprintf(&war, "comparing integers with reals");
        warningMessage(war);
      }
	  return;
    }
	case OP_I_MULOP_D :
    case OP_I_MULOP_M : {
      if(t1.base == TYPE_REAL || t2.base == TYPE_REAL){
        char *war;
        asprintf(&war, "integer operation on real");
        warningMessage(war);
      }
      return;
    }
	case OP_R_MULOP_D :
    case OP_R_MULOP_M :
	case OP_ADDOP_ADD :
    case OP_ADDOP_MIN : return;
    default: { // SHOULD NEVER OCCUR
      char *err;
      asprintf(&err, "invalid binary token, something went very very very wrong...");
      errorMessage(err);
	  return;
    }
  }
}

// This method checks if the identifier is of the correct type, REAL OR INTEGER
void checkIdentifierSecondaryType(unsigned index, SecondaryType t){
  IdEntry *entry = lookupSymbol(&stack, index);
  VariableData *data = (VariableData *)entry->data;
  if(data->type.secondary != t){
    char *err;
    asprintf(&err, "variable %s is %s and not %s", retrieveFromStringTable(*(stack.strTab), index), secondaryTypeString(data->type.secondary), secondaryTypeString(t));
    errorMessage(err);
  }
}

// This method checks if the identifier is of the correct type, SCALAR OR ARRAY
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


// This method checks if the identifier is already declared
void checkIfIdentifierIsDeclared(unsigned index){
    IdEntry *entry = lookupSymbol(&stack, index);
    if(entry == NULL){
        char *err;
        asprintf(&err, "variable %s is not yet declared", retrieveFromStringTable(*(stack.strTab), index));
        errorMessage(err);
    }
}

// This method inserts a new entry in the symbol table, and reports if this is not possible
void insert(IdEntry entry){
    if(!insertSymbol(&stack, entry)){
        char *err;
        asprintf(&err, "variable %s is already declared\n", retrieveFromStringTable(*(stack.strTab), entry.strtabIndex));
        errorMessage(err);
    }
}

// ---------- DECLARING -------

void declareVariable(StrtabIndexList indentifiers, Type type){
    for(int i = indentifiers.numberOfIndices-1 ; i >= 0 ; i--){
        VariableData *data = safeMalloc(sizeof(VariableData));
		data->type = type;

        IdEntry newEntry = makeIdEntry(indentifiers.indices[i]);
        newEntry.data = data;
        newEntry.idType = TYPE_VARIABLE;

        insert(newEntry);
    }
}

void declareFunction(unsigned index, Type type, ParameterList parameters){
    FunctionData data;
	data.returnType = type;
	data.parameters = parameters;

    IdEntry newEntry = makeIdEntry(index);
    newEntry.data = safeMalloc(sizeof(FunctionData));
	memcpy(newEntry.data, &data, sizeof(FunctionData));

    newEntry.idType = TYPE_FUNCTION;

    insert(newEntry);
}

void declareProcedure(unsigned index, ParameterList parameters){
    ProcedureData *data = safeMalloc(sizeof(ProcedureData));
	data->parameters = parameters;
    IdEntry newEntry = makeIdEntry(index);
    newEntry.data = data;
    newEntry.idType = TYPE_PROCEDURE;
	insert(newEntry);
}

void declareParametersLocallyAsVariables(ParameterList list){
    for(int i = 0 ; i < list.numberOfParameters ; i++){
        VariableData *data = safeMalloc(sizeof(VariableData *));

		data->type = list.parameters[i]->type;

        IdEntry newEntry = makeIdEntry(list.parameters[i]->strtabIndex);
        newEntry.data = data;
        newEntry.idType = TYPE_VARIABLE;
        insert(newEntry);
    }
}

void declareFunctionLocallyAsVariable(unsigned index, Type type){
    VariableData *data = safeMalloc(sizeof(VariableData *));
	data->type = type;
    IdEntry newEntry = makeIdEntry(index);
    newEntry.data = data;
    newEntry.idType = TYPE_VARIABLE;
    insert(newEntry);
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
	if (argc != 3) {
	    fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
	    return EXIT_FAILURE;
  	}
  	initLexer(argv[1]);

	FILE *output=fopen(argv[2], "w");
	if(output == NULL){
		fprintf(stderr, "Error: failed to open output file\n");
	}

    //yydebug = 1;
    strTab = newStringTable(0);
    stack = initSymbolStack(&strTab);
    yyparse();
	generateIR(output, programNode);
	fclose(output);
    freeSymbolStack(&stack);
    freeStringTable(strTab);

	freeNode(programNode);

	finalizeLexer();
	printf("VERSION 0.1\n");
    return 0;
}

