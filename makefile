

parser : parser.tab.c lex.yy.c
	gcc -g -Wall parser.tab.c lex.yy.c -o parser -lfl

parser.tab.c : parser.y
	bison -Wall -d -t parser.y

lex.yy.c : parser.l
	flex -i parser.l

clean :
	rm lex.yy.c parser.tab.c parser.tab.h
