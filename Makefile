exec = steel.exe
sources = $(wildcard src/*.c)
objects = $(sources: .c=.o)
flags = -g -std=c2x

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./steel.exe /usr/local/bin/steel

clean:
	-rm *.exe
	-rm .o
	-rm src/*.o