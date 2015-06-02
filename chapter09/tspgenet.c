#include <stdio.h>
#include <stdlib.h>

#define MAXN  100
/* трябва да бъде такова, че psize % 4 == 0 */
#define PSIZE 200

const unsigned long maxSteps = 1000;
const unsigned n = 20;   /* брой върхове на графа */
char A[MAXN][MAXN];      /* матрица на теглата */

/* създаване на произволен граф */
void initGraph(void)
{ unsigned i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) A[i][j] = random(100) + 1;
}

int population[PSIZE][MAXN]; /* цикли на популацията */
int result[PSIZE];

void randomCycle(int t)
{ char used[MAXN];
  unsigned i;
  for (i = 0; i < n; i++) used[i] = 0;
  for (i = 0; i < n; i++) {
    int p = random(n - i) + 1;
    int j = 0;
    while (p > 0) {
      while (used[j]) j++;
      p--; j++;
    }
    population[t][i] = j - 1;
    used[j - 1] = 1;
  }
}

int evaluate(int t)
{ int res = 0, i;
  for (i = 0; i < n - 1; i++)
    res += A[population[t][i]][population[t][i + 1]];
  return res + A[population[t][n - 1]][population[t][0]];
}

void combine(int p1, int p2, int q1, int q2)
{ int uq1[MAXN], uq2[MAXN], i, k, j;
  /* генерира наследници q1,q2 от родителите p1,p2 */
  k = random(n - 1) + 1;  /* разменя в точката k */
  for (i = 0; i < n; i++) {
    uq1[i] = 0;
    uq2[i] = 0;
  }

  for (i = 0; i < k; i++) {
    population[q1][i] = population[p1][i];
    uq1[population[p1][i]]++;
    population[q2][i] = population[p2][i];
    uq2[population[p2][i]]++;
  }

  for (i = k; i < n; i++) {
    if (uq1[population[p2][i]] == 0) {
      population[q1][i] = population[p2][i];
      uq1[population[p2][i]]++;
    }
    else {
      for (j = 0; uq1[j] != 0; j++);
      population[q1][i] = j;
      uq1[j]++;
    }

    if (uq2[population[p1][i]] == 0) {
      population[q2][i] = population[p1][i];
      uq2[population[p1][i]]++;
    }
    else {
      for (j = 0; uq2[j] != 0; j++);
      population[q2][i] = j;
      uq2[j]++;
    }
  }

  result[q1] = evaluate(q1);
  result[q2] = evaluate(q2);
}

void mutate(void) {
  unsigned i, k;
  /* ако се получат две поредни еднакви решения - едното "мутира" */
  for (i = 0; i < PSIZE - 1; i++) {
    int flag = 0;
    for (k = 0; k < n; k++)
      if (population[i][k] != population[i + 1][k]) {
        flag = 1;
        break;
      }

    if (!flag) {  /* цикъл i мутира */
      int p1 = random(n);
      int p2 = random(n);
      int swap = population[i][p1];
      population[i][p1] = population[i][p2];
      population[i][p2] = swap;
      result[i] = evaluate(i);
    }
  }
}

void reproduce(int s)
{ unsigned i, j, k, swap;

  /* замества най-неоптималните цикли, като комбинира произволни Ј
   * от първата половина
   */
  for (i = 0; i < (PSIZE-1)/2; i += 2) {
    /* randomCycle(i); */
    combine(i, i+1, PSIZE-i-1, PSIZE-i-2);
    result[i] = evaluate(i);
  }

  /* сортира популацията по оптималност */
  for (i = 0; i < PSIZE - 1; i++) {
    for (j = i + 1; j < PSIZE; j++) {
      if (result[j] < result[i]) {
        for (k = 0; k < n; k++) {
          swap = population[i][k];
          population[i][k] = population[j][k];
          population[j][k] = swap;
        }
        swap = result[i];
        result[i] = result[j];
        result[j] = swap;
      }
    }
  }

  if (s == maxSteps - 1) return;

  mutate();
}

int main(void) {
  unsigned i, j, s;
  int minRandom;
  initGraph();

  /* Решение с генериране на произволни цикли */  
  minRandom = n*101;
  for (s = 0; s < maxSteps; s++) {
    for (i = 0; i < PSIZE; i++) {
      randomCycle(i);
      result[i] = evaluate(i);
    }
    for (j=0; j< PSIZE; j++) if (result[j]<minRandom) minRandom = result[j];
  }
  printf("Оптимално решение, намерено при генериране на произволни %ld цикъла: %d\n",
           PSIZE*maxSteps, minRandom);

  /* Решение с Генетичен Аглоритъм със същия брой итерации */  
  for (s = 0; s < maxSteps; s++) reproduce(s);
  printf("Най-късите цикли, намерени от генетичния алгортиъм: \n");
  for (i = 10; i > 0; i--) printf("%d, ", result[i]);
  printf(" %d\n", result[0]);
  return 0;
}
