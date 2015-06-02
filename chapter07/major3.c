#include <stdio.h>
#define CDataType char

char findMajority(CDataType m[], unsigned size, CDataType *majority)
{ unsigned i, j, cnt, size2 = size / 2;
  for (i = 0; i <= size / 2; i++) {
    for (cnt = 0, j = i; j < size; j++)
      if (cnt + size - j <= size2)
        break;
      else if (m[i] == m[j])
        cnt++;
    if (cnt > size2) {
      *majority = m[i];
      return 1;
    }
  }
  return 0;
}

int main(void) {
  CDataType majority;
  if (findMajority("AAACCBBCCCBCC", 13, &majority))
    printf("Мажорант: %c\n", majority);
  else
    printf("Няма мажорант.\n");
  return 0;
}