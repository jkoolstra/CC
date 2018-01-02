
%{
    #define YYSTYPE ASTNode*
    #include <stdio.h>
    #include <string.h>
    #include "AST.h"
    #include "StringTable.h"
    #include "parser.tab.h"

    extern StringTable strTab;

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

{ASSIGNOP}  {   SemanticValue sem;
                ASTNodeValue value;
                sem.op.assign = OP_SET_EQUAL;
                value.token = TOK_ASSIGNOP;
                yylval = buildASTNode(TOKEN_NODE, value, sem, 2, NULL, NULL);
                return TOK_ASSIGNOP;
            }

{RELOP} {   SemanticValue sem;
            ASTNodeValue value;
            if (strlen(yytext) == 1) {
                switch (yytext[0]) {
                    case '<': sem.op.rel = OP_LE; break;
                    case '>': sem.op.rel = OP_GE; break;
                    case '=': sem.op.rel = OP_EQ; break;
                }
            } else { // strlen(yytext) == 2
                switch (yytext[1]) {
                    case '>': sem.op.rel = OP_NEQ; break;
                    case '=':
                        switch (yytext[0]) {
                            case '<': sem.op.rel = OP_LEQ; break;
                            case '>': sem.op.rel = OP_GEQ; break;
                        }
                        break;
                }
            }
            value.token = TOK_RELOP;
            yylval = buildASTNode(TOKEN_NODE, value, sem, 2, NULL, NULL);
            return TOK_RELOP;
        }

{ADDOP}     {   SemanticValue sem;
                ASTNodeValue value;
                switch (yytext[0]) {
                    case '+': sem.op.add = OP_PLUS; break;
                    case '-': sem.op.add = OP_MIN; break;
                }
                value.token = TOK_ADDOP;
                yylval = buildASTNode(TOKEN_NODE, value, sem, NUM_OF_CHILDREN_UNKNOWN);
                return TOK_ADDOP;
            }

{MULOP} {   SemanticValue sem;
            ASTNodeValue value;
            switch (yytext[0]) {
                case '*': sem.op.mul = OP_MUL; break;
                case '/': sem.op.mul = OP_DIV; break;
                case 'd': sem.op.mul = OP_DIV_INT; break;
                case 'm': sem.op.mul = OP_MOD; break;
            }
            value.token = TOK_MULOP;
            yylval = buildASTNode(TOKEN_NODE, value, sem, 2, NULL, NULL);
            return TOK_MULOP;
        }


{INTEGER_NUMBER}    {   SemanticValue sem;
                        ASTNodeValue value;
                        sem.intVal = atoi(yytext);
                        value.token = TOK_NUM;
                        yylval = buildASTNode(TOKEN_NODE, value, sem, 0);
                        return TOK_NUM;
                    }

{REAL_NUMBER}   {   SemanticValue sem;
                    ASTNodeValue value;
                    sscanf(yytext, "%f", &sem.realVal);
                    value.token = TOK_NUM;
                    yylval = buildASTNode(TOKEN_NODE, value, sem, 0);
                    return TOK_NUM;
                }

{ID}        {   SemanticValue sem;
                ASTNodeValue value;
                sem.strTabIndex = appendToStringTable(strTab, yytext);
                value.token = TOK_ID;
                yylval = buildASTNode(TOKEN_NODE, value, sem, 0);
                return TOK_ID;
            }

.           { return *yytext; }


















