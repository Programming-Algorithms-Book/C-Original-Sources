#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>

#define MAX_S 10
#define CHAR_CNT 256
#define DICT_SIZE 4096
#define ENCODED_SIZE 1000
#define MAX_MSG_LEN 1000
#define NOT_FOUND (unsigned)(-1)

const char *msg = "abracadabragabramabracadabragabraLALALALALALALALALALALALALALALA";

char dictionary[DICT_SIZE][MAX_S]; /* Речникът */
unsigned dictIndex;                /* Максимален индекс в речника */
unsigned encoded[ENCODED_SIZE];    /* Кодирано съобщение */
unsigned encIndex;                 /* Максимален индекс на кода */

void initTable(void) /* Инициализира таблицата */
{ unsigned i;
  for (i = 0; i < CHAR_CNT; i++) {
    dictionary[i][0] = i;
    dictionary[i][1] = '\0';
  }
  dictIndex = CHAR_CNT;
}

unsigned findIndex(char *s) /* Търси индекс в таблицата */
{ unsigned i;
  for (i = 0; i < dictIndex; i++)
    if (0 == strcmp(s,dictionary[i]))
      return i;
  return NOT_FOUND;
}

void add2Dictionary(char *s) /* Добавя нов низ в таблицата */
{ strcpy(dictionary[dictIndex++],s); }

void LZWencode(const char *msg) /* Извършва кодиране по LZW */
{ unsigned dictIndex, len;
  char ch, str[MAX_S], strch[MAX_S];

  initTable();
  encIndex = 0;
  *str = ch = *msg++; *(str+1) = '\0';
  while ('\0' != *msg) {
    ch = *msg++;
    strcpy(strch,str);
    strch[len = strlen(strch)] = ch; strch[len+1] = '\0';
    dictIndex = findIndex(strch);
    if (NOT_FOUND == dictIndex) {
      encoded[encIndex++] = findIndex(str);
      add2Dictionary(strch);
      *str = ch; *(str+1) = '\0';
    }
    else {
      str[len = strlen(str)] = ch; str[len+1] = '\0';
    }
  }
  encoded[encIndex++] = findIndex(str);
}

void LZWdecode(char *decodedMsg) /* Извършва декодиране по LZW */
{ unsigned code, oldCode, ind, len;
  char str[MAX_S], str2[MAX_S];

  initTable(); ind = 0;
  oldCode = encoded[ind++];

  strcpy(decodedMsg,dictionary[oldCode]);
  while(ind < encIndex) {
    code = encoded[ind++];
    if (code >= dictIndex) {
      strcpy(str,dictionary[oldCode]);
      str[len = strlen(str)] = *str; str[len+1] = '\0';
    }
    else
      strcpy(str,dictionary[code]);
    strcat(decodedMsg,str);
    strcpy(str2,dictionary[oldCode]);
    str2[len = strlen(str2)] = *str; str2[len+1] = '\0';
    add2Dictionary(str2);
    oldCode = code;
  }
}

void printEncodedMsg(const unsigned *encoded, const unsigned encIndex)
{ unsigned ind;
  printf("\n\nКодирано съобщение:\n");
  for (ind = 0; ind < encIndex; ind++)
    printf("%u ", encoded[ind]);
  printf("\n");
}

int main(void) {
  char decodedMsg[MAX_MSG_LEN];
  printf("\n\nВходно съобщение за кодиране:\n%s",msg);
  
  LZWencode(msg);
  printEncodedMsg(encoded, encIndex);

  LZWdecode(decodedMsg);
  printf("\nДекодирано съобщение:\n%s", decodedMsg);
  return 0;
}