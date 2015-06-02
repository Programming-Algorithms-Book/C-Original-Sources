#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S 107           /* стъпка на увеличаване при колизия */
unsigned long n = 32;   /* начален размер на хеш-таблицата */

struct singleWord {
  char *word;           /* ключ - символен низ */
  unsigned long freq;   /* честота на срещане на думата */
} *ht;

unsigned long count;

/* Хеш-функция за символен низ */
unsigned long hashFunction(const char *key)
{ unsigned long result = 0;
  while (*key)
    result += result + (unsigned char) *key++;
  return result & (n - 1);
}

/* Инициализиране на хеш-таблицата */
void initHashtable(void)
{ unsigned long i;
  count = 0;
  ht = (struct singleWord *) malloc(sizeof(*ht)*n);
  for (i = 0; i < n; i++)
    ht[i].word = NULL;
}

/* Търсене в хеш-таблицата: връща 1 при успех, и 0 – иначе */
/* При успех: *ind съдържа индекса на намерения елемент */
/* При неуспех: свободна позиция, където може да бъде вмъкнат */
char get(const char *key, unsigned long *ind)
{ unsigned long k;
  *ind = hashFunction(key);
  k = *ind;
  do {
    if (NULL == ht[*ind].word) return 0;
    if (0 == strcmp(key, ht[*ind].word)) return 1;
    *ind = (*ind + S) & (n - 1);
  } while (*ind != k);
  return 0;
}

/* Разширяване на хеш-таблицата */
void resize(void)
{ unsigned long ind, hashInd;
  struct singleWord *oldHashTable;

  /* 1. Запазване на указател към хеш-таблицата */
  oldHashTable = ht;

  /* 2. Двойно разширяване */
  n <<= 1;

  /* 3. Заделяне на памет за новата хеш-таблица */
  ht = (struct singleWord *) malloc(sizeof(*ht)*n);
  for (ind = 0; ind < n; ind++)
    ht[ind].word = NULL;

  /* 4. Преместване на записите в новата хеш-таблица */
  for (ind = 0; ind < (n >> 1); ind++) {
    if (oldHashTable[ind].word != NULL) {
      /* Премества записа на новото място */
      if (!get(oldHashTable[ind].word, &hashInd))
        ht[hashInd] = oldHashTable[ind];
      else
        printf("Грешка при разширяване на хеш-таблицата!\n");
    }
  }

  /* 5. Освобождаване на старата памет */
  free(oldHashTable);
}

/* Добавяне на елемент в хеш-таблицата */
void put(char *key)
{ unsigned long ind;
  if (!get(key, &ind)) { /* Думата не е в хеш-таблицата */
    ht[ind].word = strdup(key);
    ht[ind].freq = 1;
    if (++count > ((unsigned long) n * 0.9)) resize();
  }
  else
    ht[ind].freq++;
}

/* Отпечатване на хеш-таблица */
void printAll(void)
{ unsigned long ind;
  for (ind = 0; ind < n; ind++)
    if (ht[ind].word != NULL)
	  printf("%s %ld \n", ht[ind].word, ht[ind].freq);
}

/* Унищожаване на хеш-таблица */
void destroy(void)
{ unsigned long ind;
  for (ind = 0; ind < n; ind++)
    if (ht[ind].word != NULL) free(ht[ind].word);
  free(ht);
}

int main(void) {
  unsigned long find;
  initHashtable();

  put("reload");
  put("crush tour");
  put("room service");
  put("load");
  put("reload");
  put("reload");

  printAll();

  if (get("reload", &find))
    printf("Честота на думата 'reload': %d \n", ht[find].freq);
  else
	printf("Думата 'reload' липсва!");

  if (get("download", &find))
    printf("Честота на думата 'download': %d \n", ht[find].freq);
  else
	printf("Думата 'download' липсва!");

  destroy();
  return 0;
}
