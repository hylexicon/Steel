exec = steel.exe
sources = $(wildcard src/*.c)
objects = $(sources: .c=.o)
flags = -g

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

lexer: rules/lex.l
	flex -o src/lex.c --header-file=src/include/lex.h rules/lex.l 

parser: rules/parse.y rules/lexer.l
	bison -o src/parse.c --defines=src/include/parse.h rules/parse.y

install:
	make
	cp ./steel.exe /usr/local/bin/steel

clean:
	-rm *.exe
	-rm *.o
