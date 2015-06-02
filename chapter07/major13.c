#include <stdio.h>
#define CDataType char

char FindMajority(CDataType m[], unsigned size, CDataType *majority)
{ unsigned cnt, i;
  for (i = cnt = 0; i < size; i++) {
    if (0 == cnt) {
      *majority = m[i];
      cnt = 1;
    }
    else if (m[i] == *majority)
      cnt++;
    else
      cnt--;
  }
  if (cnt > 0) {
    for (i = cnt = 0; i < size; i++)
      if (m[i] == *majority)
        cnt++;
    return(cnt > size / 2);
  }
  return 0;
}

int main() {
  CDataType majority;
  if (FindMajority("AAACCBBCCCBCC", 13, &majority))
    printf("Мажорант: %c\n", majority);
  else
    printf("Няма мажорант.\n");
  return 0;
}