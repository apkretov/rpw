#undef ON
#ifdef ON

/* В список помещаются цифры 1...10
Вводится число 11, сначала вставляется за цифрой 10,
затем рвется связь между 3 и 4, между ними вставляется число 11.
Пример дает навык работы:
- с динамической памятью;
- создания абстрактной структуры данных - список и
  модификации списка;
- со структурами данных;
- с функциями. */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <locale.h>
/*ORIG
struct List {
	int i;
	List* next;
};
*/
struct List_t { //MINE
	int i;
	struct List_t* next;
};
typedef struct List_t List;

/* структура данных, первое поле для хранения целого, второе поле-адрес в динамической памяти*/
List* head = NULL; /* начальный адрес*/

void Hed(int i) { /* функция, которая создает очередной элемент списка */
	if (head == NULL) {
		head = (List*)malloc(sizeof(List));
		head->i = 1;
		head->next = NULL;
	} else {
		//ORIG struct List *p, *p1;
		List* p, * p1; //MINE
		p = head;
		while (p->next != NULL)
			p = p->next;
		//ORIG p1 = new List;
		p1 = (List*)malloc(sizeof(List)); //MINE
		p1->i = i;
		p1->next = NULL;
		p->next = p1;
	}
}
int s = 0;
void Print(List* p) { /* вывод списка на экран */
	printf(" %d", p->i);
	if (p->next != NULL)Print(p->next);
}

void delist() { /* освобождение динамической памяти */
	List* p;
	while (head != NULL) {
		p = head;
		head = head->next;
		free(p);
	}
}

void Vstavka(int i1, int c) { /*вставка нового элемента*/
	List *p = head, *p1;
	
	while (p->i != i1)
		p = p->next;
	
	//ORIG p1 = new List;
	p1 = (List*)malloc(sizeof(List)); //MINE
	p1->i = c;
	p1->next = p->next;
	p->next = p1;
}

void main() { /* вход в программу */
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);
	
	//ORIG clrscr();/* очистить экран */
	for (int i = 1; i <= 10; i++)
		Hed(i);/* создание списка */
	Print(head);/* вывод списка на экран */

	Vstavka(10, 11);
	printf("\n");
	Print(head);
	
	Vstavka(3, 11);
	printf("\n");
	Print(head);
	
	delist();
	//ORIG getch();
	getchar(); //MINE
}
#endif