#ifdef ON

#include <stdio.h>

main() { /* count lines in input */
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int c, nl;

   nl = 0;
   while ((c = getchar()) != EOF)
      if (c == '\n')
         ++nl;
   printf("%d\n", nl);
}

#endif
 
#ifdef EX_1_6
#include <stdio.h>

int main() {
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int n = 0, c;
   while ((c = getchar()) != EOF)
      if (c == ' ' || c == '\t' || c == '\n')
         ++n;
   printf("%d", n);
   return 0;
}
#endif

#ifdef EX_1_7
int main() {
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int c, blank = 0;
   while ((c = getchar()) != EOF) {
      if (c != ' ') {
         if (blank) {
            blank = 0;
            putchar(' ');
         }
         putchar(c);
      } else
         ++blank;
   }
   return 0;
}
#endif

#ifdef EX_1_7_1 // Dabeau's @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_1:Exercise_9#Solution_by_Dabeau

int main() {
    printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char c;
	char prev_c; /* previous character */

	prev_c = 0;
	while ((c = getchar()) != EOF)
		/* output c if it's not a blank OR if the previous c is not a blank */
		if (c != ' ' || prev_c != ' ') {
			putchar(c);
			prev_c = c;
		}
}
#endif

#ifdef EX_1_7_2 // pezcore's @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_1:Exercise_9#Solution_by_pezcore

int main() {
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int c;
   while ((c = getchar()) != EOF) {
      putchar(c);
      if (c == 0x20) {
         while ((c = getchar()) == 0x20)
            ;
         putchar(c);
      }
   }
}
#endif