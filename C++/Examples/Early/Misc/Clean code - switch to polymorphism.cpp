#ifndef ON

#undef SWITCH
#undef ENUM
#define POLYMORPHISM

#define _USE_MATH_DEFINES // For M_PI
#include <cmath> // For M_PI
#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

#ifdef SWITCH
enum class ShapeType {
	Circle,
	Rectangle,
	Triangle
};

double calculateArea(ShapeType shapeType, double dimension1, double dimension2 = 0) {
	switch (shapeType) {
		case ShapeType::Circle:
			return M_PI * dimension1 * dimension1; // Area of a circle
		case ShapeType::Rectangle:
			return dimension1 * dimension2; // Area of a rectangle
		case ShapeType::Triangle:
			return 0.5 * dimension1 * dimension2; // Area of a triangle
		default:
			throw invalid_argument("Unknown shape type");
	}
}

int main() {
	print_file_line();

	double circleArea = calculateArea(ShapeType::Circle, 5.0); // Calculate areas of different shapes
	double rectangleArea = calculateArea(ShapeType::Rectangle, 4.0, 6.0);
	double triangleArea = calculateArea(ShapeType::Triangle, 3.0, 4.0);

	cout << "Area of Circle: " << circleArea << endl; // Print areas
	cout << "Area of Rectangle: " << rectangleArea << endl;
	cout << "Area of Triangle: " << triangleArea << endl;

	return 0;
}
#endif //SWITCH

#ifdef ENUM
#include <iostream>
#include <cmath> // ��� M_PI
#include <functional> // ��� function

enum class ShapeType { // ����������� enum class � ������-���������
	Circle,
	Rectangle,
	Triangle
};

const function<double(double, double)> areaFunctions[] = { // ����������� ������� ������-������� ��� ���������� �������
	[](double radius, double) { return M_PI * radius * radius; }, // ������� �����
	[](double width, double height) { return width * height; }, // ������� ��������������
	[](double base, double height) { return 0.5 * base * height; } // ������� ������������
};

double calculateArea(ShapeType shapeType, double dimension1, double dimension2 = 0) { // ������� ��� ���������� ������� ������
	return areaFunctions[static_cast<size_t>(shapeType)](dimension1, dimension2);
}

int main() {
	print_file_line();

	cout << "Area of Circle: " << calculateArea(ShapeType::Circle, 5.0) << endl; // ���������� � ����� ��������
	cout << "Area of Rectangle: " << calculateArea(ShapeType::Rectangle, 4.0, 6.0) << endl;
	cout << "Area of Triangle: " << calculateArea(ShapeType::Triangle, 3.0, 4.0) << endl;

	return 0;
}
#endif //ENUM

#ifdef POLYMORPHISM
class Shape {
public:
	virtual ~Shape() = default; // Virtual destructor for proper cleanup
	virtual double area() const = 0; // Pure virtual function
};

class Circle : public Shape {
	double radius;
public:
	explicit Circle(double r) : radius(r) {}
	double area() const final {	return M_PI * radius * radius; } 
};

class Rectangle : public Shape {
	double width, height;
public:
	Rectangle(double w, double h) : width(w), height(h) {}
	double area() const final {	return width * height; }
};

class Triangle : public Shape {
	double base, height;
public:
	Triangle(double b, double h) : base(b), height(h) {}
	double area() const final { return 0.5 * base * height; }
};

void printArea(const Shape &shape) {
	cout << "Area: " << shape.area() << '\n';
}

int main() {
	print_file_line();

	vector<unique_ptr<Shape>> shapes;
	shapes.push_back(make_unique<Circle>(5.0));
	shapes.push_back(make_unique<Rectangle>(4.0, 6.0));
	shapes.push_back(make_unique<Triangle>(3.0, 4.0));
	for (const auto &shape : shapes) // Calculate and print areas
		printArea(*shape);
}
#endif //POLYMORPHISM
#endif //ON