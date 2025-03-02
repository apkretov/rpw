#define EOF -1
#define CMASK 0377 /*for making char's > 0*/ 
static getchar() { /*unbuffered single character input*/
	char c;
	return(read(0, &c, 1) > 0 ? c & CMASK : EOF);
}

#undef ON
#ifdef ON
#define BUFFERSIZE 100
main() {
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char c;
	int write(); // MINE Forward declaration.

	while((c = getchar()) != EOF)
		write(1, &c, 1);
	
	return 0;
}
#endif