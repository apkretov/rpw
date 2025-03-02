#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define LEN 512

static struct list {
	char c;
	struct list* next;
};
typedef struct list l;

static l* create(l* pl, char c) { //MINE
	l* newpl;

	if ((newpl = (l*)malloc(sizeof(l))) != NULL) {
		newpl->c = c;
		newpl->next = pl;
		return newpl;
	}
	return NULL;
}

static void freememory(l* head) { // 7.8.5 Storage Management @ The C Programming Language- Brian W. Kernighan, Dennis M. Ritchie.pdf, page 198.
	l *p, *q;
	
#ifdef ERR
	for (p = head; p != NULL; p = p->next) // WRONG
		free(p);
#endif
	for (p = head; p != NULL; p = q) { // The right way is to save whatever is needed before freeing.
		q = p->next;
		free(p);
	}
}

#ifdef ON
int main(int argc, char* agrv[]) { //MINE
	setlocale(LC_ALL, "RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int c;
	l* pl = NULL, * tail;
	
	while ((c = getchar()) != EOF)
		if ((pl = create(pl, c)) == NULL)
			exit(EXIT_FAILURE);
	
	tail = pl;
	while (pl != NULL) {
		putchar(pl->c);
		pl = pl->next;
	}

	freememory(tail);

	return 0;
}
#endif