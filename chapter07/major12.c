#include <stdio.h>
#define CDataType char

/* Променливи, функции и дефиниции за работа със стек */
#define STACK_SIZE  100
CDataType stack[STACK_SIZE];
unsigned stIndex;
void stackInit(void) { stIndex = 0; }
void stackPush(CDataType elem) { stack[stIndex++] = elem; }
CDataType stackPop(void) { return stack[--stIndex]; }
CDataType stackTop(void) { return stack[stIndex - 1]; }
char stackIsEmpty(void) { return 0 == stIndex; }

char findMajority(CDataType m[], unsigned size, CDataType *majority)
{ unsigned i, cnt;
  stackInit();
  for (stackPush(m[0]), i = 1; i < size; i++) {
    if (stackIsEmpty())
      stackPush(m[i]);
    else if (stackTop() == m[i])
      stackPush(m[i]);
    else
      stackPop();
  }
  if (stackIsEmpty()) return 0;
  for (*majority = stackPop(), i = cnt = 0; i < size; i++)
    if (m[i] == *majority)
      cnt++;
  return(cnt > size / 2);
}

int main() {
  CDataType majority;
  if (findMajority("AAACCBBCCCBCC", 13, &majority))
    printf("Мажорант: %c\n", majority);
  else
    printf("Няма мажорант.\n");
  return 0;
}