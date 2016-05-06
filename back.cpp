#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct{
  int weight;
  int profit;
} item;

//DFS of state space tree with backtracking
void checkNode(int currentItem, bool* currentset, int n, int C, item* items, bool* bestSet, int& maxProfit);

//sorts items by decreasing profit/weight ratio (for qsort)
int compare(const void * a, const void * b){
  item* first = (item*)a;
  float ratioA = ((float)first->profit)/first->weight;
  item* second = (item*)b;
  float ratioB = ((float)second->profit)/second->weight;
  if(ratioA>ratioB)return -1;
  return 1;
}

//solves fractional knapsack subproblems to find bounds
//assumes items are sorted by increasing profit/weight ratio
float KWF(int i, int weight, item* items, int C, int n){
  float rv = 0;
  while(weight < C && i < n){
    if(weight + items[i].weight <= C){
      weight += items[i].weight;
      rv += items[i].profit;
    }else{
      rv += (float)(C - weight) * items[i].profit / items[i].weight;
      weight = C;
    }
    ++i;
  }
  return rv;
}

int main(int argc, char** argv){
  struct timeval start, end;
  gettimeofday(&start, NULL);
  double t1 = start.tv_sec + (start.tv_usec/1000000.0);
  
  if(argc != 3){
    fprintf(stderr, "Usage: ./back <input-file> <output-file>\n");
    exit(1);
  }


  FILE* input = fopen(argv[1], "r");
  int n, C;
  fscanf(input, "%d,%d", &n, &C);
  item* items = (item*)malloc(n * sizeof(item));
  for(int i = 0; i < n; ++i){
    fscanf(input, "%d,%d", &items[i].weight, &items[i].profit);
  }
  fclose(input);

  qsort(items, n, sizeof(item), compare);

  bool* currentSet = (bool*)calloc(n, sizeof(bool));
  bool* bestSet = (bool*)calloc(n, sizeof(bool));
  int maxProfit = 0;
  int maxIncluded = 0;
  

  checkNode(0, currentSet, n, C, items, bestSet, maxProfit);




  for(int i = 0; i < n; ++i){
    if(bestSet[i]) maxIncluded++;
  }

  gettimeofday(&end, NULL);
  double t2 = end.tv_sec + (end.tv_usec/1000000.0);

  FILE* output = fopen(argv[2], "w");

  /*printf(output, "%d,%d,%d\n", n, maxProfit, maxIncluded);
  for(int i = 0; i < n; ++i){
    if(bestSet[i]) fprintf(output, "%d,%d\n", items[i].weight, items[i].profit);
  }*/
  fprintf(output, "%.6lf\n", t2-t1);
  fclose(output);

  free(items);
  free(currentSet);
  free(bestSet);
}

void checkNode(int currentItem, bool* currentSet, int n, int C, item* items, bool* bestSet, int& maxProfit){
  int totalWeight = 0;
  int totalProfit = 0;
  for(int i = 0; i < n; ++i){
    if(currentSet[i]){
      totalWeight += items[i].weight;
      totalProfit += items[i].profit;
    }
  }
  if(totalWeight <= C && totalProfit > maxProfit){
      maxProfit = totalProfit;
      memcpy(bestSet, currentSet, n*sizeof(bool));
  }
  
  if(currentItem == n-1) return;
  if(totalWeight > C) return;
  float bound = totalProfit + KWF(currentItem, totalWeight, items, C, n);
  if(bound < maxProfit) return;
    
  //node is promising
  currentSet[currentItem] = 1;
  checkNode(currentItem+1, currentSet, n, C, items, bestSet, maxProfit);
  currentSet[currentItem] = 0;
  checkNode(currentItem+1, currentSet, n, C, items, bestSet, maxProfit);
 
}
