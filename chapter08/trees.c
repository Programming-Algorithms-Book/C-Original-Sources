#include <stdio.h>
#include <string.h>
#define MAX 100

struct ST {
  unsigned len;  /* Дължина на максималната ненамаляваща подредица, завършваща в i */
  unsigned back; /* Индекс на предишния елемент в макс. редица */
  unsigned long sum; /* Сума на елементите на максималната редица */
} max1[MAX], max2[MAX];
unsigned x2[MAX], rez[MAX];
unsigned top, bestLen, bestSum;

const unsigned n = 9;  /* Брой крайпътни дървета */
const unsigned x[MAX] = {0,10,20,15,40,5,4,300,2,1}; /* Височини на дърветата */

/* Търси нарастваща редица */
void findIncSequence(struct ST max[], const unsigned x[])
{ unsigned i, j;
  /* Основен цикъл */
  for (i = 1; i <= n; i++)
    for (j = max[i].len = max[i].sum = 0; j < i; j++)
      if (x[j] <= x[i])
        if ((max[j].len + 1 > max[i].len)
           || ((max[j].len + 1 == max[i].len) && (max[j].sum + x[i] > max[i].sum)) ) {
          max[i].back = j;
          max[i].len = max[j].len + 1;
          max[i].sum = max[j].sum + x[i];
        }
}

/* Построява обърнато копие на редицата */
void reverse(unsigned x2[], const unsigned x[])
{ unsigned i;
  for (i = 1; i <= n; i++)
	x2[i] = x[n-i+1];
}

/* Намира търсената редица */
void solve(void) {
  unsigned i;
  /* стъпка (1) */
  findIncSequence(max1, x);
  /* стъпка (2) */
  reverse(x2,x);
  findIncSequence(max2, x2);
  /* стъпка (3) */
  for (bestLen = bestSum = 0, i = 1; i <= n; i++) {
    if (((max1[i].len + max2[n-i+1].len > bestLen))
        || ((max1[i].len + max2[n-i+1].len == bestLen)
            && (max1[i].sum + max2[n-i+1].sum > bestSum))) {
      bestLen = max1[i].len + max2[n-i+1].len;
      bestSum = max1[i].sum + max2[n-i+1].sum; /* Must be decreased by 1 */
      top = i;
    }
  }
}

/* Построява търсената редица */
void buildSequence(void)
{ unsigned t, len, l;
  /* Построяване на нарастващата част на редицата */
  for (l = max1[t = top].len, len = 0; t != 0; t = max1[t].back)
    rez[l-len++] = x[t];
  /* Построяване на намаляващата част на редицата */
  for (t = max2[n-top+1].back; t != 0; t = max2[t].back)
    rez[++len] = x2[t];
}

/* Извежда резултата на екрана */
void print(void)
{ unsigned i;
  printf("\nМаксимален брой дървета, които могат да се запазят: %u\n", bestLen-1);
  for (i = 1; i < bestLen; i++)
	printf("%u ", rez[i]);
  printf("\n");
}

int main(void) {
  solve();
  buildSequence();
  print();
  return 0;
}