#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define INFINITY (int)((1 << (sizeof(int)*8 - 1)) - 1)
#define N 12
#define M 54

struct CElem {
  int key;
  /* ............. 
    Някакви данни 
  ............. */
};

void init(struct CElem m[], unsigned n, unsigned mod1, unsigned mod2)
{ unsigned i;
  srand(time(NULL));
  m[0].key = rand() % mod1;
  for (i = 1; i < n; i++)
    m[i].key = m[i-1].key + (rand() % mod2);
}

int binarySearch(struct CElem m[], int left, int right, struct CElem elem)
{ int middle;
  do {
    middle = (left + right) / 2;
    if (m[middle].key < elem.key)
      left = middle + 1;
    else
      right = middle - 1;
  } while (left <= right);
  return right;
}

void binaryMerge(struct CElem a[], struct CElem b[], struct CElem c[], int n, int m)
{ int t, t2, cind, k, j;
  cind = n + m;
  while (n > 0 && m > 0) {
    if (m <= n) {
      t = (int) (log(n / m) / log(2));
      t2 = 1 << t;  /* T2 <-- 2^T */
      if (b[m - 1].key < a[n - t2].key) {
        /* Прехвърляне на a[n-t2-1],...,a[n] в изходната последователност */
        cind -= t2;
        n -= t2;
        for (j = 0; j < t2; j++)
          c[cind + j] = a[n + j];
      }
      else {
        k = binarySearch(a, n - t2, n - 1, b[m - 1]);
        for (j = 0; j < n - k - 1; j++)
          c[cind - n + k + j + 1] = a[k + j + 1];
        cind -= n - k - 1;
        n = k + 1;
        c[--cind] = b[--m];
      }
    }
    else {
      t = (int) (log(m / n) / log(2));
      t2 = 1 << t;  /* T2 <-- 2^T */
      if (a[n - 1].key < b[m - t2].key) {
        /* Прехвърляне на b[m-t2-1],...,b[m] в изходната последователност */
        cind -= t2;
        m -= t2;
        for (j = 0; j < t2; j++)
          c[cind + j] = b[m + j];
      }
      else {
        k = binarySearch(b, m - t2, m - 1, a[n - 1]);
        for (j = 0; j < m - k - 1; j++)
          c[cind - m + k + j + 1] = b[k + j + 1];
        cind -= m - k - 1;
        m = k + 1;
        c[--cind] = a[--n];
      }
    }
  }
  if (n == 0)
    for (j = 0; j < m; j++)
      c[j] = b[j];
  else
    for (j = 0; j < n; j++)
      c[j] = a[j];
}

void print(struct CElem m[], unsigned n)            /* Извежда ключовете на масива на екрана */
{ unsigned i;
  for (i = 0; i < n; i++)
    printf("%8d", m[i].key);
  printf("\n\n");
}

void check(struct CElem m[], unsigned n)            /* Проверява за възходящ ред */
{ unsigned i;
  for (i = 1; i < n; i++)
    assert(m[i-1].key <= m[i-1].key);
}

int main(void)
{ struct CElem a[N+1], b[M+1], c[N+M];
  init(a,N,200,20); init(b,M,200,20);
  printf("Преди сливането:\n"); print(a,N); print(b,M);
  binaryMerge(a, b, c, N, M);
  printf("След сливането:\n"); print(c,N+M); 
  return 0;
}