#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <algorithm>

struct timeval start, end;

typedef struct {
  int weight;
  int profit;
} item;

/*
Description - Assigns two integers to each of the substrings of a comma-delimited string.
Parameters  - line (string): ought to be of the format "<int1>,<int2>"
            - first (int): int that will be assigned the value of int1
            - second (int): int that will be assigned the value of int2
*/
void commaDelimitedInts(const std::string& line, int& first, int& second){
  std::string weight;
  std::string profit;

  int i;
  for(i = 0; line[i] != ','; ++i) weight.push_back(line[i]);
  for(i = i+1; i < line.length(); ++i) profit.push_back(line[i]);

  first = std::stoi(weight);
  second = std::stoi(profit);
}

/*
Description - Compares two items based on their profit/weight ratio.
Parameters  - a (item): item to be compared
            - b (item): item to be compared
*/
int compareItems(const item& a, const item& b){
  return (int) ((float) a.profit/a.weight >= (float) b.profit/b.weight);
}

int main(int argc, char* argv[]){
  gettimeofday(&start, NULL);
  double t1 = start.tv_sec + (start.tv_usec/1000000.0);

  if(argc < 3){
    fprintf(stderr, "Must supply parameters: <input-file> <output-file>\n");
    exit(1);
  }

  std::ifstream in (argv[1]);
  std::string line;
  FILE* out = fopen(argv[2], "w");
  std::vector<item> items;
  int no_items, capacity;
  int line_no = 0;
  while(getline(in, line)){
    line_no++;
    if (line_no == 1){
      commaDelimitedInts(line, no_items, capacity);
    }else{
      int current_weight;
      int current_profit;
      commaDelimitedInts(line, current_weight, current_profit);
      item current = {current_weight, current_profit};
      items.push_back(current);
    }
  }

  std::sort(items.begin(), items.end(), compareItems);
  std::vector<item> final_items;
  int current_weight = 0;
  int current_profit = 0;

  int i = 0;
  for (i = 0; i < items.size(); ++i){
    if (capacity - current_weight < items[i].weight){
      break;
    }else if (capacity - current_weight == items[i].weight){
      i = items.size(); // effectively breaking, and stopping the creation of a fractional item
    }else{
      final_items.push_back(items[i]);
      current_profit += items[i].profit;
      current_weight += items[i].weight;
    }
  }

  bool need_fractional = i < items.size();
  int no_final_items = (need_fractional) ? final_items.size() + 1 : final_items.size();

  fprintf(out, "%d,%d,%d\n", no_items, current_profit, no_final_items);
  for (std::vector<item>::iterator j = final_items.begin(); j != final_items.end(); ++j)
    fprintf(out, "%d,%d\n", j->weight, j->profit);

  if (need_fractional) // fractional item
    fprintf(out, "%d,%f\n", (capacity - current_weight), ((float)(capacity - current_weight)/items[i].weight)*items[i].profit);

  gettimeofday(&end, NULL);
  double t2 = end.tv_sec + (end.tv_usec/1000000.0);
  fprintf(out, "%.6lf\n", t2-t1);

  in.close();
  fclose(out);
  return 0;
}
