#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void checkNode(int currentItem, bool* currentset, int n, int C, int* weights, int* profits, bool* bestSet, int& maxProfit);

int main(int argc, char** argv){
  if(argc != 3){
    fprintf(stderr, "Usage: ./brute <input-file> <output-file>\n");
    exit(1);
  }

  struct timeval start, end;
  FILE* input = fopen(argv[1], "r");
  int n, C;
  fscanf(input, "%d,%d", &n, &C);
  int* weights = (int*)malloc(n * sizeof(int));
  int* profits = (int*)malloc(n * sizeof(int));
  for(int i = 0; i < n; ++i){
    fscanf(input, "%d,%d", &weights[i], &profits[i]);
  }
  fclose(input);

  bool* currentSet = (bool*)calloc(n, sizeof(bool));
  bool* bestSet = (bool*)calloc(n, sizeof(bool));
  int maxProfit = 0;
  int maxIncluded = 0;
  
  gettimeofday(&start, NULL);
  double t1 = start.tv_sec + (start.tv_usec/1000000.0);
  checkNode(0, currentSet, n, C, weights, profits, bestSet, maxProfit);
  gettimeofday(&end, NULL);
  double t2 = end.tv_sec + (end.tv_usec/1000000.0);



  for(int i = 0; i < n; ++i){
    if(bestSet[i]) maxIncluded++;
  }

  FILE* output = fopen(argv[2], "w");
  fprintf(output, "Elapsed time: %.6lfs\n", t2-t1);
  fprintf(output, "%d,%d,%d\n", n, maxProfit, maxIncluded);
  for(int i = 0; i < n; ++i){
    if(bestSet[i]) fprintf(output, "%d,%d\n", weights[i], profits[i]);
  }
  fclose(output);

  free(weights);
  free(profits);
  free(currentSet);
  free(bestSet);
}

void checkNode(int currentItem, bool* currentSet, int n, int C, int* weights, int* profits, bool* bestSet, int& maxProfit){
  if(currentItem == n){
    //leaf node in state space tree
    int totalWeight = 0;
    int totalProfit = 0;
    for(int i = 0; i < n; ++i){
      if(currentSet[i]){
	totalWeight += weights[i];
	totalProfit += profits[i];
      }
    }
    if(totalWeight <= C && totalProfit > maxProfit){
      maxProfit = totalProfit;
      memcpy(bestSet, currentSet, n*sizeof(bool));
    }
  }else{
    //not a leaf node
    currentSet[currentItem] = 0;
    checkNode(currentItem+1, currentSet, n, C, weights, profits, bestSet, maxProfit);
    currentSet[currentItem] = 1;
    checkNode(currentItem+1, currentSet, n, C, weights, profits, bestSet, maxProfit);
  }
}
