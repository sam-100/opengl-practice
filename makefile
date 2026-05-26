CXX=g++
CFLAGS = -c -I ThirdParty/include -I include
LDFLAGS = -L ThirdParty/lib -lglfw -lGL


all: main


# Linking Rule
main: bin/main.o bin/utils.o bin/glad.o
	$(CXX) -o main  bin/main.o bin/utils.o bin/glad.o $(LDFLAGS)


# Running final executible rule
run: main
	./main

# Compilation rules
bin/%.o: src/%.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<
bin/glad.o: ThirdParty/src/glad.c
	gcc $(CFLAGS) ThirdParty/src/glad.c -o bin/glad.o

clean:
	rm -rf bin/* main


.PHONY: all clean run