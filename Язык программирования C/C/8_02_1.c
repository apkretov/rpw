#pragma warning(disable:4996) // c++ - Remove secure warnings (_CRT_SECURE_NO_WARNINGS) from projects by default in Visual Studio - Stack Overflow @ https://stackoverflow.com/questions/16883037/remove-secure-warnings-crt-secure-no-warnings-from-projects-by-default-in-vis

#include <stdio.h>
#undef WIN
#ifdef WIN
#include <io.h>
#endif
#include <fcntl.h>
#include <stdlib.h>

#define SIZE 256 // MINE
#define FILENAME "8_02_1.c" // MINE
static mine() { // ������ ��������� ��������� 100 ���� �� TEST.TST � ������ buffer: @ http://www.c-cpp.ru/content/read-rtlread
	int fd;
	char buffer[SIZE];
	int nread; // MINE

	if ((fd = open(FILENAME, O_RDONLY)) == -1) {
		printf("Cannot open file.\n");
		(void)getchar();
		exit(1);
	}
	if ((nread = read(fd, buffer, SIZE)) != SIZE)
		printf("Possible read error.");
	else { // MINE
		*(buffer + --nread) = '\0';
		printf("Characters read: %d\nBuffer read: %s\n", nread, buffer);
	}
}

#include "3_06.h" //MINE
#include "5_04.h" //MINE
#define BUFSIZE 512 /*best size for pdp-11 unix*/ 

static myprintf(int n) { // printf("Number of elements read: %d\n", n) w/o stdio.h //MINE
	char message[] = "Number of elements read: ", nstr[BUFSIZE];

	write(1, message, strlen_5_04(message));
	itoa_3_06(n, nstr);
	write(1, nstr, strlen_5_04(nstr));
	write(1, "\n", 1);
}

static f1() { /*copy input to output*/
	char buf[BUFSIZE];
	int n;

	while ((n = read(0, buf, BUFSIZE)) > 0) {
		myprintf(n); //MINE
		write(1, buf, n);
	}
}

#undef ON
#ifdef ON
main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	//mine();
	f1();
	return 0;
}
#endif