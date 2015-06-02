#include <stdio.h>
#define MAXN 50
#define INFINITY (int)((1 << (sizeof(int)*8 - 1)) - 1)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct {
  long min, max;
  unsigned lenMin, lenMax;
} F[MAXN][MAXN];  /* Целеви функции Fmin() и Fmax() */

const unsigned n = 7;      /* Брой числа */
const long x[MAXN] = { 0, 9, -3, 8, 7, -8, 0, 7 }; /* Стойности на числата (без първото) */
char sign[MAXN] = { ' ', '+', '*', '*', '-', '+', '*', '-' }; /* Знаци между тях */

/* Извършва операцията */
long oper(long v1, char sign, long v2)
{ switch (sign) {
    case '+': return v1 + v2;
    case '-': return v1 - v2;
    case '*': return v1 * v2;
  }
  return 0;
}

/* Пресмята стойностите на целевата функция */
void calculate(unsigned beg, unsigned len)
{ unsigned i, beg2;
  long val1, val2, val3, val4, minValue, maxValue;
  if (beg > n)
	beg -= n;
  if (F[beg][len].min != INFINITY) /* Стойността вече е била сметната */
	return;
  if (1 == len) {
    F[beg][len].min = F[beg][len].max = x[beg];
    F[beg][len].lenMin = F[beg][len].lenMax = 0;
    return;
  }
  /* Стойността трябва да се пресметне */
  F[beg][len].min = INFINITY;
  F[beg][len].max = -INFINITY;
  for (i = 1; i < len; i++) {
    /* Пресмятане на всички стойности F[beg][i] и F[beg+i][len-i] */
    calculate(beg, i);
    if (beg + i > n)
	   beg2 = beg + i - n;
	else
	   beg2 = beg + i;
    calculate(beg2, len - i);
    val1 = oper(F[beg][i].min, sign[beg2 - 1], F[beg2][len - i].min);
    val2 = oper(F[beg][i].min, sign[beg2 - 1], F[beg2][len - i].max);
    val3 = oper(F[beg][i].max, sign[beg2 - 1], F[beg2][len - i].min);
    val4 = oper(F[beg][i].max, sign[beg2 - 1], F[beg2][len - i].max);
    /* Актуализиране на минималната стойност на F[beg][len] */
    minValue = MIN(val1, MIN(val2, MIN(val3, val4)));
    if (minValue < F[beg][len].min) {
      F[beg][len].min = minValue;
      F[beg][len].lenMin = i;
    }
    /* Актуализиране на максималната стойност на F[beg][len] */
    maxValue = MAX(val1, MAX(val2, MAX(val3, val4)));
    if (maxValue > F[beg][len].max) {
      F[beg][len].max = maxValue;
      F[beg][len].lenMax = i;
    }
  }
}

/* Извежда израз, за който се получава min/max */
void printMinMax(unsigned beg, unsigned len, char printMin)
{ unsigned i, beg2;
  if (beg > n)
	 beg -= n;
  if (1 == len)
    printf("%ld", x[beg]);
  else {
    if (len < n)
	  printf("(");
    i = printMin ? F[beg][len].lenMin : F[beg][len].lenMax;
	if ((beg2 = beg + i) > n)
	  beg2 -= n;
    printMinMax(beg, i, printMin); /* Рекурсия за лявата част на израза */
    printf("%c", sign[beg2 - 1]); /* Извеждане на операцията */
    printMinMax(beg2, len - i, printMin); /* Рекурсия за дясната част на израза */
    if (len < n)
	  printf(")");
  }
}

/* Намира максимума и минимума, както и как се получават */
void solve(void)
{ unsigned i, j;
  /* Инициализация */
  sign[0] = sign[n];
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
	  F[i][j].min = INFINITY;
  /* Пресмятане на стойностите на целевата функция */
  for (i = 1; i <= n; i++)
	 calculate(i, n);
}

/* Търси и извежда максимума и минимума */
void print(void)
{ unsigned i, minIndex, maxIndex;
  for (minIndex = 1, i = 2; i <= n; i++)
    if (F[i][n].min < F[minIndex][n].min)
	   minIndex = i;
  for (maxIndex = 1, i = 2; i <= n; i++)
    if (F[i][n].max > F[maxIndex][n].max)
	   maxIndex = i;
  printf("\nМинимална стойност: %d\n", F[minIndex][n].min);
  printMinMax(minIndex, n, 1);
  printf("\n\nМаксимална стойност: %d\n", F[maxIndex][n].max);
  printMinMax(maxIndex, n, 0);
}

int main(void) {
  solve();
  print();
  return 0;
}