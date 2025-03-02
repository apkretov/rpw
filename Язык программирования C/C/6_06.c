#include <stdio.h>
#include <stdlib.h> // For exit.
#include <locale.h>
#include "5_04.h"
#include "5_05.h"
#include "5_06.h"

struct nlist { /* basic table entry */ 
      char* name; 
      char* def; 
      struct nlist* next; /* next entry in chain */ 
};

#define HASHSIZE 100 
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

static hash(s)   /* form hash value for string */
char* s;
{
	int hashval;

	printf("s: %s\t", s); //MINE
	/*ORIG for (hashval = 0; *s != '\0'; )
		hashval += *s++;*/
	for (hashval = 0; *s != '\0'; s++) //MINE
		hashval += *s;
	printf("hashval: %d\thashval %% HASHSIZE: %d\n", hashval, hashval %HASHSIZE); //MINE

	return(hashval % HASHSIZE);
}

static struct nlist* lookup(s) /* look for s in hashtab */
	char* s;
{
	struct nlist* np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return(np);  /* found it */
	return(NULL);    /* not found */
}

static struct nlist* install(name, def) /* put (name, def) */
	char *name, *def;
{
	struct nlist *np, *lookup();
	char *strsave(), *alloc();
	int hashval;

	if ((np = lookup(name)) == NULL) { /* not found */
		np = (struct nlist*)alloc(sizeof(*np));
		//MINE np = (struct nlist*)alloc(sizeof(struct nlist)); // x = malloc(sizeof(int)); @ https://stackoverflow.com/questions/1750106/how-can-i-use-pointers-in-java 
		if (np == NULL)
			return(NULL);
		if ((np->name = strsave(name)) == NULL)
			return(NULL);
		hashval = hash(np->name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else        /* already there */
		free_5_04((np->def));/* free previous definition */
	if ((np->def = strsave(def)) == NULL)
		return (NULL);
	return(np);
}

#ifndef ON
main() { //MINE
	setlocale(LC_ALL, "RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	char *name1 = "A", *def1 = "A_definition"; // A: ASCII=65.
	char *name2 = "dA", *def2 = "dA_definition"; // d: ASCII=100, A: ASCII=65 -> dA = 100 + 65 = 165.
	char *def1_2 = "A_definition_2";
	struct nlist *np_out;

	printf("HASHSIZE: %d\n", HASHSIZE);

	if (install(name1, def1) == NULL)
		exit(EXIT_FAILURE);
	if (install(name2, def2) == NULL)
		exit(EXIT_FAILURE);
	if (install(name1, def1_2) == NULL)
		exit(EXIT_FAILURE);

	if ((np_out = lookup(name1)) != NULL)
		printf("def found: %s\n", np_out->def);
	else {
		printf("lookup() returned NULL\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
#endif

#ifdef MINE

#include <stdio.h>
#include <string.h>

main() {
	char *name1 = "A", *def1 = "A_definition"; // A: ASCII=65.
	char *name2 = "dA", *def2 = "dA_definition"; // d: ASCII=100, A: ASCII=65 -> dA = 100 + 65 = 165.

	printf("%d\n", strcmp(name1, name2));
	printf("%d\n", strcmp(name2, name1));
}
#endif