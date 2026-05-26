CXX=g++
CFLAGS = -c -I ThirdParty/include -I include
LDFLAGS = -lglfw -lGL


all: main


# Linking Rule
main: bin/main.o bin/utils.o
	$(CXX) -o main  bin/main.o bin/utils.o $(LDFLAGS)


# Running final executible rule
run: main
	./main

# Compilation rules
bin/%.o: src/%.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<


clean:
	rm -rf bin/* main


.PHONY: all clean run