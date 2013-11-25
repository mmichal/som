OBJECTS := ./src/Node.o ./src/Som.o ./src/SomApp.o ./src/main.o
TESTOBJECTS := ./src/Node.o ./src/Som.o ./src/SomApp.o ./test/main.o
COMPILER := g++
FLAGS := -std=c++0x -g -Wall -pedantic -iquote./src -iquote./test -iquote./lib

all: $(OBJECTS)
	$(COMPILER)  $(FLAGS) $(OBJECTS) -o app
.cpp.o:
	$(COMPILER) $(FLAGS) -c  $< -o $@
clean:
	rm ./src/*.o
	rm ./app
	rm ./test_app
 
test:  $(TESTOBJECTS)
	$(COMPILER)  $(FLAGS) $(TESTOBJECTS) -lgtest -o test_app
	./test_app
.PHONY: clean
