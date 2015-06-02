#include <stdio.h>
#include <string.h>
#define SHOW_MORE
#define MESSAGE "АРИТМЕТИКА"

#define MAX 256

struct { 
  double low, high;
} sym[MAX];
unsigned freq[MAX];

void getStatistics(char *mesg) /* Намира броя на срещанията на всеки символ */
{ unsigned i;
  for (i = 0; i < MAX; i++)
    freq[i] = 0;
  while ('\0' != *mesg)
    freq[(unsigned char) *mesg++]++;
}

void buildModel(char *mesg) /* Построява модела */
{ unsigned i, cnt, n;
  for (n = strlen(mesg), cnt = i = 0; i < MAX; i++) {
    sym[i].low = (double) cnt/n;
    cnt += freq[i];
    sym[i].high = (double) cnt/n;
  }
}

void printModel(void)
{ unsigned i;
  printf("\n             ГРАНИЦА");
  printf("\nСИМВОЛ    ДОЛНА   ГОРНА");
  for (i = 0; i < MAX; i++)
    if (freq[i])
      printf("\n%4c     %1.4f  %1.4f", i,sym[i].low,sym[i].high);
}

double arithmeticEncode(char *mesg) /* Извършва аритметично кодиране */
{ double range, low, high;
  low = 0.0, high = 1.0;
  while ('\0' != *mesg) {
    range = high - low;
    high = low + range * sym[(unsigned char) *mesg].high;
    low = low + range * sym[(unsigned char) *mesg].low;
#ifdef SHOW_MORE
    printf("\n%c    %1.9f  %1.9f",*mesg,low,high);
#endif
    *mesg++;
  }
  return low;
}

char getSymbol(double encMsg)
{ unsigned i;
  for (i = 0; i < MAX; i++)
    if (sym[i].low <= encMsg && sym[i].high > encMsg)
      break;
  return (char) i;
}

void arithmeticDecode(double msg, unsigned msgLen) /* Извършва декодиране */
{ double range;
  unsigned char ch, i;
  for (i = 0; i < msgLen; i++) {
    ch = (unsigned char) getSymbol(msg);
#ifdef SHOW_MORE
    printf("\n%c    %1.9f",ch,msg);
#else
    putc(ch,stdout);
#endif
    range = sym[ch].high - sym[ch].low;
    msg -= sym[ch].low;
    msg /= range;
  }
}

int main(void) {
  double code;
  printf("\n\nИзходно съобщение: %s",MESSAGE);
  getStatistics(MESSAGE);
  buildModel(MESSAGE);
#ifdef SHOW_MORE
  printModel();
  printf("\nНатиснете <<ENTER>>"); getchar();
#endif
  code = arithmeticEncode(MESSAGE);
  printf("\nКодът на съобщението е: %1.8f",code);
  printf("\nДекодиране: ");
  arithmeticDecode(code,strlen(MESSAGE));
  return 0;
}