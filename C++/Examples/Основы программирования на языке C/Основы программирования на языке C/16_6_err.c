#undef ON
#ifdef ON
// ������ �� ������. ��������, ���� �� ����. 
// �������� � ����. ������� �� �����.
// ���� ����� 
#include <stdio.h>
#include <dos.h>
#include <iostream.h>
#include <Process.H>
#include <Stdlib.H>
#include <conio.H>

#define MAX_SIZE 200

char s[MAX_SIZE]; //���������� �����
int next = 0; // ������� �����
int Empty() {
	return next == 0;
}

int Full() {
	return next == MAX_SIZE;
}

void Push() {
	if (next == MAX_SIZE)
	{
		cout << "������: ���� �����" << endl;
	}
	else {
		next++; cout << "��������" << endl;
		cout << "��� ��������� � ����?" << endl;
		cin >> s[next - 1];
	}
}

void OUTst() {
	int i = 0;
	if (next == 0) {
		cout << "C��� ����" << endl;
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
	if (next == 0) cout << "������: ���� ����" << endl;
	else {
		next--; cout << "������ " << endl;
	}
}

void menu() {
	cout << "0: ����������� ����" << endl;
	cout << "1: �������� � ����" << endl;
	cout << "2: ������� �� �����" << endl;
	cout << "3: ������ ����� ������� � �����" << endl;
	cout << "4: ������, ���� �� ����" << endl;
	cout << "5: ������, ����� �� ����" << endl;
	cout << "6: �������� ����" << endl;
	cout << "7: �����" << endl;
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
			"H���� " << Poz() << endl; getch(); break;
		case '4':if (Empty() == 1) cout << "����" << endl;
				else cout << "H� ����" << endl; getch(); break;
		case '5':if (Full() == 1)cout << "����" << endl;
				else cout << "H� ����" << endl; getch(); break;
		case '6':Clear(); cout <<
			"���� ������" << endl; getch(); break;
		case '7':exit(1);
		}
		delay(200);
	} while (c != 7);
	return 0;
}
#endif