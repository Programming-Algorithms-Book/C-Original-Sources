#define MAX_ROMAN_LEN 20

#include <stdio.h>
#include <string.h>

const char *roman1_9[] = {"", "A", "AA", "AAA", "AB", "B", "BA", "BAA", "BAAA", "AC"};
const char *romanDigits[] = {"IVX", "XLC", "CDM", "M" };

const char *roman2test = "MCMLXXXIX";

void getRomanDigit(char *rslt, char x, unsigned char power)
{ const char *pch;
  for (pch = roman1_9[x]; '\0' != *pch; pch++)
	*rslt++ = romanDigits[power][*pch - 'A'];
  *rslt = '\0';
}

char *decimal2Roman(char *rslt, unsigned x)
{ unsigned char power;
  char buf[10];
  char oldRslt[MAX_ROMAN_LEN];
  for (*rslt = '\0', power = 0; x > 0; power++, x /= 10) {
	getRomanDigit(buf, (char)(x % 10), power);
	strcpy(oldRslt, rslt);
	strcpy(rslt,buf);
	strcat(rslt,oldRslt);
  }
  return rslt;
}

unsigned roman2Decimal(const char *roman, char *error)
{ unsigned rslt, value, old;
  const char *saveRoman = roman;
  char buf[MAX_ROMAN_LEN];

  old = 1000; rslt = 0;
  while ('\0' != *roman) {
	switch (*roman++) {
	  case 'I': value =    1; break;
	  case 'V': value =    5; break;
	  case 'X': value =   10; break;
	  case 'L': value =   50; break;
	  case 'C': value =  100; break;
	  case 'D': value =  500; break;
	  case 'M': value = 1000; break;
	  default:
		*error = 1;
		return (unsigned)(-1);
	}
	rslt += value;
	if (value > old)
	  rslt -= 2*old;
	old = value;
  }
  return (*error = strcmp(saveRoman,decimal2Roman(buf,rslt))) 
	  ? (unsigned)(-1) : rslt;
}

int main(void) {
  unsigned decimal;
  char error;
  decimal = roman2Decimal(roman2test,&error);
  if (error) printf("Некоректнo римско число!");
  else printf("Числото в десетична бройна система е %u", decimal);
  return 0;
}
