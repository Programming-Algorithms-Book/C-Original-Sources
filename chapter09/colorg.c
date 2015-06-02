#include <stdio.h>

#define MAXN 200

const int n = 6;
const char A[MAXN][MAXN] = {
  { 0, 1, 0, 0, 0, 0 },
  { 1, 0, 1, 0, 0, 1 },
  { 0, 1, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0, 1 },
  { 0, 0, 1, 0, 0, 0 },
  { 0, 1, 0, 1, 0, 0 }
};

int color[MAXN];

/* върховете се разглеждат в произволен, а не сортиран по степента им ред */
void solve1(void)
{ int flag, i, j;
  for (i = 0; i < n; i++) { /* оцветява i-тия връх с най-малкият възможен цвят */
    int c = 0;
    do {
      c++;
      flag = 1;
      for (j = 0; j < n; j++)
        if (A[i][j] && color[j] == c) {
          flag = 0;
          break;
        }
    } while (!flag);
    color[i] = c;
  }
}

void solve2(void)
{ int c = 0, cn = 0, i, j;
  /* оцветява върхове само с първия цвят, докато е възможно, след това само с
   * втория и т.н., докато всички върхове бъдат оцветени
   */
  while (cn < n) {
    c++;
    for (i = 0; i < n; i++) {
      if (!color[i]) {
        int flag = 1;
        for (j = 0; j < n; j++)
          if (A[i][j] && color[j] == c) {
            flag = 0;
            break;
          }

        if (flag) {
          color[i] = c;
          cn++;
        }
      }
    }
  }
}

void showColor(void)
{ int i;
  for (i = 0; i < n; i++) printf("%d-%d; ", i + 1, color[i]);
  printf("\n");
}

int main(void) {
  int i;
  printf("Оцветяване на върховете по алгоритъм 1: \n");
  for (i = 0; i < n; i++) color[i] = 0;
  solve1();
  showColor();
  printf("Оцветяване на върховете по алгоритъм 2: \n");
  for (i = 0; i < n; i++) color[i] = 0;
  solve2();
  showColor();
  return 0;
}
