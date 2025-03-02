#define _CRT_SECURE_NO_WARNINGS // For scanf vs. scanf_s.
#include <stdio.h>

#undef ON
#ifdef ON
int main(int argc, char* argv[]) {
    printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);
    
    int n;
    
    printf("Enter a decimal number to be recursively printed: ");
    if (scanf("%d", &n) == 1)
        printd(n);

    return 0;
}
#endif

static printd(n)   /* print n in decimal (recursive)*/
int n;
{
    int i;

    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if ((i = n / 10) != 0)
        printd(i);
    putchar(n % 10 + '0');
}