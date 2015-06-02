#include <stdio.h>
#define MAX 10

typedef int data;
data stack[MAX];
int top;

void init(void) { top = 0; }

void push(data i)
{ if (MAX == top)
    fprintf(stderr, "Препълване на стека! \n");
  else
    stack[top++] = i;
}

data pop(void)
{ if (0 == top) {
    fprintf(stderr, "Стекът е празен! \n");
    return 0;
  }
  else
    return stack[--top];
}

int empty(void) { return (0 == top); } 

int main(void) {
  data p;
  init();

  /* Четат се цели числа от клавиатурата до прочитане на 0 и се включват в стека */
  scanf("%d", &p);
  while (0 != p) {
    push(p);
    scanf("%d", &p);
  };

  /* Изключват се последователно всички елементи от стека и се печатат. Това ще
   * доведе до отпечатване на първоначално въведената последователност в обратен ред
   */
  while (!empty()) printf("%d ", pop());
  printf("\n");
  return 0;
}
