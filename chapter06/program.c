#include <stdio.h>

/* Максимален брой учители */
#define MAXT 100
/* Максимален брой класове */
#define MAXC 100

/* Брой учители */
const unsigned t = 3;
/* Брой класове */
const unsigned c = 4;
unsigned cl[MAXC][MAXT] = {
  { 5, 5, 5 }, /* информация за клас 1 */
  { 5, 5, 5 },
  { 5, 0, 0 },
  { 0, 0, 5 }  /* информация за клас C */
};

const unsigned MAX_VALUE = 20000;

char usedC[100][MAXC];
unsigned teach[MAXT], minimal;

void generate(unsigned teacher, unsigned level, unsigned mX, unsigned totalHours)
{ unsigned i, j;
  if (totalHours >= minimal) return;
  if (teacher == t) {
    unsigned min = MAX_VALUE;
    for (i = 0; i < c; i++)
      for (j = 0; j < t; j++)
        if (cl[i][j] < min && 0 != cl[i][j]) min = cl[i][j];
    if (min == MAX_VALUE) {
      if (totalHours < minimal) minimal = totalHours;
    }
    else {
      generate(0, level + 1, min, totalHours + min);
    }
    return;
  }

  /* определя клас за учителя teacher, с който той да проведе min часа */
  for (i = 0; i < c; i++) {
    if (cl[i][teacher] > 0 && !usedC[level][i]) {
      cl[i][teacher] -= mX;
      usedC[level][i] = 1;
      generate(teacher + 1, level, mX, totalHours);
      usedC[level][i] = 0;  /* връщане */
      cl[i][teacher] += mX;
    }
  }

  /* Ако не е намерено присвояване за учителя, това означава, че не са му останали
   * часове за преподаване */
  if (i == c) generate(teacher + 1, level, mX, totalHours);
}

int main(void) {
  unsigned i, j;
  for (i = 0; i < 100; i++)
    for (j = 0; j < c; j++) usedC[i][j] = 0;
  minimal = MAX_VALUE;
  generate(t, 0, 0, 0);
  printf("Минималното разписание е с продължителност %u часа.\n", minimal);
  return 0;
}
