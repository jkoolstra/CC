

parser : parser.tab.c lex.yy.c AST.c AST.h StringTable.c StringTable.h common.c common.h
	gcc -g -Wall AST.c StringTable.c common.c parser.tab.c lex.yy.c -o parser -lfl

parser.tab.c : parser.y
	bison -Wall -d -t parser.y

lex.yy.c : parser.l
	flex -i parser.l

clean :
	rm lex.yy.c parser.tab.c parser.tab.h
