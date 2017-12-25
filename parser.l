%{
    #include <stdio.h>
    #include "parser.tab.h"

    int lineno = 1;
%}

%option nounput
%option noinput

%x comment

WHITESPACE          \t|" "
SIGN                "+"|"-"
CHARACTER           [a-z]
DIGIT               [0-9]
INTEGER_NUMBER      {DIGIT}+
EXPONENT            [eE]{SIGN}?{INTEGER_NUMBER}
REAL_NUMBER         {INTEGER_NUMBER}("."{INTEGER_NUMBER})?{EXPONENT}?|"."{INTEGER_NUMBER}{EXPONENT}?

ID          (_|{CHARACTER})(_|{CHARACTER}|{DIGIT})*
NUM         {INTEGER_NUMBER}|{REAL_NUMBER}
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

do          { return TOK_DO; }
function    { return TOK_FUNCTION; }
program     { return TOK_PROGRAM; }
procedure   { return TOK_PROCEDURE; }
var         { return TOK_VAR; }
integer     { return TOK_INTEGER; }
real        { return TOK_REAL; }
array       { return TOK_ARRAY; }
of          { return TOK_OF; }
if          { return TOK_IF; }
then        { return TOK_THEN; }
else        { return TOK_ELSE; }
while       { return TOK_WHILE; }
begin       { return TOK_BEGIN; }
end         { return TOK_END; }

{ASSIGNOP}  { return TOK_ASSIGNOP; }
{RELOP}     { return TOK_RELOP; }
{ADDOP}     { return TOK_ADDOP; }
{MULOP}     { return TOK_MULOP; }

{NUM}       { return TOK_NUM; }
{ID}        { return TOK_ID; }

.           { return *yytext; }


















