#modify this makefile so that it will work for this new assignment
CC=g++
//DEPS = starter.h
//^^There is no starter.h in this assignment

all: main.o
	$(CC) -std=c++11 main.o
	//Got rid of starter.o so that main.o can be linked to the default executable, a.out

	//bowling: starter.o $(DEPS)
	//	$(CC) -c -std=c++11 starter.cpp
	//^^ starter.cpp is from old assignment, not needed here

main.o: main.cpp
	$(CC) -c -std=c++11 main.cpp
	// creates file called main.o --> Makefile target should also be named main.o

clean:
	rm *.o *.out
