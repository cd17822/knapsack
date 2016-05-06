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
	for i in smallovercap.txt mediumovercap.txt largeovercap.txt smallundercap.txt mediumundercap.txt largeundercap.txt; do \
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
		echo "./brute $$i" >> data.txt; \
		./brute $$i brute.txt; \
		cat brute.txt >> data.txt; \
		echo "" >> data.txt; \
	done;


clean:
	rm -f *.o *.txt greedy dynamic brute back

again:	clean all