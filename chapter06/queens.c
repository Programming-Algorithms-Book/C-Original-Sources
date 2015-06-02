#include<stdio.h>
#include<stdlib.h>

/* Максимален размер на дъската */
#define MAXN 100

/* Размер на дъската */
const unsigned n = 13;

unsigned col[MAXN] , RD[2*MAXN - 1],
         LD[2*MAXN], queens [MAXN];

/* Отпечатва намереното разположение на цариците */
void printBoard()
{ unsigned i , j ;
  for (i = 0; i < n; i++) {
    printf("\n");
    for (j = 0; j < n; j++)
      if(queens[i] == j) printf("x ");
      else printf(". ");
  }
  printf("\n");
  exit(0);
}

/* Намира следваща позиция за поставяне на царица */
void generate(unsigned i)
{ if(i == n) printBoard();
  unsigned k;    
  for (k = 0; k <= n; k++) {
    if (col[k] && RD[i + k] && LD[n + i - k]) {
      col[k] = 0; RD[i + k] = 0; LD[n + i - k] = 0; queens[i] = k;
      generate(i + 1);
      col[k] = 1; RD[i + k] = 1; LD[n + i - k] = 1;
    }
  }
}

int main(void) {
  unsigned i;
  for (i = 0; i < n; i++) col[i] = 1;
  for (i = 0; i < (2*n - 1); i++) RD[i] = 1;
  for (i = 0; i < 2*n; i++) LD[i] = 1;
  generate(0);
  printf("Задачата няма решение! \n");
  return 0;
}
