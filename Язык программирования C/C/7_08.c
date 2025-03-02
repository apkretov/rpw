#include  <stdio.h>

#define LEN 512


static char* fgets_7_08(s, n, iop) /*get at most n chars from iop*/
char* s;
int n;
register FILE* iop;
{
	register int c;
	register char* cs;
	cs = s;
	while (--n > 0 && (c = getc(iop)) != EOF)
		if ((*cs++ = c) == '\n')
			break;
	*cs = '\0';
	return((c == EOF && cs == s) ? NULL : s);
}

static fputs_7_08(s, iop) /*put string s on fils iop*/
register char* s;
register FILE* iop; 
{
	register int c;
	while (c = *s++)
		putc(c, iop);
}

#undef ON
#ifdef ON
int main(int argc, char* argv[]) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);
	
	char s[LEN];

	fgets_7_08(s, LEN - 1, stdin);
	fputs_7_08(s, stdout);

	return 0;
}
#endif
