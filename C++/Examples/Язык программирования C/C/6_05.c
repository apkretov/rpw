#undef ON
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "5_04.h"
#include "5_05.h" // For strcpy() used in 5_06.c.
#include "5_06.h"
#include "6_03.h"

#define MAXWORD 20000
#define LETTER 'a'

#define _6_05
#undef _6_09
#ifdef _6_05
struct tnode { /* the basic node */ 
      char* word; /* points to the text */ 
      int count; /* number of occurrences */ 
      struct tnode* left; /* left child */ 
      struct tnode* right; /* right child */ 
};
#elif defined(_6_09)
#include "6_09.h"
#endif

#ifdef ON
main() { /* word freguency count */
    printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	struct tnode *root, *tree();
	char word[MAXWORD];
	int t;
	root = NULL;
	while ((t = getword(word, MAXWORD)) != EOF)
		if (t == LETTER)
			root = tree(root, word);
	treeprint(root);
}
#endif

static struct tnode* tree(p, w) /* install w at or below p */ //TEMPLATE: Return struct tnode* p but NOT take *p as an agrument.
struct tnode* p;
char* w;
{
	struct tnode* talloc();
	char* strsave();

	int strcmp();
	int cond;
	if (p == NULL) { /* a new word has arrived */
		p = talloc(); /* make a new node */
		p->word = strsave(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;     /* repeated word */
	else if (cond < 0)	/* lower goes into left subtree */
		p->left = tree(p->left, w);
	else				/* greater into right subtree */
		p->right = tree(p->right, w);
	return(p);
}

#ifdef _6_05 // c - difference between #if defined(WIN32) and #ifdef(WIN32) - Stack Overflow @ https://stackoverflow.com/questions/1714245/difference-between-if-definedwin32-and-ifdefwin32
static struct tnode* talloc() {
	char* alloc();
	return ((struct tnode*)alloc(sizeof(struct tnode)));
}
#elif defined(_6_09) // Тогда функцию talloc можно записать в виде
static treeptr talloc() {
	char* alloc();
	return ((treeptr)alloc(sizeof(treenode)));
}
#endif

#ifdef ON
static treeprint(p) /* print tree  p  recursively */
struct tnode* p;
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}
#endif

#ifdef EX_6_06_1

struct cnt_node {
	struct tnode* ptnode;
	struct cnt_node* left;
	struct cnt_node* right;
};

static struct cnt_node* cnt_alloc() {
	return ((struct cnt_node*)alloc(sizeof(struct cnt_node)));
}

static struct cnt_node* cnt_tree(struct cnt_node* p, struct tnode* n) { // Sort the tree by counts.
	if (p == NULL) { /* a new node has arrived */
		p = cnt_alloc(); /* make a new node */
		p->ptnode = n;
		p->left = p->right = NULL;
	} else if ((n->count - p->ptnode->count) * 100 + strcmp(n->word, p->ptnode->word) < 0) // If the counts of the n->count and p nodes are the same (the upper two decimals * 100) a difference between word letters (the last two decimals) define the order.
		p->left = cnt_tree(p->left, n); /* lower goes into left subtree */
	else			
		p->right = cnt_tree(p->right, n); /* greater into right subtree */
	return p;
}

static struct cnt_node* treestep(struct cnt_node* cnt_root, struct tnode* root) { // Step through the tree recursively.
	if (root != NULL) {
		cnt_root = treestep(cnt_root, root->left);
		cnt_root = cnt_tree(cnt_root, root);
		cnt_root = treestep(cnt_root, root->right);
	}
	return cnt_root;
}

static cnt_treeprint(struct cnt_node* p) { /* print tree  p  recursively */
	if (p != NULL) {
		cnt_treeprint(p->right);
		printf("%4d %s\n", p->ptnode->count, p->ptnode->word);
		cnt_treeprint(p->left);
	}
}

main() {
    printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	struct tnode* root, *tree();
	struct cnt_node* cnt_root;
	char word[MAXWORD];
	int t;
	root = NULL;
	cnt_root = NULL;

	while ((t = getword(word, MAXWORD)) != EOF)
		if (t == LETTER)
			root = tree(root, word);

	cnt_root = treestep(cnt_root, root);
	cnt_treeprint(cnt_root);
}
#endif

#ifdef EX_6_06_3 //EX_6_04_ENG // Solution by Bryan Williams @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_6:Exercise_4#Solution_by_Bryan_Williams
/*

  Chapter 6. Structures

          Write a program that prints out the distinct words in its
          input sorted into decreasing order of frequency of occurrence.
          Precede each word by its count.

  Author: Bryan Williams

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>


typedef struct WORD
{
    char* Word;
    size_t Count;
    struct WORD* Left;
    struct WORD* Right;
} WORD;


/*
  Assumptions: input is on stdin, output to stdout.

  Plan: read the words into a tree, keeping a count of how many we have,
        allocate an array big enough to hold Treecount (WORD *)'s
        walk the tree to populate the array.
        qsort the array, based on size.
        printf the array
        free the array
        free the tree
        free tibet (optional)
        free international shipping!
*/

#define SUCCESS                      0
#define CANNOT_MALLOC_WORDARRAY      1
#define NO_WORDS_ON_INPUT            2
#define NO_MEMORY_FOR_WORDNODE       3
#define NO_MEMORY_FOR_WORD           4


#define NONALPHA "1234567890 \v\f\n\t\r+=-*/\\,.;:'#~?<>|{}[]`!\"�$%^&()"

int ReadInputToTree(WORD** DestTree, size_t* Treecount, FILE* Input);
int AddToTree(WORD** DestTree, size_t* Treecount, char* Word);
int WalkTree(WORD** DestArray, WORD* Word);
int CompareCounts(const void* vWord1, const void* vWord2);
int OutputWords(FILE* Dest, size_t Count, WORD** WordArray);
void FreeTree(WORD* W);
char* dupstr(char* s);

void FreeTree(WORD* W)
{
    if (NULL != W)
    {
        if (NULL != W->Word)
        {
            free(W->Word);
            W->Word = NULL;
        }
        if (NULL != W->Left)
        {
            FreeTree(W->Left);
            W->Left = NULL;
        }
        if (NULL != W->Right)
        {
            FreeTree(W->Right);
            W->Right = NULL;
        }
    }
}

int AddToTree(WORD** DestTree, size_t* Treecount, char* Word)
{
    int Status = SUCCESS;
    int CompResult = 0;

    /* safety check */
    assert(NULL != DestTree);
    assert(NULL != Treecount);
    assert(NULL != Word);

    /* ok, either *DestTree is NULL or it isn't (deep huh?) */
    if (NULL == *DestTree)  /* this is the place to add it then */
    {
        *DestTree = malloc(sizeof * *DestTree);
        if (NULL == *DestTree)
        {
            /* horrible - we're out of memory */
            Status = NO_MEMORY_FOR_WORDNODE;
        }
        else
        {
            (*DestTree)->Left = NULL;
            (*DestTree)->Right = NULL;
            (*DestTree)->Count = 1;
            (*DestTree)->Word = dupstr(Word);
            if (NULL == (*DestTree)->Word)
            {
                /* even more horrible - we've run out of memory in the middle */
                Status = NO_MEMORY_FOR_WORD;
                free(*DestTree);
                *DestTree = NULL;
            }
            else
            {
                /* everything was successful, add one to the tree nodes count */
                ++* Treecount;
            }
        }
    }
    else  /* we need to make a decision */
    {
        CompResult = strcmp(Word, (*DestTree)->Word);
        if (0 < CompResult)
        {
            Status = AddToTree(&(*DestTree)->Left, Treecount, Word);
        }
        else if (0 > CompResult)
        {
            Status = AddToTree(&(*DestTree)->Left, Treecount, Word);
        }
        else
        {
            /* add one to the count - this is the same node */
            ++(*DestTree)->Count;
        }
    }  /* end of else we need to make a decision */

    return Status;
}

int ReadInputToTree(WORD** DestTree, size_t* Treecount, FILE* Input)
{
    int Status = SUCCESS;
    char Buf[8192] = { 0 };
    char* Word = NULL;

    /* safety check */
    assert(NULL != DestTree);
    assert(NULL != Treecount);
    assert(NULL != Input);

    /* for every line */
    while (NULL != fgets(Buf, sizeof Buf, Input))
    {
        /* strtok the input to get only alpha character words */
        Word = strtok(Buf, NONALPHA);
        while (SUCCESS == Status && NULL != Word)
        {
            /* deal with this word by adding it to the tree */
            Status = AddToTree(DestTree, Treecount, Word);

            /* next word */
            if (SUCCESS == Status)
            {
                Word = strtok(NULL, NONALPHA);
            }
        }
    }

    return Status;
}

int WalkTree(WORD** DestArray, WORD* Word) {
    int Status = SUCCESS;
    static WORD** Write = NULL;

    assert(NULL != Word); /* safety check */
    if (NULL != DestArray) /* store the starting point if this is the first call */
        Write = DestArray;

    if (NULL != Word) { /* Now add this node and it's kids */
        *Write = Word;
        ++Write;
        if (NULL != Word->Left)
            Status = WalkTree(NULL, Word->Left);
        if (NULL != Word->Right)
            Status = WalkTree(NULL, Word->Right);
    }
    return Status;
}

int CompareCounts(const void* vWord1, const void* vWord2) { /* CompareCounts is called by qsort. This means that it gets pointers to the data items being compared. In this case the data items are pointers too. */
    int Result = 0;
    WORD* const* Word1 = vWord1;
    WORD* const* Word2 = vWord2;

    assert(NULL != vWord1);
    assert(NULL != vWord2);

    if ((*Word1)->Count < (*Word2)->Count) /* ensure the result is either 1, 0 or -1 */
        Result = 1;
    else if ((*Word1)->Count > (*Word2)->Count)
        Result = -1;
    else
        Result = 0;

    return Result;
} 

int OutputWords(FILE* Dest, size_t Count, WORD** WordArray) {
    int Status = SUCCESS;
    size_t Pos = 0;

    assert(NULL != Dest); /* safety check */
    assert(NULL != WordArray);
    fprintf(Dest, "Total Words : %lu\n", (unsigned long)Count); /* Print a header */

    while (SUCCESS == Status && Pos < Count) { /* Print the words in descending order */
        fprintf(Dest, "%10lu %s\n", (unsigned long)WordArray[Pos]->Count, WordArray[Pos]->Word);
        ++Pos;
    }
    return Status;
}

char* dupstr(char* s) /* dupstr: duplicate a string */
{
    char* Result = NULL;
    size_t slen = 0;

    /* sanity check */
    assert(NULL != s);

    /* get string length */
    slen = strlen(s);

    /* allocate enough storage */
    Result = malloc(slen + 1);

    /* populate string */
    if (NULL != Result)
    {
        memcpy(Result, s, slen);
        *(Result + slen) = '\0';
    }

    return Result;
} 

int main(void) {
    printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

    int Status = SUCCESS;
    WORD* Words = NULL;
    size_t Treecount = 0;
    WORD** WordArray = NULL;

    if (SUCCESS == Status) /* Read the words on stdin into a tree */
        Status = ReadInputToTree(&Words, &Treecount, stdin);
    if (SUCCESS == Status) /* Sanity check for no sensible input */
        if (0 == Treecount)
            Status = NO_WORDS_ON_INPUT;

    if (SUCCESS == Status) { /* allocate a sufficiently large array */
        WordArray = malloc(Treecount * sizeof * WordArray);
        if (NULL == WordArray)
            Status = CANNOT_MALLOC_WORDARRAY;
    }

    if (SUCCESS == Status) /* Walk the tree into the array */
        Status = WalkTree(WordArray, Words);
    if (SUCCESS == Status) /* qsort the array */
        qsort(WordArray, Treecount, sizeof * WordArray, CompareCounts);
    if (SUCCESS == Status) /* walk down the WordArray outputting the values */
        Status = OutputWords(stdout, Treecount, WordArray);

    if (NULL != WordArray) { /* free the word array */
        free(WordArray);
        WordArray = NULL;
    }

    if (NULL != Words) { /* and free the tree memory */
        FreeTree(Words);
        Words = NULL;
    }

    if (SUCCESS != Status) /* Error report and we are finshed */
        fprintf(stderr, "Program failed with code %d\n", Status);
    
    return (SUCCESS == Status ? EXIT_SUCCESS : EXIT_FAILURE);
}
#endif
