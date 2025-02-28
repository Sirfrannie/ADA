.PHONY : all heuristic
CC=gcc
CFLAGS= -std=c++20 -lstdc++

heuristic: heuristic/main.cpp heuristic/heuristic_methods.hpp
	$(CC) -o a.out heuristic/main.cpp heuristic/heuristic_methods.hpp $(CFLAGS)
	./a.out

dc: 
	$(CC) divide_and_conquer/solution.cpp $(CFLAGS)
	./a.out

dijkstra:
	$(CC) MST_SP/dijkstra.cpp $(CFLAGS)
	./a.out

prim:
	$(CC) MST_SP/prim.cpp $(CFLAGS)
	./a.out

kruskal:
	$(CC) MST_SP/kruskal.cpp $(CFLAGS)
	./a.out

clean:
	rm -f *.o *.out

