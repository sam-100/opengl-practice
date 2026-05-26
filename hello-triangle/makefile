
OBJ = bin/main.o

all: main


# Linking Rule
main: bin/main.o
	g++ -o main  bin/main.o -lglfw


# Running final executible rule
run: main
	./main

# Compilation rules
bin/main.o: src/main.cpp
	g++ -c -I ../../ThirdParty/include -o bin/main.o src/main.cpp


clean:
	rm -rf bin/* main