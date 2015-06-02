#include <stdio.h>
#include <math.h>
#define log2(x) log(x)/log(2)
#define MAX 100

const double p[MAX] = {0.2, 0.2, 0.15, 0.15, 0.10, 0.10, 0.05, 0.05};
const unsigned n = 8; /* Брой вероятности */

/* Пресмята ентропията на източника */
double calcEntropy(const double *p, const unsigned n) 
{ unsigned i;
  double sum;
  for (sum = i = 0; i < n; i++)
    sum -= p[i]*log2(p[i]);
  return sum;
}

/* Пресмята цената на кода */
double calcValue(const double *p, const unsigned *l, const unsigned n)
{ unsigned i;
  double sum;
  for (sum = i = 0; i < n; i++)
    sum += p[i]*l[i];
  return sum;
}

/* Пресмята дължините на кодовете на отделните букви */
void calcLengths(unsigned *l, const double *p, const unsigned n)
{ unsigned i;
  for (i = 0; i < n; i++)
    l[i] = (unsigned) ceil(log2(1.0 / p[i]));
}

int main(void) {
  unsigned i;
  double entr;
  unsigned l[MAX];

  printf("\n\nИзточник, зададен с честоти на срещане: ");
  for (i = 0; i < n; i++)
    printf("%2.2lf ",p[i]);

  entr = calcEntropy(p,n);
  printf("\nЕнтропия на източника: %8.5lf",entr);
  printf("\nТеоретична цена на кода: %8.5lf",entr + 1);
  
  calcLengths(l,p,n);
  printf("\nДължини на кодовете: ");
  for (i = 0; i < n; i++)
    printf("%u ",l[i]);

  printf("\nЦена на кода при горните дължини: %2.2lf",calcValue(p,l,n));
  return 0;
}