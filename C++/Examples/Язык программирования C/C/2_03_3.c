#undef ON
#ifdef ON

#include <stdio.h>

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char s[] = "test";
	printf("%d", strlen_2_03_3(s));
	return 0;
}
#endif

/* ORIG
strlen_2_03_3(s) // return length of s
char  s[];
*/
int strlen_2_03_3(char s[]) {
   int i;

   i = 0;
   while (s[i] != '\0')
      ++i;
   
   return(i);
}
