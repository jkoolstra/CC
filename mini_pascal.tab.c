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
     RELOP = 275,
     ADDOP = 276,
     I_MULOP = 277,
     R_MULOP = 278,
     INUM = 279,
     RNUM = 280,
     ID = 281
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
#define RELOP 275
#define ADDOP 276
#define I_MULOP 277
#define R_MULOP 278
#define INUM 279
#define RNUM 280
#define ID 281




/* Copy the first part of user declarations.  */
#line 2 "mini_pascal.y"

    #include "IdEntry.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include "lex.yy.c"
    #include "StringTable.h"
    #include "SymbolStack.h"
    #include "common.h"

    // CHECKING
	void checkCondition(Type);
	void checkAssignment(Type, Type);
    void checkIfIdentifierIsDeclared(unsigned);
    void checkIdentifierIdType(unsigned, IdType);
    void checkIdentifierSecondaryType(unsigned, SecondaryType);
	void checkIfArrayIndexIsInteger(Type);
	void checkIfMultipleArrayIndicesAreAllIntegers(TypeList types);
	void checkParameterCountAndTypes(unsigned id, TypeList list, IdType type);
    Type checkTypes(Type, Type, enum yytokentype);

	// DECLARING
    void declareFunctionLocallyAsVariable(StrtabIndexList, Type type);
    void declareParametersLocallyAsVariables(ParameterList);
    void declareVariable(StrtabIndexList, Type);
    void declareFunction(StrtabIndexList, Type, ParameterList);
    void declareProcedure(StrtabIndexList, ParameterList);

	// ERROR HANDLING
    int yyerror(char *errmsg);
    void errorMessage(char *msg);
    void warningMessage(char *msg);

    SymbolStack stack;


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
#line 37 "mini_pascal.y"
{
    StrtabIndexList indexList;
    ParameterList parameterList;
    Type type;
    TypeList typeList;
}
/* Line 193 of yacc.c.  */
#line 190 "mini_pascal.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 203 "mini_pascal.tab.c"

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
#define YYLAST   110

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  49
/* YYNRULES -- Number of states.  */
#define YYNSTATES  115

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,    28,     2,     2,    31,     2,    30,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    32,    29,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,    14,    16,    20,    27,    28,    30,    40,
      42,    44,    48,    49,    53,    60,    65,    69,    70,    74,
      80,    84,    86,    87,    89,    93,    97,    99,   101,   108,
     113,   115,   120,   122,   127,   129,   133,   135,   139,   141,
     144,   148,   150,   154,   158,   160,   165,   167,   169,   173
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,     3,    26,    27,    37,    28,    29,    38,
      41,    46,    30,    -1,    26,    -1,    37,    31,    26,    -1,
      38,    13,    37,    32,    39,    29,    -1,    -1,    40,    -1,
      14,    33,    24,    30,    30,    24,    34,    15,    40,    -1,
      17,    -1,    18,    -1,    41,    42,    29,    -1,    -1,    43,
      38,    46,    -1,     4,    26,    44,    32,    40,    29,    -1,
       5,    26,    44,    29,    -1,    27,    45,    28,    -1,    -1,
      37,    32,    39,    -1,    45,    29,    37,    32,    39,    -1,
       6,    47,     7,    -1,    48,    -1,    -1,    49,    -1,    48,
      29,    49,    -1,    50,    19,    53,    -1,    51,    -1,    46,
      -1,     8,    53,     9,    49,    10,    49,    -1,    11,    53,
      12,    49,    -1,    26,    -1,    26,    33,    52,    34,    -1,
      26,    -1,    26,    27,    52,    28,    -1,    53,    -1,    52,
      31,    53,    -1,    54,    -1,    54,    20,    54,    -1,    55,
      -1,    21,    55,    -1,    54,    21,    55,    -1,    56,    -1,
      55,    23,    56,    -1,    55,    22,    56,    -1,    26,    -1,
      26,    27,    52,    28,    -1,    24,    -1,    25,    -1,    27,
      53,    28,    -1,    26,    33,    54,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    60,    60,    70,    71,    75,    78,    81,    84,    88,
      91,    95,    96,    98,   104,   116,   124,   128,   134,   142,
     151,   155,   156,   158,   159,   161,   164,   165,   166,   169,
     173,   181,   192,   196,   202,   205,   210,   213,   217,   220,
     223,   227,   230,   233,   237,   246,   254,   258,   262,   265
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "FUNCTION", "PROCEDURE",
  "BEG", "END", "IF", "THEN", "ELSE", "WHILE", "DO", "VAR", "ARRAY", "OF",
  "ARRSEP", "INTEGER", "REAL", "ASSIGNOP", "RELOP", "ADDOP", "I_MULOP",
  "R_MULOP", "INUM", "RNUM", "ID", "'('", "')'", "';'", "'.'", "','",
  "':'", "'['", "']'", "$accept", "Program", "Identifier_list",
  "Declarations", "Type", "Standard_type", "Subprogram_declarations",
  "Subprogram_declaration", "Subprogram_head", "Arguments",
  "Parameter_list", "Compound_statement", "Optional_statements",
  "Statement_list", "Statement", "Variable", "Procedure_statement",
  "Expression_list", "Expression", "Simple_expression", "Term", "Factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    40,    41,    59,
      46,    44,    58,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    39,    39,    40,
      40,    41,    41,    42,    43,    43,    44,    44,    45,    45,
      46,    47,    47,    48,    48,    49,    49,    49,    49,    49,
      50,    50,    51,    51,    52,    52,    53,    53,    54,    54,
      54,    55,    55,    55,    56,    56,    56,    56,    56,    56
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,    10,     1,     3,     6,     0,     1,     9,     1,
       1,     3,     0,     3,     6,     4,     3,     0,     3,     5,
       3,     1,     0,     1,     3,     3,     1,     1,     6,     4,
       1,     4,     1,     4,     1,     3,     1,     3,     1,     2,
       3,     1,     3,     3,     1,     4,     1,     1,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     3,     0,     0,     0,
       6,     4,    12,     0,     0,     0,     0,     0,    22,     0,
       6,     0,     0,    17,    17,     0,     0,    32,    27,     0,
      21,    23,     0,    26,    11,     0,     2,     0,     9,    10,
       0,     7,     0,     0,     0,     0,    46,    47,    44,     0,
       0,    36,    38,    41,     0,     0,     0,    20,     0,     0,
      13,     0,     5,     0,     0,     0,    15,    39,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,     0,
      24,    25,     0,     0,    16,     0,     0,     0,     0,    48,
       0,    37,    40,    43,    42,    29,    33,     0,    31,     0,
      18,     0,    14,    45,    49,     0,    35,     0,     0,    28,
       0,    19,     0,     0,     8
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,    12,    40,    41,    14,    19,    20,    43,
      64,    28,    29,    30,    31,    32,    33,    77,    78,    51,
      52,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -76
static const yytype_int8 yypact[] =
{
      23,     2,    37,   -10,   -76,     4,   -76,    17,    15,    32,
     -76,   -76,    36,     4,    63,    33,    47,    57,     3,    58,
     -76,    56,    29,    61,    61,    14,    14,   -12,   -76,    82,
      64,   -76,    71,   -76,   -76,     7,   -76,    59,   -76,   -76,
      65,   -76,     4,    66,    67,    30,   -76,   -76,     9,    14,
      86,    40,    48,   -76,    79,    14,    14,   -76,     3,    14,
     -76,    73,   -76,    44,    49,    62,   -76,    48,    14,    14,
      72,     3,    14,    30,    30,    30,     3,    22,   -76,   -15,
     -76,   -76,    69,    29,   -76,     4,    74,    31,    -9,   -76,
      91,    81,    48,   -76,   -76,   -76,   -76,    14,   -76,    75,
     -76,    50,   -76,   -76,   -76,     3,   -76,    80,    29,   -76,
      76,   -76,    92,    62,   -76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -76,   -76,   -11,    88,   -75,   -62,   -76,   -76,   -76,    85,
     -76,    -8,   -76,   -76,   -53,   -76,   -76,   -46,   -25,    -6,
     -41,    10
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -31
static const yytype_int8 yytable[] =
{
      50,    54,    15,    86,    67,    80,    21,   -30,   100,    18,
      79,    25,    73,    18,    26,    55,    97,     5,    90,    98,
      13,    56,    87,    95,    70,   104,     1,    60,     3,    27,
       6,    63,    92,   111,    81,    45,    68,     4,    46,    47,
      48,    49,    69,    37,    10,     8,    38,    39,     9,    13,
      96,   114,   109,    97,    46,    47,    48,    49,    11,   103,
      72,    73,    97,    88,     9,    22,    91,    16,    17,    18,
      74,    75,   106,    23,   101,     9,    83,    84,    85,    38,
      39,     9,   108,    24,    93,    94,    36,    34,    42,    57,
      59,    76,    61,    58,    62,    71,    66,    82,    65,    99,
      89,   105,    73,   102,   110,   107,     0,   113,    35,    44,
     112
};

static const yytype_int8 yycheck[] =
{
      25,    26,    13,    65,    45,    58,    14,    19,    83,     6,
      56,     8,    21,     6,    11,    27,    31,    27,    71,    34,
      13,    33,    68,    76,    49,    34,     3,    35,    26,    26,
      26,    42,    73,   108,    59,    21,    27,     0,    24,    25,
      26,    27,    33,    14,    29,    28,    17,    18,    31,    13,
      28,   113,   105,    31,    24,    25,    26,    27,    26,    28,
      20,    21,    31,    69,    31,    32,    72,     4,     5,     6,
      22,    23,    97,    26,    85,    31,    32,    28,    29,    17,
      18,    31,    32,    26,    74,    75,    30,    29,    27,     7,
      19,    12,    33,    29,    29,     9,    29,    24,    32,    30,
      28,    10,    21,    29,    24,    30,    -1,    15,    20,    24,
      34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    36,    26,     0,    27,    26,    37,    28,    31,
      29,    26,    38,    13,    41,    37,     4,     5,     6,    42,
      43,    46,    32,    26,    26,     8,    11,    26,    46,    47,
      48,    49,    50,    51,    29,    38,    30,    14,    17,    18,
      39,    40,    27,    44,    44,    21,    24,    25,    26,    27,
      53,    54,    55,    56,    53,    27,    33,     7,    29,    19,
      46,    33,    29,    37,    45,    32,    29,    55,    27,    33,
      53,     9,    20,    21,    22,    23,    12,    52,    53,    52,
      49,    53,    24,    32,    28,    29,    40,    52,    54,    28,
      49,    54,    55,    56,    56,    49,    28,    31,    34,    30,
      39,    37,    29,    28,    34,    10,    53,    30,    32,    49,
      24,    39,    34,    15,    40
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
#line 66 "mini_pascal.y"
    {
                    //declareIdentifiers($2, makeEmptyType(), TYPE_PROGRAM);
                ;}
    break;

  case 3:
#line 70 "mini_pascal.y"
    { (yyval.indexList) = (yyvsp[(1) - (1)].indexList); ;}
    break;

  case 4:
#line 71 "mini_pascal.y"
    {
                                                (yyval.indexList) = combineIdentifiers((yyvsp[(1) - (3)].indexList), (yyvsp[(3) - (3)].indexList));
                                            ;}
    break;

  case 5:
#line 75 "mini_pascal.y"
    {
                                                                    declareVariable((yyvsp[(3) - (6)].indexList), (yyvsp[(5) - (6)].type));
                                                                ;}
    break;

  case 7:
#line 81 "mini_pascal.y"
    {
                                    (yyval.type) = makeType((yyvsp[(1) - (1)].type).base, TYPE_SCALAR);
                                ;}
    break;

  case 8:
#line 84 "mini_pascal.y"
    {
                                                                        (yyval.type) = makeType((yyvsp[(9) - (9)].type).base, TYPE_ARRAY);
                                                                    ;}
    break;

  case 9:
#line 88 "mini_pascal.y"
    {
                                (yyval.type).base = TYPE_INTEGER ;
                            ;}
    break;

  case 10:
#line 91 "mini_pascal.y"
    {
                                (yyval.type).base = TYPE_REAL ;
                            ;}
    break;

  case 13:
#line 100 "mini_pascal.y"
    {
                                                    outdent(&stack);
                                                ;}
    break;

  case 14:
#line 106 "mini_pascal.y"
    {
                                                            declareFunction((yyvsp[(2) - (6)].indexList), (yyvsp[(5) - (6)].type), (yyvsp[(3) - (6)].parameterList));
															printSymbolStack(&stack);
                                                            indent(&stack);
															printSymbolStack(&stack);
                                                            declareFunctionLocallyAsVariable((yyvsp[(2) - (6)].indexList), (yyvsp[(5) - (6)].type));
															printSymbolStack(&stack);
                                                            declareParametersLocallyAsVariables((yyvsp[(3) - (6)].parameterList));
															printSymbolStack(&stack);
                                                        ;}
    break;

  case 15:
#line 118 "mini_pascal.y"
    {
                                        declareProcedure((yyvsp[(2) - (4)].indexList), (yyvsp[(3) - (4)].parameterList));
                                        indent(&stack);
                                        declareParametersLocallyAsVariables((yyvsp[(3) - (4)].parameterList));
                                    ;}
    break;

  case 16:
#line 124 "mini_pascal.y"
    {

                                                (yyval.parameterList) = (yyvsp[(2) - (3)].parameterList);
                                            ;}
    break;

  case 17:
#line 128 "mini_pascal.y"
    {
                                                ParameterList list;
                                                list.numberOfParameters = 0;
                                                (yyval.parameterList) = list;
                                            ;}
    break;

  case 18:
#line 134 "mini_pascal.y"
    {
												printf("Single\n");
                                                (yyval.parameterList) = createParameterList((yyvsp[(1) - (3)].indexList), (yyvsp[(3) - (3)].type));
												printf("%d \n",(yyval.parameterList).numberOfParameters);
												for(int i = 0; i < (yyval.parameterList).numberOfParameters; i++){
													printf("[%d] %s: \n", i, retrieveFromStringTable(*(stack.strTab), (yyval.parameterList).parameters[i]->strtabIndex));
												}
                                            ;}
    break;

  case 19:
#line 142 "mini_pascal.y"
    {
                                                                    appendParameterLists(&(yyvsp[(1) - (5)].parameterList), (yyvsp[(3) - (5)].indexList), (yyvsp[(5) - (5)].type));
																	(yyval.parameterList) = (yyvsp[(1) - (5)].parameterList);
																	printf("%d \n",(yyval.parameterList).numberOfParameters);
																	for(int i = 0; i < (yyval.parameterList).numberOfParameters; i++){
																		printf("[%d] %s: \n", i, retrieveFromStringTable(*(stack.strTab), (yyval.parameterList).parameters[i]->strtabIndex));
																	}
																;}
    break;

  case 25:
#line 161 "mini_pascal.y"
    {
	 												checkAssignment((yyvsp[(1) - (3)].type), (yyvsp[(3) - (3)].type));
												;}
    break;

  case 28:
#line 166 "mini_pascal.y"
    {
																	checkCondition((yyvsp[(2) - (6)].type));
																;}
    break;

  case 29:
#line 169 "mini_pascal.y"
    {
																	checkCondition((yyvsp[(2) - (4)].type));
																;}
    break;

  case 30:
#line 173 "mini_pascal.y"
    {
                                                  checkIfIdentifierIsDeclared((yyvsp[(1) - (1)].indexList).indices[0]);
                                                  checkIdentifierIdType((yyvsp[(1) - (1)].indexList).indices[0], TYPE_VARIABLE);
												  checkIdentifierSecondaryType((yyvsp[(1) - (1)].indexList).indices[0], TYPE_SCALAR);
												  IdEntry *entry = lookupSymbol(&stack,(yyvsp[(1) - (1)].indexList).indices[0]);
												  VariableData *data = (VariableData *)entry->data;
												  (yyval.type) = *data->type;
                                              ;}
    break;

  case 31:
#line 181 "mini_pascal.y"
    {
                                                  checkIfIdentifierIsDeclared((yyvsp[(1) - (4)].indexList).indices[0]);
                                                  checkIdentifierIdType((yyvsp[(1) - (4)].indexList).indices[0], TYPE_VARIABLE);
                                                  checkIdentifierSecondaryType((yyvsp[(1) - (4)].indexList).indices[0], TYPE_ARRAY);
												  checkIfMultipleArrayIndicesAreAllIntegers((yyvsp[(3) - (4)].typeList));
												  IdEntry *entry = lookupSymbol(&stack,(yyvsp[(1) - (4)].indexList).indices[0]);
												  VariableData *data = (VariableData *)entry->data;
												  (yyval.type) = *data->type;
												  (yyval.type).secondary = TYPE_SCALAR;
                                              ;}
    break;

  case 32:
#line 192 "mini_pascal.y"
    {
													checkIfIdentifierIsDeclared((yyvsp[(1) - (1)].indexList).indices[0]);
													checkIdentifierIdType((yyvsp[(1) - (1)].indexList).indices[0], TYPE_PROCEDURE);
												;}
    break;

  case 33:
#line 196 "mini_pascal.y"
    {
														checkIfIdentifierIsDeclared((yyvsp[(1) - (4)].indexList).indices[0]);
														checkIdentifierIdType((yyvsp[(1) - (4)].indexList).indices[0], TYPE_PROCEDURE);
														checkParameterCountAndTypes((yyvsp[(1) - (4)].indexList).indices[0], (yyvsp[(3) - (4)].typeList), TYPE_PROCEDURE);
													;}
    break;

  case 34:
#line 202 "mini_pascal.y"
    {
														(yyval.typeList) = createTypeList((yyvsp[(1) - (1)].type));
													;}
    break;

  case 35:
#line 205 "mini_pascal.y"
    {
														appendToTypeLists(&(yyvsp[(1) - (3)].typeList), (yyvsp[(3) - (3)].type));
														(yyval.typeList) = (yyvsp[(1) - (3)].typeList);
													;}
    break;

  case 36:
#line 210 "mini_pascal.y"
    {
                                                                  (yyval.type) = (yyvsp[(1) - (1)].type);
                                                              ;}
    break;

  case 37:
#line 213 "mini_pascal.y"
    {
                                                                  (yyval.type) = checkTypes((yyvsp[(1) - (3)].type), (yyvsp[(3) - (3)].type), RELOP);
                                                              ;}
    break;

  case 38:
#line 217 "mini_pascal.y"
    {
                                                        (yyval.type) = (yyvsp[(1) - (1)].type);
                                                    ;}
    break;

  case 39:
#line 220 "mini_pascal.y"
    {
                                                        (yyval.type) = (yyvsp[(2) - (2)].type);
                                                    ;}
    break;

  case 40:
#line 223 "mini_pascal.y"
    {
                                                        (yyval.type) = checkTypes((yyvsp[(1) - (3)].type), (yyvsp[(3) - (3)].type), ADDOP);
                                                    ;}
    break;

  case 41:
#line 227 "mini_pascal.y"
    {
                                                    (yyval.type) = (yyvsp[(1) - (1)].type);
                                                ;}
    break;

  case 42:
#line 230 "mini_pascal.y"
    {
                                                    (yyval.type) = checkTypes((yyvsp[(1) - (3)].type), (yyvsp[(3) - (3)].type), R_MULOP);
                                                ;}
    break;

  case 43:
#line 233 "mini_pascal.y"
    {
                                                    (yyval.type) = checkTypes((yyvsp[(1) - (3)].type), (yyvsp[(3) - (3)].type), I_MULOP);
                                                ;}
    break;

  case 44:
#line 237 "mini_pascal.y"
    {
                                                    checkIfIdentifierIsDeclared((yyvsp[(1) - (1)].indexList).indices[0]);
                                                    checkIdentifierIdType((yyvsp[(1) - (1)].indexList).indices[0], TYPE_VARIABLE);
                                                    checkIdentifierSecondaryType((yyvsp[(1) - (1)].indexList).indices[0], TYPE_SCALAR);
                                                    IdEntry *entry = lookupSymbol(&stack,(yyvsp[(1) - (1)].indexList).indices[0]);
                                                    VariableData *data = (VariableData *)entry->data;
                                                    (yyval.type) = *data->type;

                                                ;}
    break;

  case 45:
#line 246 "mini_pascal.y"
    {
                                                    checkIfIdentifierIsDeclared((yyvsp[(1) - (4)].indexList).indices[0]);
                                                    checkIdentifierIdType((yyvsp[(1) - (4)].indexList).indices[0], TYPE_FUNCTION);
													checkParameterCountAndTypes((yyvsp[(1) - (4)].indexList).indices[0], (yyvsp[(3) - (4)].typeList), TYPE_FUNCTION);
                                                    IdEntry *entry = lookupSymbol(&stack,(yyvsp[(1) - (4)].indexList).indices[0]);
                                                    FunctionData *data = (FunctionData *)entry->data;
                                                    (yyval.type) = *data->returnType;
                                                ;}
    break;

  case 46:
#line 254 "mini_pascal.y"
    {
                                                    (yyval.type).base = TYPE_INTEGER;
                                                    (yyval.type).secondary = TYPE_SCALAR;
                                                ;}
    break;

  case 47:
#line 258 "mini_pascal.y"
    {
                                                    (yyval.type).base = TYPE_REAL;
                                                    (yyval.type).secondary = TYPE_SCALAR;
                                                ;}
    break;

  case 48:
#line 262 "mini_pascal.y"
    {
                                                    (yyval.type) = (yyvsp[(2) - (3)].type);
                                                ;}
    break;

  case 49:
#line 265 "mini_pascal.y"
    {
                                                    checkIfIdentifierIsDeclared((yyvsp[(1) - (4)].indexList).indices[0]);
                                                    checkIdentifierIdType((yyvsp[(1) - (4)].indexList).indices[0], TYPE_VARIABLE);
                                                    checkIdentifierSecondaryType((yyvsp[(1) - (4)].indexList).indices[0], TYPE_ARRAY);
													checkIfArrayIndexIsInteger((yyvsp[(3) - (4)].type));
                                                    IdEntry *entry = lookupSymbol(&stack,(yyvsp[(1) - (4)].indexList).indices[0]);
                                                    VariableData *data = (VariableData *)entry->data;
                                                    (yyval.type) = *data->type;
                                                    (yyval.type).secondary = TYPE_SCALAR;
                                                ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1810 "mini_pascal.tab.c"
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


#line 276 "mini_pascal.y"

// ----------- CHECKING -----

// This function checks if the given type of the condition expression is boolean
void checkCondition(Type t1){
	if(t1.base != TYPE_BOOL){
		char *err;
		asprintf(&err, "conditions need to be booleans");
		errorMessage(err);
	}
}

// This function checks if the two types in an assignment will result in truncation
void checkAssignment(Type t1, Type t2){
	if(t1.base == TYPE_INTEGER && t2.base == TYPE_REAL){
		char *war;
        asprintf(&war, "assigning an real to an integer will result in truncation");
        warningMessage(war);
	}
}

/* This function checks two things:
	1. Is the correct amount of parameters given
	2. Are the given parameters of the right type
*/
void checkParameterCountAndTypes(unsigned id, TypeList list, IdType type){
	printSymbolStack(&stack);
	IdEntry *entry = lookupSymbol(&stack, id);
	ParameterList params;
	if(entry->idType != type)
		entry = findShadowedFunctionOrProcedure(&stack, id);

	if(type ==  TYPE_FUNCTION)
		params = *((FunctionData *)entry->data)->parameters;
	else
		params = *((ProcedureData *)entry->data)->parameters;

	printf("expected %d parameters but got %d instead\n", params.numberOfParameters, list.numberOfTypes);
	if(params.numberOfParameters != list.numberOfTypes){
		char *err;
		asprintf(&err, "expected %d parameters but got %d instead", params.numberOfParameters, list.numberOfTypes);
		errorMessage(err);
	}

	for(int i = 0; i < params.numberOfParameters; i++){
		if(params.parameters[i]->type->secondary != list.types[i]->secondary){
			char *err;
			asprintf(&err, "parameter %s of %s is of type %s %s but received %s %s",	retrieveFromStringTable(*(stack.strTab), params.parameters[i]->strtabIndex), retrieveFromStringTable(*(stack.strTab), id),
																						baseTypeString(params.parameters[i]->type->base), secondaryTypeString(params.parameters[i]->type->secondary),
																						baseTypeString(list.types[i]->base), secondaryTypeString(list.types[i]->secondary)
																				);
			errorMessage(err);
		}
		if(params.parameters[i]->type->base != list.types[i]->base){
			char *war;
			asprintf(&war, "parameter %s of %s is of type %s %s but received %s %s",	retrieveFromStringTable(*(stack.strTab), params.parameters[i]->strtabIndex), retrieveFromStringTable(*(stack.strTab), id),
																						baseTypeString(params.parameters[i]->type->base), secondaryTypeString(params.parameters[i]->type->secondary),
																						baseTypeString(list.types[i]->base), secondaryTypeString(list.types[i]->secondary)
																				);
			warningMessage(war);
		}
	}
}

// Checks for one index of an array if it is the right type
void checkIfArrayIndexIsInteger(Type type){
	if(type.base != TYPE_INTEGER){
		char *err;
		asprintf(&err, "array index should be an integer");
		errorMessage(err);
	}
}

// This method checks if all given indexes of an array are of the right type
void checkIfMultipleArrayIndicesAreAllIntegers(TypeList types){
	for(int i =0; i < types.numberOfTypes; i++){
		checkIfArrayIndexIsInteger(*types.types[i]);
	}
}

// This method checks if all given indexes of an array are of the right type
Type checkTypes(Type t1, Type t2, enum yytokentype token){
  switch(token){
    case RELOP : {
      if(t1.base != t1.base){
        char *war;
        asprintf(&war, "comparing integers with reals");
        warningMessage(war);
      }
      return makeType(TYPE_BOOL, TYPE_SCALAR);
    }
    case I_MULOP : {
      if(t1.base == TYPE_REAL || t2.base == TYPE_REAL){
        char *err;
        asprintf(&err, "integer operation on real");
        errorMessage(err);
      }
      return makeType(TYPE_INTEGER, TYPE_SCALAR);
    }
    case R_MULOP : {
      return makeType(TYPE_REAL, TYPE_SCALAR);
    }
    case ADDOP : {
      if(t1.base == t2.base){ // SAME TYPE NO ISSUE
        return t1;
      }
      return makeType(TYPE_REAL, TYPE_SCALAR);
    }
    default: { // SHOULD NEVER OCCUR
      char *err;
      asprintf(&err, "invalid binary token, something went very very very wrong...");
      errorMessage(err);
	  return makeType(TYPE_REAL, TYPE_SCALAR);	// stops warning;
    }
  }
}

void checkIdentifierSecondaryType(unsigned index, SecondaryType t){
  IdEntry *entry = lookupSymbol(&stack, index);
  VariableData *data = (VariableData *)entry->data;
  if(data->type->secondary != t){
    char *err;
    asprintf(&err, "variable %s is %s and not %s", retrieveFromStringTable(*(stack.strTab), index), secondaryTypeString(data->type->secondary), secondaryTypeString(t));
    errorMessage(err);
  }
}

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

void checkIfIdentifierIsDeclared(unsigned index){
    IdEntry *entry = lookupSymbol(&stack, index);
    if(entry == NULL){
        //printSymbolStack(&stack);
        char *err;
        asprintf(&err, "variable %s is not yet declared", retrieveFromStringTable(*(stack.strTab), index));
        errorMessage(err);
    }
}

// ---------- DECLARING -------

void insert(IdEntry entry){
    if(!insertSymbol(&stack, entry)){
        char *err;
        asprintf(&err, "variable %s is already declared\n", retrieveFromStringTable(*(stack.strTab), entry.strtabIndex));
        errorMessage(err);
    }
}

void declareVariable(StrtabIndexList indentifiers, Type type){
    //printf("declareVariable\n");
    for(int i = indentifiers.numberOfIndices-1 ; i >= 0 ; i--){
        VariableData *data = safeMalloc(sizeof(VariableData *));

		data->type = safeMalloc(sizeof(Type));
		memcpy(data->type, &type, sizeof(Type));

        IdEntry newEntry = makeIdEntry(indentifiers.indices[i]);
        newEntry.data = data;
        newEntry.idType = TYPE_VARIABLE;

        insert(newEntry);
    }
}

void declareFunction(StrtabIndexList indentifiers, Type type, ParameterList parameters){
    FunctionData data;

	data.returnType = safeMalloc(sizeof(Type));
	memcpy(data.returnType, &type, sizeof(Type));


	data.parameters = safeMalloc(sizeof(ParameterList));
	memcpy(data.parameters, &parameters, sizeof(ParameterList));
	printf("%d \n",parameters.numberOfParameters);
	for(int i = 0; i < parameters.numberOfParameters; i++){
		printf("[%d] %s: \n", i, retrieveFromStringTable(*(stack.strTab), parameters.parameters[i]->strtabIndex));
	}

    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = safeMalloc(sizeof(FunctionData));
	memcpy(newEntry.data, &data, sizeof(FunctionData));
    newEntry.idType = TYPE_FUNCTION;

	printf("base: %s -> secondary : %s \n", baseTypeString(((FunctionData *)newEntry.data)->returnType->base), secondaryTypeString(((FunctionData *)newEntry.data)->returnType->secondary));
	for(int i = 0; i < ((FunctionData *)newEntry.data)->parameters->numberOfParameters; i++){
		printf("[%d] %s: \n", i, retrieveFromStringTable(*(stack.strTab), ((FunctionData *)newEntry.data)->parameters->parameters[i]->strtabIndex));
	}
	printEntry(newEntry, *stack.strTab);
    insert(newEntry);
}

void declareProcedure(StrtabIndexList indentifiers, ParameterList parameters){
    ProcedureData *data = safeMalloc(sizeof(ProcedureData *));
	data->parameters = safeMalloc(sizeof(ParameterList));
	memcpy(data->parameters, &parameters, sizeof(ParameterList));
    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
    newEntry.idType = TYPE_PROCEDURE;
	insert(newEntry);
}

void declareParametersLocallyAsVariables(ParameterList list){
    //printf("declareParametersLocallyAsVariables : %d\n", list.numberOfParameters);
    for(int i = 0 ; i < list.numberOfParameters ; i++){
		//printf("base: %s -> secondary : %s \n", baseTypeString(list.parameters[i].type.base), secondaryTypeString(list.parameters[i].type.secondary));
        VariableData *data = safeMalloc(sizeof(VariableData *));

		data->type = list.parameters[i]->type;/*safeMalloc(sizeof(Type));
		memcpy(data->type, &list.parameters[i]->type, sizeof(Type));*/

        IdEntry newEntry = makeIdEntry(list.parameters[i]->strtabIndex);
        newEntry.data = data;
        newEntry.idType = TYPE_VARIABLE;
		//printEntry(newEntry, *stack.strTab);
        insert(newEntry);
    }
	//printSymbolStack(&stack);
	//printSymbolStack(&stack);
}

void declareFunctionLocallyAsVariable(StrtabIndexList indentifiers, Type type){
	//printSymbolStack(&stack);
    VariableData *data = safeMalloc(sizeof(VariableData *));
	//printf("base: %s -> secondary : %s \n", baseTypeString(type.base), secondaryTypeString(type.secondary));
	data->type = safeMalloc(sizeof(Type));
	memcpy(data->type, &type, sizeof(Type));
	//printf("base: %s -> secondary : %s \n", baseTypeString(data->type.base), secondaryTypeString(data->type.secondary));

    IdEntry newEntry = makeIdEntry(indentifiers.indices[0]);
    newEntry.data = data;
    newEntry.idType = TYPE_VARIABLE;
	//printEntry(newEntry, *stack.strTab);
    insert(newEntry);
	//printSymbolStack(&stack);
    //printSymbolStack(&stack);
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

