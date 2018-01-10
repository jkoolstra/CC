CC=gcc
CFLAGS=-O2 -Wall -Wunused-function
all: scanner parser SymbolTable.o SymbolStack.o StringTable.o IdEntry.o common.o
	${CC} ${CFLAGS} mini_pascal.tab.c StringTable.o SymbolTable.o SymbolStack.o IdEntry.o common.o -ll -lm

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

test:
	./a.out < Tests/pasc1.in
	./a.out < Tests/pasc2.in
	./a.out < Tests/pasc3.in
	./a.out < Tests/pasc4.in
	./a.out < Tests/pasc5.in
	./a.out < Tests/pasc6.in
	./a.out < Tests/pasc7.in
	./a.out < Tests/pasc8.in
	./a.out < Tests/pasc9.in
	./a.out < Tests/pasc10.in
	./a.out < Tests/pasc11.in
	./a.out < Tests/pasc12.in
	./a.out < Tests/pasc13.in
	./a.out < Tests/pasc14.in
	./a.out < Tests/pasc15.in
	./a.out < Tests/pasc16.in
	./a.out < Tests/pasc17.in
	./a.out < Tests/pasc18.in
	./a.out < Tests/pasc19.in
	./a.out < Tests/pasc20.in

cs:
	./a.out < Cases/calc.pas
	./a.out < Cases/fibonacci.pas
	./a.out < Cases/gcd.pas
	./a.out < Cases/missing.pas
	./a.out < Cases/prime.pas
	./a.out < Cases/pyth.pas
	./a.out < Cases/sumsproducts.pas
	./a.out < Cases/alt.pas
	./a.out < Cases/count.pas
	./a.out < Cases/funcproc.pas
	./a.out < Cases/longexp.pas
	./a.out < Cases/permutations.pas
	./a.out < Cases/puzzle.pas
	./a.out < Cases/sign.pas
