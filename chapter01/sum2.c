int a[n];

int sum(void)
{ unsigned int i;
  int s = 0;
  for (i = 0; i < n; i++) s += a[i];
  return s;
}
