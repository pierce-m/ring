CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-ll -ly
PARSER=bison
PFLAGS=-vdty
LEXER=flex
SOURCES=y.tab.c lex.yy.c interpreter.c node.c
PARSERSRC=ring.y
LEXERSRC=ring.l
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ring

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

lex.yy.c: y.tab.c $(LEXERSRC)
	$(LEXER) $(LEXERSRC)

y.tab.c: $(PARSERSRC)
	$(PARSER) $(PFLAGS) $(PARSERSRC)

clean:
	rm $(EXECUTABLE) $(OBJECTS) y.tab.c lex.yy.c y.tab.h y.output
