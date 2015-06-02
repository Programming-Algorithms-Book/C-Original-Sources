#include <stdio.h>
#define MAX_NUM 127
#define CDataType unsigned char
CDataType cnt[MAX_NUM + 1];

char findMajority(CDataType m[], unsigned size, CDataType *majority)
{ unsigned i, j, size2 = size / 2;
  /* Инициализация */
  for (i = 0; i < MAX_NUM; i++)
    cnt[i] = 0;
  /* Броене */
  for (j = 0; j < size; j++)
    cnt[m[j]]++;
  /* Проверка за мажорант */
  for (i = 0; i < MAX_NUM; i++)
    if (cnt[i] > size2) {
      *majority = i;
      return 1;
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