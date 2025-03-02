#undef ON
#ifdef ON
#include <stdio.h>

int main() { /* fahrenheit-celsius table */
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int fahr;
   for (fahr = 0; fahr <= 300; fahr = fahr + 20)
      printf("%4d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));
   return 0;
}
#endif

#undef EX_1_05
#ifdef EX_1_05

#include <stdio.h>

int main() {
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   const int lower = 0, upper = 300, step = 20;
   int fahr;
   float cel;

   printf("%-13s%s", "Fahrenheit", "Celsium");
   for (fahr = upper; fahr >= lower; fahr -= step) {
      cel = 5.0 / 9.0 * (fahr - 32.0);
      printf("\n%10d%10.1f", fahr, cel);
   }
}

#endif