#define EPS 0.0001
#define MAX_LEN 100

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

char getChar(char n) /* Връща символа, съответстващ на n */
{  return (n < 10) ? n + '0' : n + 'A' - 10; }

char getValue(char c) /* Връща стойността на символа c */
{  return (c >= '0' && c <= '9') ? c - '0' : c - 'A' + 10; }

void reverse(char *pch)
{ char *pEnd;
  for (pEnd = pch + strlen(pch) - 1; pch < pEnd; pch++, pEnd--) {
	char c = *pch;
	*pch = *pEnd;
	*pEnd = c;
  }
}

void convert(char *rslt, unsigned long n, unsigned char base)
/* Преобразува цялото десетично число n (n >= 0) в бройна система с основа base */
{ char *saveRslt = rslt;
  while (n > 0) {
	*rslt++ = getChar((char)(n % base));
	n /= base;
  }
  *rslt = '\0';
  reverse(saveRslt);
}

void convertLessThan1(char *rslt, double n, unsigned char base, unsigned char cnt)
/* Преобразува десетичното число 0 <= n < 1 в бройна система с основа base
   с не повече от cnt на брой цифри след десетичната запетая */
{ 
  while (cnt--) {
    /* Дали не сме получили 0? */
	if (fabs(n) < EPS) break;
	/* Получаване на следващата цифра */
    n *= base;
	*rslt++ = getChar((char)(int)floor(n));
    n -= floor(n);
  }
  *rslt = '\0';
}

void convertReal(char *rslt, double n, unsigned char base, unsigned char cnt)
  /* Преобразува десетичното реално число n в бройна система с основа base */
{ double integer, fraction;

  /* Намиране на знака */
  if (n < 0) {
	*rslt++ = '-';
	n = -n;
  }

  /* Разбиване на цяла и дробна част */
  fraction = modf(n, &integer); 

  /* Конвертиране на цялата част */
  convert(rslt, (unsigned long)integer, base);

  /* Поставяне на десетична точка */
  if ('\0' == *rslt)
	*rslt++ = '0';
  else
	rslt += strlen(rslt);
  *rslt++ = '.';

  /* Конвертиране на дробната част */
  convertLessThan1(rslt, fraction, base, cnt);
  if ('\0' == *rslt) {
	*rslt++ = '0';
	*rslt = '\0';
  }
}

unsigned long calculate(const char *numb, unsigned char base)
/* Намира десетичната стойност на числото numb, зададено в бройна система
    с основа base, numb >= 0 */
{ unsigned long result;
  for (result = 0; '\0' != *numb; numb++)
    result = result*base + getValue(*numb);
  return result;
}

double calculateLessThan1(const char *numb, unsigned char base)
/* Намира десетичната стойност на числото numb (0 < numb < 1),
   зададено в бройна система с основа base */
{ const char *end;
  double result;
  for (end = numb + strlen(numb) - 1, result = 0.0; end >= numb; end--)
    result = (result + getValue(*end)) / base;
  return result;
}

double calculateReal(char *numb, unsigned char base)
/* Намира десетичната стойност на реалното число numb, зададено
   в бройна система с основа base */
{ char *pointPos;
  char minus;
  double result;

  /* Проверка за минус */
  if ('-' == *numb) {
	minus = -1;
	numb++;
  }
  else
	minus = 1;

  if (NULL == (pointPos = strchr(numb, '.')))
    return calculate(numb, base); /* Няма дробна част */
  
  /* Пресмятане на цялата част */
  *pointPos = '\0';
  result = calculate(numb, base);
  *pointPos = '.';

  /* Прибавяне на дробната част */
  result += calculateLessThan1(pointPos+1, base);

  return minus*result;

}

int main(void) {
  char numb[MAX_LEN];
  printf("!!! Демонстрация на преобразуването между бройни системи !!!\n");
  convertReal(numb, 777.777, 7, 10); printf("Седмичният запис на 777.777 (10) е %s\n", numb);
  strcpy(numb,"11.D873");
  printf("Десетичният запис на 11.D873 (16) е: %0.10lf\n",calculateReal(numb,16));
  return 0;
}