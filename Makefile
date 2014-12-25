ring: y.tab.o lex.yy.o interpreter.o node.o
	gcc -o ring y.tab.o lex.yy.o interpreter.o -ll -ly

lex.yy.c: y.tab.c ring.l
	flex ring.l

y.tab.c:
	bison -vdty ring.y

clean:
	rm ring y.tab.c lex.yy.c y.tab.h y.output y.tab.o node.o lex.yy.o interpreter.o
