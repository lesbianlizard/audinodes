SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
FLAGS=-Wall -g
LIBS=-lsndfile
BINNAME=audinodes

prog: $(OBJ)
	g++ $(OBJ) $(FLAGS) $(LIBS) -o $(BINNAME)

.cpp.o: $<
	g++ $(FLAGS) $(LIBS) -I. -c $<

.PHONY: clean
clean:
	rm *.o $(BINNAME)
