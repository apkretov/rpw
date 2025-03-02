#include <stdio.h>
#include <stdarg.h>

static void minprintf(char* fmt, ...) { /* minprintf: minimal printf with variable argument list */
	va_list ap; /* points to each unnamed arg in turn */
	char *p, *sval;
	int ival;
	double dval;
	va_start(ap, fmt); /* make ap point to 1st unnamed arg */
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
		case 'd':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 's':
			for (sval = va_arg(ap, char*); *sval; sval++)
				putchar(*sval);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap); /* clean up when done */
}

#undef ON
#ifdef ON

int main(int argc, char* agrv[]) {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	minprintf("Test %s number %d\nTest %s number %d\n", "string", 1, "line", 2);

	return 0;
}
#endif