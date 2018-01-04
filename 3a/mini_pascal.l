
%{
    #define _PARSER_L
    #include "mini_pascal.tab.h" // YYSTYPE yylval
    #include <stdio.h>
    #include <string.h>
    //#include "StringTable.h"

int lineno = 1;

%}

%option nounput
%option noinput

%x comment

WHITESPACE          \t|" "
SIGN                "+"|"-"
CHARACTER           [a-z]
DIGIT               [0-9]
EXPONENT            [eE]{SIGN}?{INTEGER_NUMBER}
INTEGER_NUMBER      {DIGIT}+
REAL_NUMBER         {INTEGER_NUMBER}("."{INTEGER_NUMBER})?{EXPONENT}?|"."{INTEGER_NUMBER}{EXPONENT}?

ID          ("_"|{CHARACTER})("_"|{CHARACTER}|{DIGIT})*
ASSIGNOP    ":="
RELOP       "<"|"<="|">"|">="|"<>"|"="
ADDOP       {SIGN}
MULOP       "*"|"/"|"div"|"mod"

%%

{WHITESPACE}    /* eat */

"{"             { BEGIN(comment); }
<comment>"}"    { BEGIN(INITIAL); }
<comment>.      /* eat */

<*>\n     { ++lineno; }

do          { return DO; }
function    { return FUNCTION; }
program     { return PROGRAM; }
procedure   { return PROCEDURE; }
var         { return VAR; }
integer     { return INTEGER; }
real        { return REAL; }
array       { return ARRAY; }
of          { return OF; }
if          { return IF; }
then        { return THEN; }
else        { return ELSE; }
while       { return WHILE; }
begin       { return BEG; }
end         { return END; }

{ASSIGNOP}  { return ASSIGNOP; }
{RELOP}     { return RELOP; }
{ADDOP}     { return ADDOP; }
{MULOP}     { return MULOP; }
{INTEGER_NUMBER}    { return INUM; }
{REAL_NUMBER}   {  return RNUM; }
{ID}        { return ID;  }
.           { return *yytext; }















