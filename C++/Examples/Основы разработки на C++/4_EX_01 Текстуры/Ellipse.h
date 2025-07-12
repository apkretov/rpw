#pragma once

#include <memory>
#include "Common.h"
using namespace std;

class Ellipse : public IShape {
public:
	unique_ptr<IShape> Clone() const override { return {}; } // Клонированная фигура использует ту же самую текстуру, что и оригинал. В дальнейшем клонированной фигуре можно задать новую текстуру.

	void SetPosition(Point) override {}
	Point GetPosition() const override { return {}; }

	void SetSize(Size) override {}
	Size GetSize() const override { return {}; }

	void SetTexture(shared_ptr<ITexture>) override {} // Задаёт новую текстуру.
	ITexture *GetTexture() const override { return {}; }

	void Draw(Image &) const override {}
};
