#include <stdio.h>
#define CDataType char

unsigned count(CDataType m[], unsigned left, unsigned right, CDataType candidate)
{ unsigned cnt;
  for (cnt = 0; left <= right; left++)
    if (m[left] == candidate)
      cnt++;
  return cnt;
}

char findMajority(CDataType m[], unsigned left, unsigned right, CDataType *majority)
{ unsigned mid;
  if (left == right) {
    *majority = m[left];
    return 1;
  }
  mid = (left + right) / 2;
  if (findMajority(m, left, mid, majority))
    if (count(m, left, right, *majority) > (right - left + 1) / 2)
      return 1;
  if (findMajority(m, mid + 1, right, majority))
    if (count(m, left, right, *majority) > (right - left + 1) / 2)
      return 1;
  return 0;
}

int main(void) {
  CDataType majority;
  if (findMajority("AAACCBBCCCBCC", 0, 12, &majority))
    printf("Мажорант: %c\n", majority);
  else
    printf("Няма мажорант.\n");
  return 0;
}