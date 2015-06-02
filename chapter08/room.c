#include <stdio.h>
#define MAXN  5000  /* Максимален брой заявки */
#define MAXD  365   /* Максимален брой дни */
struct TZ { unsigned b, e; };

struct { unsigned cntBlue, cntRed; } B[MAXD], R[MAXD];

const unsigned n = 2; /* Брой сини заявки */
const unsigned m = 4; /* Брой червени заявки */
struct TZ blueOrders[MAXN] = { {1,5}, {12,20} };
struct TZ redOrders[MAXN] = { {2,10}, {6,11}, {15,25}, {26,30} };

/* Сортира заявките */
void sort(struct TZ Z[], const unsigned count)
{ unsigned i, j;
  struct TZ swp;
  for (i = 0; i < count; i++)
    for (j = i + 1; j < count; j++)
      if (Z[i].e > Z[j].e) {
        swp = Z[i];
		Z[i] = Z[j];
		Z[j] = swp;
      }
}

/* Решава задачата с динамично оптимиране */
void solveDynamic(void)
{ unsigned d, bb, be, blueIndex, redIndex;
  /* Инициализация */
  B[0].cntBlue = B[0].cntRed = R[0].cntBlue = R[0].cntRed = 0; 
  blueIndex = redIndex = 1;
  /* Пресмятане на B[1..MAXD], R[1..MAXD] */
  for (d = 1; d <= MAXD; d++) {
    /* Пресмятане на B[d] */
    B[d] = B[d - 1];
    for (blueIndex = 0; blueIndex < n; blueIndex++) {
      if (blueOrders[blueIndex].e > d)
        break;
      else {
        bb = blueOrders[blueIndex].b;
        be = blueOrders[blueIndex].e;
        if (R[bb-1].cntBlue + R[bb-1].cntRed + (be-bb+1) > B[d].cntBlue + B[d].cntRed) {
          B[d].cntBlue = R[bb - 1].cntBlue + (be - bb + 1);
          B[d].cntRed = R[bb - 1].cntRed + 0;
        }
      }
    }
    /* Пресмятане на R[d]: аналогично на B[d] */
    R[d] = R[d - 1];
    for (redIndex = 0; redIndex < m; redIndex++) {
      if (redOrders[redIndex].e > d)
        break;
      else {
        bb = redOrders[redIndex].b;
        be = redOrders[redIndex].e;
        if (B[bb-1].cntBlue + B[bb-1].cntRed + (be-bb+1) > R[d].cntBlue + R[d].cntRed) {
          R[d].cntBlue = B[bb - 1].cntBlue;
          R[d].cntRed = B[bb - 1].cntRed + (be - bb + 1);
        }
      }
    }
  }
}

/* Извежда резултата на екрана */
void printResult(void)
{ if (B[MAXD].cntBlue + B[MAXD].cntRed > R[MAXD].cntBlue + R[MAXD].cntRed) {
    printf("\nЗаетост на залата (дни): %u", B[MAXD].cntBlue + B[MAXD].cntRed);
    printf("\nБрой дни за червените: %u", B[MAXD].cntRed);
    printf("\nБрой дни за сините: %u", B[MAXD].cntBlue);
  }
  else {
    printf("\nЗаетост на залата (дни): %u", R[MAXD].cntBlue + R[MAXD].cntRed);
    printf("\nБрой дни за червените: %u", R[MAXD].cntRed);
    printf("\nБрой дни за сините: %u", R[MAXD].cntBlue);
  }
}

int main(void) {
  sort(blueOrders, n);
  sort(redOrders, m);
  solveDynamic();
  printResult();
  return 0;
}