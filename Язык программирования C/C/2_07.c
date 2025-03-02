#undef ON
#ifdef ON

#include <stdio.h>

main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	printf("atoi(\"1230456\"): %d\n", atoi("1230456"));
	printf("lower(\'a\'): %c\n", lower('a'));
	return 0;
}

static atoi(s)         /* convert s to integer */
char s[];
{
	int i, n;

	n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = 10 * n + s[i] - '0';
	return(n);
}

static lower(c) /* convert c to lower case; ascii only */
int c;
{
	if (c >= 'a' && c <= 'z')
		//ORIG ERR return(c + '@' - 'a');
		return(c + 'A' - 'a'); //MINE
	else   /*@ Записано вместо 'a' строчного*/
		return(c);
}
#endif

#undef EX_2_02_1
#ifdef EX_2_02_1

#include <stdio.h>

static int htoi(char s[]) {
	int n = 0;
	for (int i = 0; s[i] >= '0' && s[i] <= '9' || s[i] >= 'A' && s[i] <= 'F' || s[i] >= 'a' && s[i] <= 'f'; ++i) {
		n *= 16;
		if (s[i] >= '0' && s[i] <= '9')
			n += (s[i] - '0');
		else if (s[i] >= 'A' && s[i] <= 'Z')
			n += (10 + s[i] - 'A');
		else
			n += (10 + s[i] - 'a');
	}
	return n;
}

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char s[] = "FF";
	printf("%d\n", htoi(s));
}
#endif

#undef EX_2_02_2
#ifdef EX_2_02_2
#include <stdio.h>

static int htoi(char* hex[]) {
	int n = 0;
	char* ph = hex;
	char c;

	while ((c = *ph++) != '\0')
		if (c >= '0' && c <= '9')
			n = n * 16 + c - '0';
		else if (c >= 'A' && c <= 'F')
			n = n * 16 + 10 + c - 'A';
		else if (c >= 'a' && c <= 'f')
			n = n * 16 + 10 + c - 'a';
		else {
			printf("%c is non-hexadecimal character.\n", c);
			return 0;
		}

	return n;
}

int main(int argc, char* argv[]) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char hex[512];
	int c, i = 0;
	while ((c = getchar()) != EOF)
		if (c != '\n')
			hex[i++] = c;
		else {
			hex[i] = '\0';
			printf("%d\n", htoi(hex));
			i = 0;
		}
	return 0;
}

#endif