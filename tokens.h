#ifndef TOKENS_H
#define TOKENS_H

// From parser.tab.h
// We need this because we cannot yet define YYSTYPE
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
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
    ASSIGNOP = 273,
    RELOP_GR = 274,
    RELOP_GREQ = 275,
    RELOP_SM = 276,
    RELOP_SMEQ = 277,
    RELOP_NOEQ = 278,
    RELOP_EQ = 279,
    ADDOP_MIN = 280,
    ADDOP_ADD = 281,
    I_MULOP_M = 282,
    I_MULOP_D = 283,
    R_MULOP_M = 284,
    R_MULOP_D = 285,
    INUM = 286,
    RNUM = 287,
    ID = 288
 };

#endif
typedef enum yytokentype Token;

#endif
