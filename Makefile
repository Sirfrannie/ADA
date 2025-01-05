CC=g++
CFLAGS= -std=c++20

lab1: 
	$(CC) divide_and_conquer/solution.cpp $(CFLAGS)
	./a.out
clean:
	rm -f *.o *.out

