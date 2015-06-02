#include <stdio.h>
#include <stdlib.h>
#define CDataType char

void findMajority(CDataType m[], unsigned size, CDataType *majority)
{ unsigned i, curCnt;
  unsigned *cnt = (unsigned *) malloc(size * sizeof(*cnt));
  for (i = 0; i < size; i++) cnt[i] = 1;
  do {
    for (curCnt = 0, i = 1; i < size; i += 2) {
      if (m[i - 1] == m[i]) {
        cnt[curCnt] = cnt[i - 1] + cnt[i];
        m[curCnt++] = m[i];
      }
      else if (cnt[i] > cnt[i - 1]) {
        cnt[curCnt] = cnt[i] - cnt[i - 1];
        m[curCnt++] = m[i];
      }
      else if (cnt[i] < cnt[i - 1]) {
        cnt[curCnt] = cnt[i - 1] - cnt[i];
        m[curCnt++] = m[i - 1];
      }
    }
    if (size & 1) {
      cnt[curCnt] = cnt[i - 1];
      m[curCnt++] = m[i - 1];
    }
    size = curCnt;
  } while (size > 1);
  free(cnt);
  *majority = m[0];
}

int main() {
  CDataType m[14] = "AAACCBBCCCBCC";
  CDataType majority;
  findMajority(m, 13, &majority);
  printf("Мажорант: %c\n", majority);
  return 0;
}