#undef EX_3_01
#ifdef EX_3_01

#include <stdio.h>
#include "1_09.h"

#define MAXLEN 512

static expand(const char s[], char t[]) {
	int i, j;
	for (i = 0, j = 0; s[i] != '\0' && j < MAXLEN - 1; ++i) {
		switch (s[i]){
		case '\t':
			t[j++] = '\\';
			t[j++] = 't';
			break;
		case '\n':
			t[j++] = '\\';
			t[j++] = 'n';
			break;
		default:
			t[j++] = s[i];
		}
	}
	if (s[i] == '\0')
		t[j] = '\0';
	printf("%s\n", t);
}

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char s[MAXLEN], t[MAXLEN];

	while (getline(s, MAXLEN) > 0) {
		expand(s, t);
	}
	
	return 0;
}
#endif