#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_4/05%20Programming%20Assignment/Solution/text_editor.cpp

#include <iostream>
#include <list>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#undef ERR

class Editor {
public:
	Editor();
	void Left();
	void Right();
	void Insert(char token);
	void Cut(size_t tokens = 1);
	void Copy(size_t tokens = 1);
	void Paste();
	string GetText() const;
private:
	list<char> text;
	list<char> buffer; //TEST
	list<char>::iterator cursor; //TEST!
};

Editor::Editor() : text{}, cursor{text.begin()} {}

void Editor::Left() {
	if (cursor == begin(text)) return;
	cursor--;
}

void Editor::Right() {
	if (cursor == end(text)) return;
	cursor++;
}

void Editor::Insert(char token) {
	text.insert(cursor, token);
}

void Editor::Cut(size_t tokens) {
	Copy(tokens);
	auto temp_cursor = cursor;
	for (size_t i = tokens; i > 0; --i) {
		if (++temp_cursor == end(text)) break;
	}
	cursor = text.erase(cursor, temp_cursor);
}

void Editor::Copy(size_t tokens) {
	buffer = {cursor, next(cursor, tokens)};
}

void Editor::Paste() {
	text.insert(cursor, buffer.begin(), buffer.end());
}

string Editor::GetText() const {
	return {text.begin(), text.end()};
}

void TypeText(Editor &editor, const string &text) {
	for (char c : text) {
		editor.Insert(c);
	}
}

#ifdef ERR
void TestEditing() {
	{
		Editor editor;

		const size_t text_len = 12;
		const size_t first_part_len = 7;

		TypeText(editor, "hello, world");
		for (size_t i = 0; i < text_len; ++i) {
			editor.Left();
		}
		editor.Cut(first_part_len);

		for (size_t i = 0; i < text_len - first_part_len; ++i) {
			editor.Right();
		}
		TypeText(editor, ", ");
		editor.Paste();
		editor.Left();
		editor.Left();
		editor.Cut(3);

		ASSERT_EQUAL(editor.GetText(), "world, hello");
	}
	{
		Editor editor;

		TypeText(editor, "misprnit");
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Cut(1);
		editor.Right();
		editor.Paste();

		ASSERT_EQUAL(editor.GetText(), "misprint");
	}
}

void TestReverse() {
	Editor editor;

	const string text = "esreveR";
	for (char c : text) {
		editor.Insert(c);
		editor.Left();
	}
	ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
	Editor editor;
	ASSERT_EQUAL(editor.GetText(), "");

	editor.Left();
	editor.Left();
	editor.Right();
	editor.Right();
	editor.Copy(0);
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
	Editor editor;

	editor.Paste();
	TypeText(editor, "example");
	editor.Left();
	editor.Left();
	editor.Paste();
	editor.Right();
	editor.Paste();
	editor.Copy(0);
	editor.Paste();
	editor.Left();
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "example");
}
#endif //ERR

int main() {
	PRINT_FILE_LINE();

#ifdef ERR
	TestRunner tr;
	LOG_DURATION("All tests");
	{
		tr.RunTest(TestEditing, "TestEditing");
		tr.RunTest(TestReverse, "TestReverse");
		tr.RunTest(TestNoText, "TestNoText");
		tr.RunTest(TestEmptyBuffer, "TestEmptyBuffer");
	}
#endif //ERR

	return 0;
}
#endif //1

/*
Текстовый редактор
Условие

Рассмотрим упрощённый текстовый редактор, поддерживающий следующий набор команд:

	Перемещение курсора влево (Left) и вправо (Right) на одну позицию.
	Ввод символа в текущую позицию курсора (Insert).
	Копирование фрагмента текста, начинающегося в текущей позиции курсора, в буфер обмена (Copy).
	Вырезание фрагмента текста аналогично копированию с последующим удалением скопированных символов из текста (Cut).
	Вставка содержимого буфера обмена в текущую позицию курсора (Paste).

Эти команды действительно поддерживаются практически любым текстовым редактором. Также для команд действуют стандартные правила, определяющие их эффект:

	Если редактор содержит текст длиной n символов, то курсор может находиться в одной из (n + 1) возможных позиций. Например, обозначим курсор вертикальной чертой | (это обозначение мы будем использовать в дальнейшем), тогда в тексте abc курсор может располагаться в 4 позициях: |abc, a|bc, ab|c, abc|. Поэтому команда Left не имеет эффекта, когда курсор расположен в начале текста, а Right не имеет эффекта, когда курсор находится в конце. В частности, ни Left, ни Right не имеют эффекта, когда редактор не содержит текста.
	Введённый символ располагается в позиции курсора, сдвигая курсор и весь текст справа от него на одну позицию вправо. Аналогично, при вставке фрагмента длиной n курсор и текст справа от него смещаются на n позиций вправо. В таблице ниже приведены примеры, демонстрирующие данное правило.

До вставки 	Вводимый символ/вставляемый фрагмент 	После вставки
| 	a 	a|
ab| 	c 	abc|
|bc 	a 	a|bc
|world 	hello_ 	hello_|world
hello_| 	world 	hello_world|
123|78 	456 	123456|78

	Буфер обмена изначально пуст. Вставка пустого фрагмента не имеет эффекта. Содержимое буфера не сбрасывается после вставки, а остается неизменным до следующей команды Copy или Cut. Копирование или вырезание фрагмента нулевой длины не оказывает влияния на текст, но опустошает буфер обмена. Курсор не смещается ни при копировании, ни при вырезании текста. Например, после вырезания из текста ab|cdef фрагмента из трёх символов, получим текст ab|f.

Вам предстоит реализовать «ядро» текстового редактора, поддерживающего все описанные операции, в виде класса Editor, имеющего следующий интерфейс:

class Editor {
public:
  Editor();
  void Left();   // сдвинуть курсор влево
  void Right();  // сдвинуть курсор вправо
  void Insert(char token);   // вставить символ token
  void Copy(size_t tokens);  // cкопировать
							 // не более tokens символов,
							 // начиная с текущей позиции курсора
  void Cut(size_t tokens);  // вырезать не более tokens символов,
							// начиная с текущей позиции курсора
  void Paste();  // вставить содержимое буфера
				 // в текущую позицию курсора
  string GetText() const;  // получить текущее содержимое
						   // текстового редактора
};

Как можно заметить, каждой описанной команде сопоставлен метод класса Editor. Также введён метод GetText(), позволяющий получить текущее содержимое редактора в виде строки. В комментариях к методам Cut(size_t tokens) и Copy(size_t tokens) указано, что в буфер обмена попадает фрагмент длиной не более tokens символов — это означает, что, если справа от курсора располагается менее, чем tokens символов, методы Cut() и Copy() должны вырезать/скопировать все символы справа.
Заготовка решения

text_editor.cpp
Ограничения

Реализация класса Editor должна обрабатывать 10^6 запросов не более чем за 1 секунду. При этом гарантируется, что:

	длина текста никогда не превышает 10^6 символов;
	методы Copy() и Cut() суммарно копируют/вырезают не более 10^6 символов;
	метод GetText() вызывается один раз в каждом из тестов.

Пример

Код

int main() {
  Editor editor;
  const string text = "hello, world";
  for (char c : text) {
	editor.Insert(c);
  }
  // Текущее состояние редактора: `hello, world|`
  for (size_t i = 0; i < text.size(); ++i) {
	editor.Left();
  }
  // Текущее состояние редактора: `|hello, world`
  editor.Cut(7);
  // Текущее состояние редактора: `|world`
  // в буфере обмена находится текст `hello, `
  for (size_t i = 0; i < 5; ++i) {
	editor.Right();
  }
  // Текущее состояние редактора: `world|`
  editor.Insert(',');
  editor.Insert(' ');
  // Текущее состояние редактора: `world, |`
  editor.Paste();
  // Текущее состояние редактора: `world, hello, |`
  editor.Left();
  editor.Left();
  //Текущее состояние редактора: `world, hello|, `
  editor.Cut(3); // Будут вырезаны 2 символа
  // Текущее состояние редактора: `world, hello|`
  cout << editor.GetText();
}

Вывод

world, hello
*/