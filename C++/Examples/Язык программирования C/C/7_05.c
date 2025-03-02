#include <stdio.h>
#pragma warning(disable:4996) // c++ - Remove secure warnings (_CRT_SECURE_NO_WARNINGS) from projects by default in Visual Studio - Stack Overflow @ https://stackoverflow.com/questions/16883037/remove-secure-warnings-crt-secure-no-warnings-from-projects-by-default-in-vis

#undef ON
#ifdef ON
main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char name[50], nameout[50];
	int n = 10, m, count;
	sprintf(name, "temp%d", n);
	printf("%s\n", name);

	count = sscanf(name, "%4s %2d", nameout, &m);
	printf("count: %d\n", count);
	printf("%s %d\n", nameout, m);
	
	(void)getchar();
}
#endif