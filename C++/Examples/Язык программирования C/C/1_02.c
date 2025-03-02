/* print fahrenheit-celsius table for f = 0, 20, ..., 300 */
#undef ON
#ifdef ON
#include <stdio.h>

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int lower, upper, step;
	float fahr, celsius;
	lower = 0;  /* lower limit of temperature	table */
	upper = 300; /* upper limit */
	step = 20; /* step size */
	fahr = lower;
	while (fahr <= upper) {
		celsius = (5.0 / 9.0) * (fahr - 32.0);
		printf("%4.0f %6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
	return 0;
}
#endif

#undef EX_1_3
#ifdef EX_1_3

#include <stdio.h>

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	const int lower = 0, upper = 300, step = 20;
	int fahr = 0;
	double cel;

	printf("%-13s%s", "Fahrenheit", "Celsius");
	
	while (fahr <= upper) {
		cel = (5.0 / 9.0) * (fahr - 32.0);
		printf("\n%10d%10.1f", fahr, cel);
		fahr += step;
	}

	return 0;
}
#endif

#undef EX_1_4
#ifdef EX_1_4

#include <stdio.h>

int main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	const int lower = 0, upper = 100, step = 10;
	int cel = 0;
	double fahr;

	printf("%-10s%s", "Celsius", "Fahrenheit");
	
	while (cel <= upper) {
		fahr = 9.0 / 5.0 * cel + 32.0;
		printf("\n%7d%13.1f", cel, fahr);
		cel += step;
	}

	return 0;
}
#endif