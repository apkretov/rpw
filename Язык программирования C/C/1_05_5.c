#undef ON
#ifdef ON

#include <stdio.h>

#define yes 1
#define no 0

main() { /* count lines, words, chars in input */
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int c, nc, nl, nw, inword;

   inword = no;
   nl = nw = nc = 0;
   while ((c = getchar()) != EOF) {
      ++nc;
      if (c == '\n')
         ++nl;
      if (c == ' ' || c == '\n' || c == '\t')
         inword = no;
      else if (inword == no) {
         inword = yes;
         ++nw;
      }
   }
   printf("%d %d %d\n", nl, nw, nc);
}
#endif

#undef EX_1_10
#ifdef EX_1_10

int main() {
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int c, blank = 1;
   while ((c = getchar()) != EOF) {
      if (c != ' ' && c != '\t' && c != '\n') {
         putchar(c);
         blank = 0;
      }
      else if (!blank) {
         ++blank;
         putchar('\n');
      }
   }
}
#endif

#undef EX_1_10_1 // Solution by KreativitetNO @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_1:Exercise_12#Solution_by_KreativitetNO
#ifdef EX_1_10_1

#include <stdio.h>

int main() {
    printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c, bp;
	char buffer[512];

	bp = 0;
	while ((c = getchar()) != EOF) {
		/* any word separating character you define goes here */
		if (c != ' ' && c != '\t' && c != '\n')
			buffer[bp++] = c;
		else if (bp > 0) {
			printf("%s\n", buffer);
			bp = 0;
		}
		buffer[bp] = '\0';
		}
		if (bp > 0)
			printf("%s\n", buffer);
	}
#endif

#undef EX_1_10_2 // Solution by sl4y3r 0wn3r @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_1:Exercise_12#Solution_by_sl4y3r_0wn3r
#ifdef EX_1_10_2

#include <stdio.h>
#define IS_UPPER(N) ((N) >= 'A' && (N) <= 'Z')   /* 'A'==65 && 'Z'==90 */
#define IS_LOWER(N) ((N) >= 'a' && (N) <= 'z')   /* 'a'==97 && 'z'==122 */
#define IS_ALPHA(N) (IS_LOWER(N) || IS_UPPER(N)) /* [A-Za-z] x*/
#define OUT 0
#define IN  1

int main(void)
{
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int c = EOF, state = OUT;
   while ((c = getchar()) != EOF) {
      if (IS_ALPHA(c)) {
         state = IN;
         putchar(c);
      }
      else if (state == IN) {
         state = OUT;
         putchar('\n');
      }
   }

   return 0;
}

#endif

#undef EX_1_11
#ifdef EX_1_11

#include <stdio.h>

#define YES 1
#define NO 0

int main() {
   printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

   int c;
   int lc, wc, cc;
   int inword = NO;
   lc = wc = cc = 0;
	
   while ((c = getchar()) != EOF) {
		++cc;
		if (c != ' ' && c != '\t' && c != '\n') {
         if (c == '\'' || c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z') {
            if (!inword) {
               inword = YES;
               if (!(c >= '0' && c <= '9') && c != '\'')
                  ++wc;
            }
         } else if (wc > 0) // Any non-word charachter encountered inside a word decrements the word count.
            --wc;
      } else {
         inword = NO;
         if (c == '\n')
            ++lc;
      }
	}
   printf("cc: %2d \twc: %2d \tlc: %2d", cc, wc, lc);
}
#endif