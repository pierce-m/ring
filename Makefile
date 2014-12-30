CC=gcc
CFLAGS=-Wall
SOURCES=y.tab.c lex.yy.c interpreter.c node.c
OBJECTS=$(SOURCES:.c=.o)
TRASH=y.tab.c lex.yy.c y.tab.h y.output out.ring ring.dSYM
EXECUTABLE=ring

$(EXECUTABLE): $(OBJECTS)
	$(CC) -g -o $(EXECUTABLE) $(SOURCES) -ll -ly 

lex.yy.c: y.tab.c
	flex ring.l

y.tab.c:
	bison -vdty ring.y

clean:
	rm -rf $(TRASH) $(EXECUTABLE) $(OBJECTS) 
