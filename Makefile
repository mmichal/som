OBJECTS := Node.o Som.o SomApp.o main.o
COMPILER := g++
FLAGS := -std=c++0x -g -Wall -pedantic

all: $(OBJECTS)
	$(COMPILER)  $(FLAGS) $(OBJECTS) -o app
.cpp.o:
	$(COMPILER) $(FLAGS) -c  $< -o $@
clean:
	rm *.o

.PHONY: clean
