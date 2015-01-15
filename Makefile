CC=gcc
CFLAGS=-Wall -c
SOURCES=src/*.c lib/*.c
PARSERFILES=y.tab.c lex.yy.c
OTHERS=y.output out.ring ring.dSYM *.o
EXECUTABLE=ring

$(EXECUTABLE): $(PARSERFILES) 
	$(CC) -g -o $(EXECUTABLE) $(SOURCES) $(PARSERFILES) -ll -ly 

$(PARSERFILES):
	bison -vdty src/ring.y
	flex src/ring.l

clean:
	rm -rf $(OTHERS) $(EXECUTABLE) 

clean-all: clean
	rm -rf $(PARSERFILES) y.tab.h
