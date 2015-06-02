#include <stdio.h>
#define CDataType char

void findMajority(CDataType m[], unsigned size, CDataType *majority)
{ unsigned i, curCnt;
  do {
    for (curCnt = 0, i = 1; i < size; i += 2)
      if (m[i - 1] == m[i])
        m[curCnt++] = m[i];
    if (size & 1)
      *majority = m[size - 1];
    size = curCnt;
  } while (size > 0);
}

int main(void) {
  CDataType m[14] = "AAACCBBCCCBCC";
  CDataType majority;
  findMajority(m, 13, &majority);
  printf("Мажорант: %c\n", majority);
  return 0;
}