#pragma once

#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include "Ellipse.h"
#include "IShape.h"
#include "Rectangle.h"
using namespace std;

struct Point {
	int x;
	int y;
};

struct Size {
	int width;
	int height;
};

inline bool IsPointInEllipse(Point p, Size size) { // Вычисляет (можно по-разному) целочисленную форму эллипса.
	double x = (p.x + 0.5) / (size.width / 2.0) - 1;
	double y = (p.y + 0.5) / (size.height / 2.0) - 1;
	return x * x + y * y <= 1;
}

using Image = vector<string>;

enum class ShapeType { Rectangle, Ellipse }; // Существуют два вида фигур: прямоугольник и эллипс.

unique_ptr<IShape> MakeShape(ShapeType shape_type) { // Создаёт фигуру заданного вида.
	if (shape_type == ShapeType::Rectangle)
		return make_unique<Rectangle>();
	else if (shape_type == ShapeType::Rectangle)
		return make_unique<Ellipse>();
	else
		throw std::invalid_argument("Unknown shape type");
}