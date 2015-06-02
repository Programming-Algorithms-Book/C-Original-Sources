int a[n];
int mult(void)
{ unsigned int i;
  int s = 1;
  for (i = 0; i < n; i++) s *= a[i];
  return s;
}
