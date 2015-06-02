unsigned n = 4242;

int main(void) {
  unsigned digits;
  for (digits = 0; n > 0; n /= 10, digits++);
  printf("Броят на цифрите на %u е %u\n", n, digits);
  return 0;
}
