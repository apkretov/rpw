#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week3/09%20Programming%20Assignment

#undef MINE
#define GITHUB // Better.

#include <memory>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

struct Expression {
	virtual ~Expression() = default;
	virtual int Evaluate() const = 0; // возвращает численное значение выражения. Для "2*(3+4)" это будет 14.
	virtual string ToString() const = 0; // форматирует выражение как строку. Для простоты реализации, чтобы не учитывать приоритеты операций, каждый узел берётся в скобки. То есть для "2*(3+4)" этот метод вернёт "(2)*((3)+(4))".
};

using ExpressionPtr = unique_ptr<Expression>;

class ValueExpr final : public Expression {
	int val;
public:
	explicit ValueExpr(int value) : val(value) {}
	int Evaluate() const override { return val; }
	string ToString() const override { return to_string(val); }
};

#ifdef MINE
class Operation : public Expression {
	ExpressionPtr left_;
	ExpressionPtr right_;
public:
	Operation(ExpressionPtr left, ExpressionPtr right) : left_(std::move(left)), right_(std::move(right)) {}
protected:
	const ExpressionPtr &left() const { return left_; }
	const ExpressionPtr &right() const { return right_; }
};

struct SumExpr final : Operation { //TEST! //																										MINE: I added this class from the Github hint.
	using Operation::Operation;
	int Evaluate() const override { return left()->Evaluate() + right()->Evaluate(); };
	string ToString() const override { return '(' + left()->ToString() + ")+(" + right()->ToString() + ')'; }
};

struct ProductExpr final : Operation {
	using Operation::Operation;
	int Evaluate() const override { return left()->Evaluate() * right()->Evaluate(); };
	string ToString() const override { return '(' + left()->ToString() + ")*(" + right()->ToString() + ')'; }
};
#endif //MINE

#ifdef GITHUB //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week3/09%20Programming%20Assignment/solution.cpp
class BinaryExpr : public Expression { // Базовый класс бинарных операций
	ExpressionPtr left_;
	ExpressionPtr right_;
	virtual char GetSymbol() const = 0; //TEST! //																										Введение этих новых вирутальных функций позволяет уменьшить дублирование	// кода в наследниках, т.к. весь общий код собран в функциях ToString() и	// Evaluate() базового (данного) класса. А наследники просто сообщают символ	// операции и применяют её к переданным операндам.
	virtual int EvaluateOnValues(int l, int r) const = 0; //TEST! //																					MINE: I didn't make my version of this class pure virtual.
public:
	BinaryExpr(ExpressionPtr left, ExpressionPtr right) : left_(move(left)), right_(move(right)) {}
	int Evaluate() const final { return EvaluateOnValues(left_->Evaluate(), right_->Evaluate()); }

	string ToString() const final { // Здесь виртуальные функции переопределяются с ключевым словом "final".	// Это то же самое, что и "override", но только мы запрещаем дальнейшее	// их переопределение в наследниках. Действительно, мы хотим показать,	// что наследники должны переопределить закрытые функции GetSymbol() и	// EvaluateOnValues(), а сами функции ToString() и Evaluate() трогать больше	// не нужно.
		ostringstream result;
		result << '(' << left_->ToString() << ')' << GetSymbol() << '(' << right_->ToString() << ')';
		return result.str();
	}
};

class ProductExpr : public BinaryExpr { // Класс для операции умножения
	char GetSymbol() const override { return '*'; }
	int EvaluateOnValues(int left, int right) const override { return left * right; }
public:
	ProductExpr(ExpressionPtr left, ExpressionPtr right) : BinaryExpr(move(left), move(right)) {}
};

class SumExpr : public BinaryExpr { // Класс для операции сложения
	char GetSymbol() const override { return '+'; }
	int EvaluateOnValues(int left, int right) const override { return left + right; }
public:
	using BinaryExpr::BinaryExpr; // Данное выражение позволяет унаследовать конструктор из базового класса.	// Сравните с реализацией класса ProductExpr, где мы использовали "обычный"	// конструктор, который принимает ровно те же параметры, что и конструктор	// базового класса, и просто передаёт их ему. Ту же самую работу за нас	// может проделать компилятор, если мы скажем ему унаследовать конструктор.
};
#endif //GITHUB

ExpressionPtr Value(int value) { return make_unique<ValueExpr>(value); } // возвращает дерево из одного узла, представляющего целое число.
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) { return make_unique<SumExpr>(std::move(left), std::move(right)); } // возвращает новое дерево, которое представляет сумму двух переданных выражений.
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) { return make_unique<ProductExpr>(std::move(left), std::move(right)); } // возвращает новое дерево, которое представляет произведение двух переданных выражений.

string Print(const Expression *e) {
	if (!e)
		return "Null expression provided";
	stringstream output;
	output << e->ToString() << " = " << e->Evaluate();
	return output.str();
}

void Test() {
	ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
	ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14"); // 2 * (3 + 4)

	ExpressionPtr e2 = Sum(std::move(e1), Value(5));
	ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19"); // 2 * (3 + 4) + 5
	ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
	PRINT_FILE_LINE();
	TestRunner tr;
	RUN_TEST(tr, Test);
	return 0;
}
#endif //1

/*
Дерево выражений

В этой задаче мы воспользуемся умным указателем unique_ptr для управления временем жизни дерева полиморфных объектов. А конкретнее, будем работать с деревом арифметического выражения. Узлами дерева будут числа и операции.

Например, выражение "2*(3+4)" будет представлено вот таким деревом:

			*
		   / \
		  2	  +
			 / \
			3	4

В программе узлы дерева представляются объектами типов, унаследованных от интерфейса Expression, который объявлен в файле Common.h. У интерфейса есть два метода:

	Evaluate() возвращает численное значение выражения. Для нашего примера это будет 14.

	ToString() форматирует выражение как строку. Для простоты реализации, чтобы не учитывать приоритеты операций, каждый узел берётся в скобки. То есть для нашего примера этот метод вернёт "(2)*((3)+(4))".

Так как Expression — это абстрактный класс, работать с ним можно только через указатель или ссылку. Чтобы не заниматься ручным управлением памятью, будем использовать умный указатель unique_ptr. Чтобы не загромождать код выражениями unique_ptr, в файле Common.h для этого выражения предоставлен синоним ExpressionPtr.

Реализуйте функции, которые позволяют создавать такое дерево выражения. Они объявлены в файле Common.h, который приведён ниже:

	Value() возвращает дерево из одного узла, представляющего целое число.

	Sum() возвращает новое дерево, которое представляет сумму двух переданных выражений.

	Product() возвращает новое дерево, которое представляет произведение двух переданных выражений.

Таким образом, следующий код создаст дерево для выражения "2*(3+4)":

Product(Value(2), Sum(Value(3), Value(4)));

На проверку пришлите cpp-файл, который

	подключает заголовочный файл Common.h

	содержит реализацию функций Product(), Value() и Sum()

Заготовка решения содержится в файле main.cpp

#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

string Print(const Expression* e) {
if (!e) {
  return "Null expression provided";
}
stringstream output;
output << e->ToString() << " = " << e->Evaluate();
return output.str();
}

void Test() {
ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

ExpressionPtr e2 = Sum(move(e1), Value(5));
ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
TestRunner tr;
RUN_TEST(tr, Test);
return 0;
}

Header file

#pragma once

#include <memory>
#include <string>

// Ð‘Ð°Ð·Ð¾Ð²Ñ‹Ð¹ ÐºÐ»Ð°Ñ�Ñ� Ð°Ñ€Ð¸Ñ„Ð¼ÐµÑ‚Ð¸Ñ‡ÐµÑ�ÐºÐ¾Ð³Ð¾ Ð²Ñ‹Ñ€Ð°Ð¶ÐµÐ½Ð¸Ñ�
class Expression {
public:
virtual ~Expression() = default;

// Ð’Ñ‹Ñ‡Ð¸Ñ�Ð»Ñ�ÐµÑ‚ Ð·Ð½Ð°Ñ‡ÐµÐ½Ð¸Ðµ Ð²Ñ‹Ñ€Ð°Ð¶ÐµÐ½Ð¸Ñ�
virtual int Evaluate() const = 0;

// Ð¤Ð¾Ñ€Ð¼Ð°Ñ‚Ð¸Ñ€ÑƒÐµÑ‚ Ð²Ñ‹Ñ€Ð°Ð¶ÐµÐ½Ð¸Ðµ ÐºÐ°Ðº Ñ�Ñ‚Ñ€Ð¾ÐºÑƒ
// ÐšÐ°Ð¶Ð´Ñ‹Ð¹ ÑƒÐ·ÐµÐ» Ð±ÐµÑ€Ñ‘Ñ‚Ñ�Ñ� Ð² Ñ�ÐºÐ¾Ð±ÐºÐ¸, Ð½ÐµÐ·Ð°Ð²Ð¸Ñ�Ð¸Ð¼Ð¾ Ð¾Ñ‚ Ð¿Ñ€Ð¸Ð¾Ñ€Ð¸Ñ‚ÐµÑ‚Ð°
virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

// Ð¤ÑƒÐ½ÐºÑ†Ð¸Ð¸ Ð´Ð»Ñ� Ñ„Ð¾Ñ€Ð¼Ð¸Ñ€Ð¾Ð²Ð°Ð½Ð¸Ñ� Ð²Ñ‹Ñ€Ð°Ð¶ÐµÐ½Ð¸Ñ�
ExpressionPtr Value(int value);
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right);
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right);

Подсказки
Для этой задачи есть набор подсказок, которые должны помочь вам с решением. Если вам не удаётся решить задачу и вы чувствуете, что у вас кончились идеи, вы можете ими воспользоваться. Но сначала обязательно попробуйте решить задачу без подсказок.
*/