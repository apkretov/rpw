#if 0 // GITHUB @ https://github.com/avtomato/Basics-of-C-plus-plus-development-yellow-belt/blob/master/week-05/03-Programming-Assignment/Solution/figures.cpp

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "../../stdafx.h"
using namespace std;

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
};

class Rect : public Figure {
public:
	Rect(int width, int height) : width_(width), height_(height) {
	}

	string Name() const override { return "RECT"; }

	double Perimeter() const override {
		return 2 * (width_ + height_);
	}

	double Area() const override {
		return width_ * height_;
	}

private:
	int width_, height_;
};

class Triangle : public Figure {
public:
	Triangle(int side_one, int side_two, int side_three)
		: side_one_(side_one)
		, side_two_(side_two)
		, side_three_(side_three) {
	}

	string Name() const override { return "TRIANGLE"; }

	double Perimeter() const override {
		return side_one_ + side_two_ + side_three_;
	}

	double Area() const override {
		double p = Perimeter() / 2.0;
		return sqrt(p * (p - side_one_) * (p - side_two_) * (p - side_three_));
	}

private:
	int side_one_, side_two_, side_three_;
};

class Circle : public Figure {
public:
	Circle(double radius) : radius_(radius) {
	}

	string Name() const override { return "CIRCLE"; }

	double Perimeter() const override {
		return 2 * pi_ * radius_;
	}

	double Area() const override {
		return pi_ * radius_ * radius_;
	}

private:
	const double pi_ = 3.14;
	double radius_;
};

shared_ptr<Figure> CreateFigure(istream &input_stream) {
	string type;
	input_stream >> type;
	if (type == "RECT") {
		int width, height;
		input_stream >> width >> height;
		return make_shared<Rect>(width, height);
	} else if (type == "TRIANGLE") {
		int side_one, side_two, side_three;
		input_stream >> side_one >> side_two >> side_three;
		return make_shared<Triangle>(side_one, side_two, side_three);
	} else {
		int radius;
		input_stream >> radius;
		return make_shared<Circle>(radius);
	}
}

int main() {
	PRINT_FILE_LINE();

	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		} else if (command == "PRINT") {
			for (const auto &current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	return 0;
}

#endif //1

/*
Задание по программированию: Набор фигур

Вам дана функция main, которая считывает из стандартного ввода команды по работе с набором геометрических фигур:

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
	istringstream is(line);

	string command;
	is >> command;
	if (command == "ADD") {
	  figures.push_back(CreateFigure(is));
	} else if (command == "PRINT") {
	  for (const auto& current_figure : figures) {
		cout << fixed << setprecision(3)
			 << current_figure->Name() << " "
			 << current_figure->Perimeter() << " "
			 << current_figure->Area() << endl;
	  }
	}
  }
  return 0;
}

Как видно из кода, есть два вида команд:

	ADD — добавить фигуру в набор;
	PRINT — для каждой фигуры в наборе распечатать название, периметр и площадь.

Программа поддерживает три вида фигур: прямоугольник, треугольник и круг. Их добавление описывается так:

	ADD RECT width height — добавить прямоугольник с размерами width и height (например, ADD RECT 2 3).
	ADD TRIANGLE a b c — добавить треугольник со сторонами a, b и c (например, ADD TRIANGLE 3 4 5).
	ADD CIRCLE r — добавить круг радиуса r (например, ADD CIRCLE 5).

Пример работы программы
Ввод

ADD RECT 2 3
ADD TRIANGLE 3 4 5
ADD RECT 10 20
ADD CIRCLE 5
PRINT

Вывод

RECT 10.000 6.000
TRIANGLE 12.000 6.000
RECT 60.000 200.000
CIRCLE 31.400 78.500

Не меняя функцию main, реализуйте недостающие функции и классы:

	базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
	классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы;
	функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.

Гарантируется, что все команды ADD корректны; размеры всех фигур — это натуральные числа не больше 1000. В качестве значения π используйте 3,14.
Как будет тестироваться ваш код
Автоматическая проверяющая система заменит в вашей программе функцию main на ту, которая приведена в условии задачи, скомпилирует получившийся файл и прогонит на наборе тестов. Кроме того, отдельно проверяется, что функция CreateFigure возвращает объект, созданный с помощью make_shared<Rect>, если во входном потоке задан прямоугольник, объект, созданный с помощью make_shared<Circle>, если во входном потоке задан круг, и т. д.
*/