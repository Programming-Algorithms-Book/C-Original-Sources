// GC-to tuk zasira qko - zashtoto funkciite mi sa ednoredovi
#include <stdio.h>

typedef int data;
data stack[10];
int top;

void init(void) { top = 0; }
void push(data i) { stack[top++] = i; }
data pop(void) { return stack[--top]; }
int empty(void) { return(top == 0); }

int main(void) { 
  /* ... */
  return 0;
}
