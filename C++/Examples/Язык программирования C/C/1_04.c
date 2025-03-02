#undef ON
#ifdef ON

#include <stdio.h>

#define  LOWER 0/* lower limit of table */
#define  UPPER 300  /* upper limit */
#define  STEP 20  /* step size */

int main() { /* fahrenheit-celsius table */
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int fahr;
	for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
		printf("%4d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));

	return 0;
}
#endif
