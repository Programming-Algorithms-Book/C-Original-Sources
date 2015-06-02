#include <stdio.h>
#define CDataType char
#define MAX 100

void findMajority(CDataType m[], unsigned size, CDataType *majority)
{ unsigned i, curCnt;
  char part = 0;
  do {
    for (curCnt = 0, i = 1; i < size; i += 2)
      if (m[i - 1] == m[i])
        m[curCnt++] = m[i];
    if (i == size) {
      m[curCnt++] = m[i - 1];
      part = 1;
    }
    else if (part)
      m[curCnt] = m[size - 2];
    else if (m[size - 2] == m[size - 1])
      m[curCnt] = m[size - 2];
    else
      curCnt--;
    size = curCnt;
  } while (size > 1);
  *majority = m[0];
}

int main(void) {
  CDataType majority;
  CDataType m[MAX] = "AAACCBBCCCBCC";
  findMajority(m, 13, &majority);
  printf("Мажорант: %c\n", majority);
  return 0;
}