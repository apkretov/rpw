#undef ON
#ifdef ON

#include <stdio.h>

#undef VER1
#define VER2

main() { /* test power function */
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int i;

   for (i = 0; i < 10; ++i)
      printf("%d %d %d\n", i, power(2, i), power(-3, i));
}

#ifdef VER1
static power(x, n)  /* raise  x  n-th power; n > 0  */
int x, n;
{
   int i, p;
   p = 1;
   for (i = 1; i <= n; ++i)
      p = p * x;
   return (p);
}
#endif //VER1

#ifdef VER2
static int power(int x, int n) {
   int p;
   for (p = 1; n > 0; --n)
      p = p * x;
   return p;
}
#endif //VER2
#endif //ON

#undef EX_1_13
#ifdef EX_1_13

int main() {
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int c;
   while ((c = getchar()) != EOF)
      putchar(power(c));
   return 0;
}

static int power(int c) {
   if (c >= 'A' && c <= 'Z')
      return c + 'a' - 'A';
   else if (c == '\n' || c >= 'a' && c <= 'z')
      return c;
   else
      return 'c';
}
#endif