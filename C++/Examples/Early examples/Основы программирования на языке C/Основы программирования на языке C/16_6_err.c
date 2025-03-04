#undef ON
#ifdef ON
// Работа со стеком. Проверка, пуст ли стек. 
// Добавить в стек. Выбрать из стека.
// Стек полон 
#include <stdio.h>
#include <dos.h>
#include <iostream.h>
#include <Process.H>
#include <Stdlib.H>
#include <conio.H>

#define MAX_SIZE 200

char s[MAX_SIZE]; //компоненты стека
int next = 0; // позиция стека
int Empty() {
	return next == 0;
}

int Full() {
	return next == MAX_SIZE;
}

void Push() {
	if (next == MAX_SIZE)
	{
		cout << "Ошибка: стек полон" << endl;
	}
	else {
		next++; cout << "Добавлен" << endl;
		cout << "Что поместить в стек?" << endl;
		cin >> s[next - 1];
	}
}

void OUTst() {
	int i = 0;
	if (next == 0) {
		cout << "Cтек пуст" << endl;
	}
	else {
		for (i = 0; i < next; i++)
			cout << s[i] << " " << endl;
	}
}

void Clear() {
	next = 0;
}

Poz() {
	return next;
}

void Del() {
	int a;
	if (next == 0) cout << "Ошибка: стек пуст" << endl;
	else {
		next--; cout << "Удален " << endl;
	}
}

void menu() {
	cout << "0: распечатать стек" << endl;
	cout << "1: добавить в стек" << endl;
	cout << "2: удалить из стека" << endl;
	cout << "3: узнать номер позиции в стеке" << endl;
	cout << "4: узнать, пуст ли стек" << endl;
	cout << "5: узнать, полон ли стек" << endl;
	cout << "6: очистить стек" << endl;
	cout << "7: выход" << endl;
}

main() {
	char c;
	clrscr();
	textcolor(15);
	do {
		menu();
		cin >> c;
		clrscr();
		switch (c) {
		case '0':OUTst(); getch(); break;
		case '1':Push(); break;
		case '2':Del(); getch(); break;
		case '3':cout <<
			"Hомер " << Poz() << endl; getch(); break;
		case '4':if (Empty() == 1) cout << "Пуст" << endl;
				else cout << "Hе пуст" << endl; getch(); break;
		case '5':if (Full() == 1)cout << "Полн" << endl;
				else cout << "Hе полн" << endl; getch(); break;
		case '6':Clear(); cout <<
			"Стек очищен" << endl; getch(); break;
		case '7':exit(1);
		}
		delay(200);
	} while (c != 7);
	return 0;
}
#endif