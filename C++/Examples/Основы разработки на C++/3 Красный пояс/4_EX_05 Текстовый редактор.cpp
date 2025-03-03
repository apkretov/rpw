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
��������� ��������
�������

���������� ���������� ��������� ��������, �������������� ��������� ����� ������:

	����������� ������� ����� (Left) � ������ (Right) �� ���� �������.
	���� ������� � ������� ������� ������� (Insert).
	����������� ��������� ������, ������������� � ������� ������� �������, � ����� ������ (Copy).
	��������� ��������� ������ ���������� ����������� � ����������� ��������� ������������� �������� �� ������ (Cut).
	������� ����������� ������ ������ � ������� ������� ������� (Paste).

��� ������� ������������� �������������� ����������� ����� ��������� ����������. ����� ��� ������ ��������� ����������� �������, ������������ �� ������:

	���� �������� �������� ����� ������ n ��������, �� ������ ����� ���������� � ����� �� (n + 1) ��������� �������. ��������, ��������� ������ ������������ ������ | (��� ����������� �� ����� ������������ � ����������), ����� � ������ abc ������ ����� ������������� � 4 ��������: |abc, a|bc, ab|c, abc|. ������� ������� Left �� ����� �������, ����� ������ ���������� � ������ ������, � Right �� ����� �������, ����� ������ ��������� � �����. � ���������, �� Left, �� Right �� ����� �������, ����� �������� �� �������� ������.
	�������� ������ ������������� � ������� �������, ������� ������ � ���� ����� ������ �� ���� �� ���� ������� ������. ����������, ��� ������� ��������� ������ n ������ � ����� ������ �� ���� ��������� �� n ������� ������. � ������� ���� ��������� �������, ��������������� ������ �������.

�� ������� 	�������� ������/����������� �������� 	����� �������
| 	a 	a|
ab| 	c 	abc|
|bc 	a 	a|bc
|world 	hello_ 	hello_|world
hello_| 	world 	hello_world|
123|78 	456 	123456|78

	����� ������ ���������� ����. ������� ������� ��������� �� ����� �������. ���������� ������ �� ������������ ����� �������, � �������� ���������� �� ��������� ������� Copy ��� Cut. ����������� ��� ��������� ��������� ������� ����� �� ��������� ������� �� �����, �� ���������� ����� ������. ������ �� ��������� �� ��� �����������, �� ��� ��������� ������. ��������, ����� ��������� �� ������ ab|cdef ��������� �� ��� ��������, ������� ����� ab|f.

��� ��������� ����������� ����� ���������� ���������, ��������������� ��� ��������� ��������, � ���� ������ Editor, �������� ��������� ���������:

class Editor {
public:
  Editor();
  void Left();   // �������� ������ �����
  void Right();  // �������� ������ ������
  void Insert(char token);   // �������� ������ token
  void Copy(size_t tokens);  // c����������
							 // �� ����� tokens ��������,
							 // ������� � ������� ������� �������
  void Cut(size_t tokens);  // �������� �� ����� tokens ��������,
							// ������� � ������� ������� �������
  void Paste();  // �������� ���������� ������
				 // � ������� ������� �������
  string GetText() const;  // �������� ������� ����������
						   // ���������� ���������
};

��� ����� ��������, ������ ��������� ������� ����������� ����� ������ Editor. ����� ����� ����� GetText(), ����������� �������� ������� ���������� ��������� � ���� ������. � ������������ � ������� Cut(size_t tokens) � Copy(size_t tokens) �������, ��� � ����� ������ �������� �������� ������ �� ����� tokens �������� � ��� ��������, ���, ���� ������ �� ������� ������������� �����, ��� tokens ��������, ������ Cut() � Copy() ������ ��������/����������� ��� ������� ������.
��������� �������

text_editor.cpp
�����������

���������� ������ Editor ������ ������������ 10^6 �������� �� ����� ��� �� 1 �������. ��� ���� �������������, ���:

	����� ������ ������� �� ��������� 10^6 ��������;
	������ Copy() � Cut() �������� ��������/�������� �� ����� 10^6 ��������;
	����� GetText() ���������� ���� ��� � ������ �� ������.

������

���

int main() {
  Editor editor;
  const string text = "hello, world";
  for (char c : text) {
	editor.Insert(c);
  }
  // ������� ��������� ���������: `hello, world|`
  for (size_t i = 0; i < text.size(); ++i) {
	editor.Left();
  }
  // ������� ��������� ���������: `|hello, world`
  editor.Cut(7);
  // ������� ��������� ���������: `|world`
  // � ������ ������ ��������� ����� `hello, `
  for (size_t i = 0; i < 5; ++i) {
	editor.Right();
  }
  // ������� ��������� ���������: `world|`
  editor.Insert(',');
  editor.Insert(' ');
  // ������� ��������� ���������: `world, |`
  editor.Paste();
  // ������� ��������� ���������: `world, hello, |`
  editor.Left();
  editor.Left();
  //������� ��������� ���������: `world, hello|, `
  editor.Cut(3); // ����� �������� 2 �������
  // ������� ��������� ���������: `world, hello|`
  cout << editor.GetText();
}

�����

world, hello
*/