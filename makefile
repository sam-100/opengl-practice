CXX=g++
CFLAGS = -c -I ThirdParty/include -I include
LDFLAGS = -L ThirdParty/lib -lglfw

OBJ = bin/main.o \
	bin/utils.o \
	bin/glad.o \
	bin/camera.o

all: main

# Linking Rule
main: $(OBJ)
	$(CXX) -o main  $(OBJ) $(LDFLAGS)


# Running final executible rule
run: main
	LD_LIBRARY_PATH=ThirdParty/lib ./main

# Compilation rules
bin/%.o: src/%.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<
bin/glad.o: ThirdParty/src/glad.c
	gcc $(CFLAGS) ThirdParty/src/glad.c -o bin/glad.o

clean:
	rm -rf bin/* main


.PHONY: all clean run