float power(float x, unsigned y)
{ float res = x;
  unsigned i;
  for (i = 1; i < y; i++) res *= x;
  return res;
}
