#undef ON
#ifdef ON

#define _CRT_SECURE_NO_WARNINGS

//Построение матрицы инцидентности
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
//OFF #include <iostream.h>
#include <locale.h>

/*ORIG
struct elem {
	int num; // Номер вершины 
	int suns; // Количество сыновей
	char str[20]; // Строка с номерами сыновей
	elem* next; // Указатель на следующую вершину
} *head, * w1, * w2;
*/
struct elem_t { //MINE
	int num; // Номер вершины 
	int suns; // Количество сыновей
	char str[20]; // Строка с номерами сыновей
	struct elem* next; // Указатель на следующую вершину
};
typedef struct elem_t elem;
elem *head, *w1, *w2; //MINE

int connected(int i, int j) {
	int k;
	char* str1;
	w2 = head;
	if (i == j) return 0;
	for (k = 1; k < i; k++)
		w2 = w2->next;
	if (strchr(w2->str, j)) return 1;
	return 0;
}

void main() {
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);

	int tops;
	int i, j, k, l;
	char* str1;
	//ORIG clrscr();
	printf("Введите количество вершин \n");
	scanf("%d", &tops);
	head = (elem*)malloc(sizeof(elem));
	head->num = 1;
	head->suns = 0;
	head->str[0] = '\0';
	head->next = NULL;
	w1 = head;
	for (i = 2; i <= tops; i++) {
		w2 = (elem*)malloc(sizeof(elem));
		w2->num = i;
		w2->suns = 0;
		w2->str[0] = '\0';
		w2->next = NULL;
		w1->next = w2;
		w1 = w2;
	}
	w1 = head;
	for (i = 1; i <= tops; i++) {
		// clrscr();
		printf("Введите количество путей из вершины % d\n", i);
			scanf("%d", &k);
		for (j = 1; j <= k; j++) {
			printf("Введите связь %d\n", j);
			scanf("%d", &l);
			if ((l <= 0) || (l > tops)) {
				printf("Такой вершины нет, повторите попытку\n");
					l = 0;
				j--;
				continue;
			}
			w1->str[w1->suns++] = l;
			w1->str[w1->suns] = '\0';
			if (w1->suns == 49) {
				printf("Слишком много связей !");
				exit(1);
			}
		}
		w1 = w1->next;
	}
	//ORIG clrscr();
	printf("\n\n Матрица инциндентности :\n");
	for (i = 1; i <= tops; i++) {
		printf("\n %d) ", i);
		for (j = 1; j <= tops; j++) {
			printf("%d ", connected(i, j));
		}
	}
	printf("\n\n Нажмите любую клавишу...");
	//ORIG getch();
	(void)getchar();
}
#endif
