all:	greedy dynamic brute back

greedy: greedy.o
	g++ greedy.o -o greedy

greedy.o: greedy.cpp
	g++ -std=c++11 -c greedy.cpp -o greedy.o

dynamic: dynamic.o
	g++ dynamic.o -o dynamic

dynamic.o: dynamic.cpp
	g++ -std=c++11 -c dynamic.cpp -o dynamic.o

back: back.o
	g++ back.o -o back

back.o: back.cpp
	g++ -c back.cpp -o back.o

brute: brute.o
	g++ brute.o -o brute

brute.o: brute.cpp
	g++ -c brute.cpp -o brute.o

test: all
	python knapsack.py;
	> data.txt;
	for i in 10undercap.txt 10overcap.txt 20undercap.txt 20overcap.txt 30undercap.txt 30overcap.txt 40undercap.txt 40overcap.txt 50undercap.txt 50overcap.txt 60undercap.txt 60overcap.txt 70undercap.txt 70overcap.txt 80undercap.txt 80overcap.txt 90undercap.txt 90overcap.txt 100undercap.txt 100overcap.txt; do \
		echo "./back $$i" >> data.txt; \
		./back $$i back.txt; \
		cat back.txt >> data.txt; \
		echo "" >> data.txt; \
		echo "./dynamic $$i" >> data.txt; \
		./dynamic $$i dynamic.txt; \
		cat dynamic.txt >> data.txt; \
		echo "" >> data.txt; \
		echo "./greedy $$i" >> data.txt; \
		./greedy $$i greedy.txt; \
		cat greedy.txt >> data.txt; \
		echo "" >> data.txt; \
	done;


clean:
	rm -f *.o *.txt greedy dynamic brute back

again:	clean all