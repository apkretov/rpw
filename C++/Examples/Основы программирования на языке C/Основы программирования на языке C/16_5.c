#undef ON
#ifdef ON

/* � ������ ���������� ����� 1...10
�������� ����� 11, ������� ����������� �� ������ 10,
����� ������ ����� ����� 3 � 4, ����� ���� ����������� ����� 11.
������ ���� ����� ������:
- � ������������ �������;
- �������� ����������� ��������� ������ - ������ �
  ����������� ������;
- �� ����������� ������;
- � ���������. */
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

/* ��������� ������, ������ ���� ��� �������� ������, ������ ����-����� � ������������ ������*/
List* head = NULL; /* ��������� �����*/

void Hed(int i) { /* �������, ������� ������� ��������� ������� ������ */
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
void Print(List* p) { /* ����� ������ �� ����� */
	printf(" %d", p->i);
	if (p->next != NULL)Print(p->next);
}

void delist() { /* ������������ ������������ ������ */
	List* p;
	while (head != NULL) {
		p = head;
		head = head->next;
		free(p);
	}
}

void Vstavka(int i1, int c) { /*������� ������ ��������*/
	List *p = head, *p1;
	
	while (p->i != i1)
		p = p->next;
	
	//ORIG p1 = new List;
	p1 = (List*)malloc(sizeof(List)); //MINE
	p1->i = c;
	p1->next = p->next;
	p->next = p1;
}

void main() { /* ���� � ��������� */
	setlocale(LC_ALL, "ru-RU");
	printf("File: %s\tLine: %d\n\n", __FILE__, __LINE__);
	
	//ORIG clrscr();/* �������� ����� */
	for (int i = 1; i <= 10; i++)
		Hed(i);/* �������� ������ */
	Print(head);/* ����� ������ �� ����� */

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