all:	GreedyKnapsack.o DynamicKnapsack.o
	g++ -std=c++11	-g GreedyKnapsack.o -o GreedyKnapsack
	g++ -std=c++11	-g DynamicKnapsack.o -o DynamicKnapsack

GreedyKnapsack.o:	GreedyKnapsack.cpp
	g++ -std=c++11 -g -c GreedyKnapsack.cpp

DynamicKnapsack.o:	DynamicKnapsack.cpp
	g++ -std=c++11 -g -c DynamicKnapsack.cpp

clean:
	rm -f *.o *.txt GreedyKnapsack DynamicKnapsack

again:	clean all