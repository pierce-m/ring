ring: y.tab.o lex.yy.o 
	gcc -o ring y.tab.o lex.yy.o -ll -ly

lex.yy.c: y.tab.c ring.l
	flex ring.l

y.tab.c:
	bison -vdty ring.y

clean:
	rm ring y.tab.c lex.yy.c y.tab.h y.output y.tab.o lex.yy.o
