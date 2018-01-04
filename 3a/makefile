CC=gcc
CFLAGS=-O2 -Wall -Wunused-function
all: scanner parser
	${CC} ${CFLAGS} mini_pascal.tab.c -ll -lm

scanner: mini_pascal.l
	flex -i mini_pascal.l
parser: mini_pascal.y
	bison -d -v mini_pascal.y
clean:
	rm -f mini_pascal.tab.c
	rm -f mini_pascal.tab.h
	rm -f lex.yy.c
	rm -f *.o
	rm -f *~
