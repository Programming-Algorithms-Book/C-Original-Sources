#include <stdio.h>

/* намалява p/q, докато p стане равно на 1 */
void cancel(unsigned long *p, unsigned long *q) {
  if (0 == *q % *p) {
    *q /= *p;
    *p = 1;
  }
}

void solve(unsigned long p, unsigned long q) {
  printf("%ld/%ld = ", p, q);
  cancel(&p, &q);

  while (p > 1) {
    /* намира максималната дроб 1/r, 1/r<=p/q */
    unsigned long r;
    r = (q + p) / p;
    printf("%d/%ld + ", 1, r);

    /* изчислява p/q - 1/r */
    p = p * r - q;
    q = q * r;
    cancel(&p, &q);
  }
  (p > 0) ? printf("%ld/%ld\n", p, q) : printf("\n");
}

int main(void) {
  solve(3, 7);
  return 0;
}
