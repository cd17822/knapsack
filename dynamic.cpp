#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>

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

  int matrix[no_items+1][capacity+1];
  for (int i = 0; i < no_items+1; ++i)
    matrix[i][0] = 0; //init first col to 0
  for (int i = 1; i < capacity+1; ++i)
    matrix[0][i] = 0; //init first row to 0

  for (int i = 1; i < no_items+1; ++i) {
    for (int j = 1; j < capacity+1; ++j) {
      if (items[i-1].weight <= j){
        if (matrix[i-1][j-items[i-1].weight]+items[i-1].profit > matrix[i-1][j]){
          matrix[i][j] = matrix[i-1][j-items[i-1].weight]+items[i-1].profit;
        }else{
          matrix[i][j] = matrix[i-1][j];
        }
      }else{
        matrix[i][j] = matrix[i-1][j];
      }
    }
  }

  int i = no_items;
  int c = capacity;
  std::vector<item> final_items;
  while(i > 0 && c > 0){
    if (matrix[i][c] != matrix[i-1][c]){
      final_items.push_back(items[i-1]);
      c -= items[i-1].weight;
    }
    i--;
  }

  /*fprintf(out, "%d,%d,%lu\n", no_items, matrix[no_items][capacity], final_items.size());
  for (std::vector<item>::iterator j = final_items.begin(); j != final_items.end(); ++j)
    fprintf(out, "%d,%d\n", j->weight, j->profit);
  */
  gettimeofday(&end, NULL);
  double t2 = end.tv_sec + (end.tv_usec/1000000.0);
  fprintf(out, "%.6lf\n", t2-t1);

  in.close();
  fclose(out);
  return 0;
}
