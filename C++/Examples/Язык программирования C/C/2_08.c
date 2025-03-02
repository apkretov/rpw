#undef ON
#ifdef ON

#include <stdio.h>

#define LENMAX 256

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char s[LENMAX] = "first", t[] = "_second";
	strcat(s, t);
	printf("%s", s);
	return 0;
}

static squeeze(s, c) /* delete all c from s */
char s[];
int c;
{
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
}

static strcat(s, t)     /* concatenate t to end of s */
char s[], t[];  /* s must be big enough */
{
	int i, j;

	i = j = 0;
	while (s[i] != '\0') /* find end of s */
		i++;
	while ((s[i++] = t[j++]) != '\0') /* copy t */
		;
}
#endif

#undef EX_2_03
#ifdef EX_2_03

#include <stdio.h>
#define YES 1
#define NO 0

static squeeze(char s1[], const char s2[]) {
	int k = 0, skip = NO;
	
	for (int i = 0; s1[i] != '\0'; ++i) {
		for (int j = 0; s2[j] != '\0'; ++j) {
			if (s1[i] == s2[j]) {
				skip = YES;
				break;
			}
		}
		if (skip == NO)
			s1[k++] = s1[i];
		else
			skip = NO;
	}
	
	s1[k] = '\0';
}

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char s1[] = "test", s2[] = "es";
	squeeze(s1, s2);
	printf("%s", s1);
}
#endif

#undef EX_2_04
#ifdef EX_2_04

#include <stdio.h>

static int any(const char s1[], const char s2[]) {
	int i, j;
	int first = -1;
	for (i = 0; first == -1 && s1[i] != '\0'; ++i) {
		for (j = 0; s2[j] != '\0'; ++j)
			if (s1[i] == s2[j])
				first = i;
	}
	return first;
}

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char s1[] = "test", s2[] = "his";
	printf("%d\n", any(s1, s2));
}
#endif