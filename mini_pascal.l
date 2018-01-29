
%{
    #define _PARSER_L
	//#include "tokens.h"
    #include "mini_pascal.tab.h" // YYSTYPE yylval
    #include <stdio.h>
    #include <string.h>
    #include "StringTable.h"
    #include "IdEntry.h"
    #include "common.h"

	#define PRINT 0
	#define INDENT 0
	#define LINES 0

int lineno = 1;
StringTable strTab;
void makeIdentifier();

%}

%option nounput
%option noinput

%x comment

SIGN 				"+"|"-"
WHITESPACE          \t|" "
CHARACTER           [a-z]
DIGIT               [0-9]
EXPONENT            [eE]{SIGN}?{INTEGER_NUMBER}
INTEGER_NUMBER      {DIGIT}+
REAL_NUMBER         {INTEGER_NUMBER}("."{INTEGER_NUMBER})?{EXPONENT}?|"."{INTEGER_NUMBER}{EXPONENT}?

ID          ("_"|{CHARACTER})("_"|{CHARACTER}|{DIGIT})*
ASSIGNOP    ":="
RELOP_GR  	"<"
RELOP_GREQ	"<="
RELOP_SM	">"
RELOP_SMEQ	">="
RELOP_NOEQ	"<>"
RELOP_EQ	"="
ADDOP_ADD   "+"
ADDOP_MIN	"-"
R_MULOP_M   "*"
R_MULOP_D	"/"
I_MULOP_D   "div"
I_MULOP_M	"mod"

%%

{WHITESPACE}    /* eat */{ if(INDENT){printf("%s", yytext);} }

"{"                 { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} BEGIN(comment); }
<comment>"}"        { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} BEGIN(INITIAL); }
<comment>.          /* eat */

<*>\n               { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} ++lineno; }

writeln				{ if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");}  return WRITELN; }
readln				{ if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");}  return READLN; }
do                  { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");}  return DO; }
function            { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return FUNCTION; }
program             { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return PROGRAM; }
procedure           { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return PROCEDURE; }
var                 { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return VAR; }
integer             { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return INTEGER; }
real                { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return REAL; }
array               { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return ARRAY; }
of                  { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return OF; }
if                  { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return IF; }
then                { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return THEN; }
else                { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return ELSE; }
while               { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return WHILE; }
begin               { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return BEG; }
end                 { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return END; }

{ASSIGNOP}          { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return ASSIGNOP; }
{RELOP_GR}          { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return RELOP_GR; }
{RELOP_GREQ}        { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return RELOP_GREQ; }
{RELOP_SM}          { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return RELOP_SM; }
{RELOP_SMEQ}        { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return RELOP_SMEQ; }
{RELOP_NOEQ}        { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return RELOP_NOEQ; }
{RELOP_EQ}          { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return RELOP_EQ; }
{ADDOP_MIN}         { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return ADDOP_MIN; }
{ADDOP_ADD}         { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return ADDOP_ADD; }
{R_MULOP_D}         { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return R_MULOP_D; }
{R_MULOP_M}         { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return R_MULOP_M; }
{I_MULOP_D}         { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return I_MULOP_D; }
{I_MULOP_M}         { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return I_MULOP_M; }
{INTEGER_NUMBER}    { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} yylval.iValue = atoi(yytext); return INUM; }
{REAL_NUMBER}       { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} yylval.rValue = atof(yytext);return RNUM; }
{ID}                { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} makeIdentifier(); return ID;  }
.                   { if(PRINT){printf("%s", yytext);} if(LINES){printf("\n");} return *yytext; }

%%

void initLexer(char *filename) {
  yyin = fopen(filename, "r");

  if (yyin == NULL) {
    fprintf(stderr, "Error: failed to open input file\n");
    exit(EXIT_FAILURE);
  }
}

void makeIdentifier(){
    yylval.index = appendToStringTable(&strTab, yytext);
}

void finalizeLexer() {
  yylex_destroy();
}
