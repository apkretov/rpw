#pragma once

#include "common.h"
#include <map>
#include <iostream>
#include "IShape.h"
#include "ITexture.h"
#include "Canvas.h"
using namespace std;

class Canvas { // Автоматизированный редактор графики, который управляется через открытые методы.
public:
	using ShapeId = size_t;
	void SetSize(Size size) { size_ = size; }

	ShapeId AddShape(ShapeType shape_type, Point position, Size size, unique_ptr<ITexture> texture) { // Добавляет новую фигуру с помощью функции MakeShape().
		auto shape = MakeShape(shape_type);
		shape->SetPosition(position);
		shape->SetSize(size);
		shape->SetTexture(std::move(texture));
		return InsertShape(std::move(shape));
	}

	ShapeId DuplicateShape(ShapeId source_id, Point target_position) { // Клонирует существующую фигуру, вызывая метод Clone().
		auto shape = GetShapeNodeById(source_id)->second->Clone();
		shape->SetPosition(target_position);
		return InsertShape(std::move(shape));
	}

	void RemoveShape(ShapeId id) { shapes_.erase(GetShapeNodeById(id)); }
	void MoveShape(ShapeId id, Point position) { GetShapeNodeById(id)->second->SetPosition(position); }
	void ResizeShape(ShapeId id, Size size) { GetShapeNodeById(id)->second->SetSize(size); }
	int GetShapesCount() const { return static_cast<int>(shapes_.size()); }

	void Print(ostream &output) const {
		Image image(size_.height, string(size_.width, ' '));

		for (const auto &[id, shape] : shapes_)
			shape->Draw(image);

		output << '#' << string(size_.width, '#') << "#\n";
		for (const auto &line : image)
			output << '#' << line << "#\n";
		output << '#' << string(size_.width, '#') << "#\n";
	}
private:
	using Shapes = map<ShapeId, unique_ptr<IShape>>;

	Shapes::iterator GetShapeNodeById(ShapeId id) {
		auto it = shapes_.find(id);
		if (it == shapes_.end()) {
			throw std::out_of_range("No shape with given ID");
		}
		return it;
	}

	ShapeId InsertShape(unique_ptr<IShape> shape) {
		shapes_[current_id_] = std::move(shape);
		return current_id_++;
	}

	Size size_ = {};
	ShapeId current_id_ = 0;
	Shapes shapes_;
};
