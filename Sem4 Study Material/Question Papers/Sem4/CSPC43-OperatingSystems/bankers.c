#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define P 5
#define R 4

void calculateNeed(int need[P][R], int maxm[P][R], int allot[P][R]) {
  for (int i = 0; i < P; i++)
    for (int j = 0; j < R; j++)
      need[i][j] = maxm[i][j] - allot[i][j];
}

void printMat(int mat[][R]) {
  for (int i = 0; i < R; i++)
    printf("%c ", 65 + i);
  printf("\n");
  for (int i = 0; i < P; i++) {
    for (int j = 0; j < R; j++)
      printf("%d ", mat[i][j]);
    printf("\n");
  }
}

void printTurn(int work[], int need[][R]) {
  printf("Currently Available :");
  for (int i = 0; i < R; i++)
    printf("%d ", work[i]);
  printf("\nCurrent Need : \n");

  printMat(need);
}

bool isSafe(int processes[], int avail[], int maxm[][R], int allot[][R]) {
  int need[P][R];
  calculateNeed(need, maxm, allot);
  bool finish[P] = {0};
  int safeSeq[P], work[R], count = 0;
  for (int i = 0; i < R; i++)
    work[i] = avail[i];
  while (count < P) {
    bool found = false, pass[R] = {1};
    for (int p = 0; p < P; p++) {
      if (finish[p] == 0) {
        int j;
        int failed = 0;
        for (j = 0; j < R; j++) {
          if (need[p][j] > work[j]) {
            pass[j] = 0;
            failed = 1;
          } else
            pass[j] = 1;
        }
        if (!failed) {
          printTurn(work, need);
          printf("Process Selected P%d\n\n", p);
          for (int k = 0; k < R; k++) {
            need[p][k] = 0;
            work[k] += allot[p][k];
          }
          safeSeq[count++] = p;
          finish[p] = 1;
          found = true;
        }
      }
    }
    if (found == false) {
      printTurn(work, need);
      printf("\nNo process's Need Can be satisfied with the remaining "
             "resources\n");
      printf("The following resources couldnt be satisfied : ");
      for (int i = 0; i < R; i++)
        if (!pass[i])
          printf("%c ", (char)(65 + i));
      printf("\nSystem is not in safe state\n");
      return false;
    }
  }
  printf("System is in safe state.\nSafe sequence is: ");
  for (int i = 0; i < P; i++)
    printf("P%d ", safeSeq[i]);
  printf("\n");
  return true;
}

int main() {
  int processes[] = {0, 1, 2, 3, 4};
  int avail[] = {0, 3, 0, 1};
  // int avail[] = {1, 0, 0, 2};

  int allot[P][R] = {
      {3, 0, 1, 4}, {2, 2, 1, 0}, {3, 1, 2, 1}, {0, 5, 1, 0}, {4, 2, 1, 2}};

  int maxm[P][R] = {
      {5, 1, 1, 7}, {3, 2, 1, 1}, {3, 3, 2, 1}, {4, 6, 1, 2}, {6, 3, 2, 5}};

  printf("\n");
  isSafe(processes, avail, maxm, allot);
  return 0;
}
