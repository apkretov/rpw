#if 1 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week4/01%20Programming%20Assignment

#include <cassert>
#include <memory>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#pragma region common.h //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week4/01%20Programming%20Assignment/source/common.h
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

class ITexture { // Объект текстуры должен быть удалён в тот момент, когда нет больше фигур, которые имеют данную текстуру. Это может произойти при удалении фигуры, или при назначении фигуре другой текстуры.
public:
	virtual ~ITexture() = default;
	virtual Size GetSize() const = 0;
	virtual const Image &GetImage() const = 0;
};

#ifdef ORIG
class IShape { // Интерфейс IShape описывает фигуру. 
public:
#else //MINE
struct IShape { // Интерфейс IShape описывает фигуру. 
#endif //MINE
	virtual ~IShape() = default;

	virtual unique_ptr<IShape> Clone() const = 0; // Клонированная фигура использует ту же самую текстуру, что и оригинал. В дальнейшем клонированной фигуре можно задать новую текстуру.

	virtual void SetPosition(Point) = 0;
	virtual Point GetPosition() const = 0;

	virtual void SetSize(Size) = 0;
	virtual Size GetSize() const = 0;

	virtual void SetTexture(shared_ptr<ITexture>) = 0; // Задаёт новую текстуру.
	virtual ITexture *GetTexture() const = 0;

	/* Отрисовывает текущую фигуру на заданном изображении по следующим правилам:
		Из позиции и размера фигуры формируется её ограничивающий прямоугольник
		Внутри ограничивающего прямоугольника формируется множество точек, принадлежащих фигуре - форма фигуры(если фигура это прямоугольник, то форма фигуры совпадает с ограничивающим прямоугольником)
		Текстура накладывается на ограничивающий прямоугольник таким образом, чтобы их левый верхний угол совпадал
		Заполняются пиксели изображения, попадающие внутрь формы фигуры
		Пиксели, что находятся на пересечении формы фигуры и текстуры, заполняются пикселями текстуры(если текстура отсутствует, можно считать, что она нулевого размера)
		Остальные пиксели заполняются заливкой по умолчанию - символом "." (точка)
		Если какие - то пиксели выходят за границы изображения, они просто игнорируются */
	virtual void Draw(Image &) const = 0;
};

#pragma region MINE
struct Rectangle final : IShape {
	unique_ptr<IShape> Clone() const override { return {}; } // Клонированная фигура использует ту же самую текстуру, что и оригинал. В дальнейшем клонированной фигуре можно задать новую текстуру.

	void SetPosition(Point) override {}
	Point GetPosition() const override { return {}; }

	void SetSize(Size) override {}
	Size GetSize() const override { return {}; }

	void SetTexture(shared_ptr<ITexture>) override {} // Задаёт новую текстуру.
	ITexture *GetTexture() const override { return {}; }

	void Draw(Image &) const override {}
};
#ifdef OFF
struct Ellipse : IShape {};
#endif //OFF

unique_ptr<IShape> MakeShape(ShapeType shape_type) { // Создаёт фигуру заданного вида.
	if (shape_type == ShapeType::Rectangle)
		return make_unique<Rectangle>();
	else
#ifdef OFF
		return make_unique<Ellipse>();
#else
		return {};
#endif //OFF
}
#pragma endregion MINE
#pragma endregion common.h

#pragma region textures.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week4/01%20Programming%20Assignment/source/textures.cpp
class Texture : public ITexture { 
	Image image_;
public:
	Texture(Image image) : image_(std::move(image)) {
		for (const auto &line : image_)
			assert(line.size() == image_[0].size());
	}

	Size GetSize() const override {
		auto width = static_cast<int>(image_.empty() ? 0 : image_[0].size());
		auto height = static_cast<int>(image_.size());
		return {width, height};
	}

	const Image &GetImage() const override { return image_;	}
};

unique_ptr<ITexture> MakeTextureSolid(Size size, char pixel) {
	Image image(size.height, string(size.width, pixel));
	return make_unique<Texture>(std::move(image));
}

unique_ptr<ITexture> MakeTextureCheckers(Size size, char pixel1, char pixel2) {
	Image image(size.height, string(size.width, pixel1));

	for (int i = 0; i < size.height; ++i)
		for (int j = 0; j < size.width; ++j)
			if ((i + j) % 2 != 0)
				image[i][j] = pixel2;

	return make_unique<Texture>(std::move(image));
}

unique_ptr<ITexture> MakeTextureCow() {
	Image image = {R"(^__^            )",
				   R"((oo)\_______    )",
				   R"((__)\       )\/\)",
				   R"(    ||----w |   )",
				   R"(    ||     ||   )"};
	return make_unique<Texture>(std::move(image));
}
#pragma endregion textures.cpp

#pragma region main.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week4/01%20Programming%20Assignment/source/main.cpp
class Canvas { // Автоматизированный редактор графики, который управляется через открытые методы.
public:
	using ShapeId = size_t;
	void SetSize(Size size) { size_ = size;	}

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

	void RemoveShape(ShapeId id) { shapes_.erase(GetShapeNodeById(id));	}
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
			throw out_of_range("No shape with given ID");
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

void TestSimple() {
	Canvas canvas;
	canvas.SetSize({5, 3});

	canvas.AddShape(ShapeType::Rectangle, {1, 0}, {3, 3}, nullptr);

	stringstream output;
	canvas.Print(output);

	const auto answer =
		"#######\n"
		"# ... #\n"
		"# ... #\n"
		"# ... #\n"
		"#######\n";

	ASSERT_EQUAL(answer, output.str());
}

#ifdef OFF
void TestSmallTexture() {
	Canvas canvas;
	canvas.SetSize({6, 4});

	canvas.AddShape(ShapeType::Rectangle, {1, 1}, {4, 2},
		MakeTextureSolid({3, 1}, '*'));

	stringstream output;
	canvas.Print(output);

	const auto answer =
		"########\n"
		"#      #\n"
		"# ***. #\n"
		"# .... #\n"
		"#      #\n"
		"########\n";

	ASSERT_EQUAL(answer, output.str());
}

void TestCow() {
	Canvas canvas;
	canvas.SetSize({18, 5});

	canvas.AddShape(ShapeType::Rectangle, {1, 0}, {16, 5}, MakeTextureCow());

	stringstream output;
	canvas.Print(output);

	// Ð—Ð´ÐµÑÑŒ ÑƒÐ¼ÐµÑÑ‚Ð½Ð¾ Ð¸ÑÐ¿Ð¾Ð»ÑŒÐ·Ð¾Ð²Ð°Ñ‚ÑŒ ÑÑ‹Ñ€Ñ‹Ðµ Ð»Ð¸Ñ‚ÐµÑ€Ð°Ð»Ñ‹, Ñ‚.Ðº. Ð² Ñ‚ÐµÐºÑÑ‚ÑƒÑ€Ðµ ÐµÑÑ‚ÑŒ ÑÐ¸Ð¼Ð²Ð¾Ð»Ñ‹ '\'
	const auto answer =
		R"(####################)""\n"
		R"(# ^__^             #)""\n"
		R"(# (oo)\_______     #)""\n"
		R"(# (__)\       )\/\ #)""\n"
		R"(#     ||----w |    #)""\n"
		R"(#     ||     ||    #)""\n"
		R"(####################)""\n";

	ASSERT_EQUAL(answer, output.str());
}

void TestCpp() {
	Canvas canvas;
	canvas.SetSize({77, 17});

	// Ð‘ÑƒÐºÐ²Ð° "C" ÐºÐ°Ðº Ñ€Ð°Ð·Ð½Ð¾ÑÑ‚ÑŒ Ð´Ð²ÑƒÑ… ÑÐ»Ð»Ð¸Ð¿ÑÐ¾Ð², Ð¾Ð´Ð¸Ð½ Ð¸Ð· ÐºÐ¾Ñ‚Ð¾Ñ€Ñ‹Ñ… Ð½Ð°Ñ€Ð¸ÑÐ¾Ð²Ð°Ð½ Ñ†Ð²ÐµÑ‚Ð¾Ð¼ Ñ„Ð¾Ð½Ð°
	canvas.AddShape(ShapeType::Ellipse, {2, 1}, {30, 15},
		MakeTextureCheckers({100, 100}, 'c', 'C'));
	canvas.AddShape(ShapeType::Ellipse, {8, 4}, {30, 9},
		MakeTextureSolid({100, 100}, ' '));

	// Ð“Ð¾Ñ€Ð¸Ð·Ð¾Ð½Ñ‚Ð°Ð»ÑŒÐ½Ñ‹Ðµ Ñ‡Ñ‘Ñ€Ñ‚Ð¾Ñ‡ÐºÐ¸ Ð¿Ð»ÑŽÑÐ¾Ð²
	auto h1 = canvas.AddShape(ShapeType::Rectangle, {54, 7}, {22, 3},
		MakeTextureSolid({100, 100}, '+'));
	auto h2 = canvas.DuplicateShape(h1, {30, 7});

	// Ð’ÐµÑ€Ñ‚Ð¸ÐºÐ°Ð»ÑŒÐ½Ñ‹Ðµ Ñ‡Ñ‘Ñ€Ñ‚Ð¾Ñ‡ÐºÐ¸ Ð¿Ð»ÑŽÑÐ¾Ð²
	auto v1 = canvas.DuplicateShape(h1, {62, 3});
	canvas.ResizeShape(v1, {6, 11});
	auto v2 = canvas.DuplicateShape(v1, {38, 3});

	stringstream output;
	canvas.Print(output);

	const auto answer =
		"###############################################################################\n"
		"#                                                                             #\n"
		"#            cCcCcCcCcC                                                       #\n"
		"#        CcCcCcCcCcCcCcCcCc                                                   #\n"
		"#      cCcCcCcCcCcCcCcCcCcCcC          ++++++                  ++++++         #\n"
		"#    CcCcCcCcCcCc                      ++++++                  ++++++         #\n"
		"#   CcCcCcCcC                          ++++++                  ++++++         #\n"
		"#   cCcCcCc                            ++++++                  ++++++         #\n"
		"#  cCcCcC                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
		"#  CcCcCc                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
		"#  cCcCcC                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
		"#   cCcCcCc                            ++++++                  ++++++         #\n"
		"#   CcCcCcCcC                          ++++++                  ++++++         #\n"
		"#    CcCcCcCcCcCc                      ++++++                  ++++++         #\n"
		"#      cCcCcCcCcCcCcCcCcCcCcC          ++++++                  ++++++         #\n"
		"#        CcCcCcCcCcCcCcCcCc                                                   #\n"
		"#            cCcCcCcCcC                                                       #\n"
		"#                                                                             #\n"
		"###############################################################################\n";

	ASSERT_EQUAL(answer, output.str());
}
#endif //OFF

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestSimple);
#ifdef OFF
	RUN_TEST(tr, TestSmallTexture);
	RUN_TEST(tr, TestCow);
	RUN_TEST(tr, TestCpp);
#endif //OFF

	return 0;
}
#pragma endregion main.cpp
#endif //1

/*
Текстуры

На лекциях вы познакомились с умным указателем shared_ptr, который обеспечивает совместное владение объектом. В данной задаче вам нужно будет реализовать классы фигур, которые можно отрисовывать на изображении, и которые совместно владеют заданной текстурой.

Среди доступных вам файлов вас в первую очередь будет интересовать файл Common.h. В нём приведён интерфейс IShape, который описывает фигуру. Существуют два вида фигур: прямоугольник и эллипс. Они указаны в перечислении ShapeType. Ваша задача реализовать функцию MakeShape, которая создаёт фигуру заданного вида.

Интерфейс IShape позволяет запрашивать и задавать ряд свойств фигуры: позицию, размер и текстуру. Также он позволяет клонировать фигуру с помощью метода Clone(). Это похоже на то, как если бы вы выбрали в редакторе графики фигуру и нажали Ctrl+C и Ctrl+V. Идея в том, что склонированная фигура использует ту же самую текстуру, что и оригинал. Это удобно, т.к. в общем случае текстура может занимать много памяти. Разумеется, в дальнейшем склонированной фигуре можно задать новую текстуру.

Объект текстуры должен быть удалён в тот момент, когда нет больше фигур, которые имеют данную текстуру. Это может произойти при удалении фигуры, или при назначении фигуре другой текстуры.

Кроме того, интерфейс IShape позволяет отрисовать текущую фигуру на заданном изображении с помощью метода Draw(). Отрисовка происходит по следующим правилам: alt text

	Из позиции и размера фигуры формируется её ограничивающий прямоугольник

	Внутри ограничивающего прямоугольника формируется множество точек, принадлежащих фигуре - форма фигуры (если фигура это прямоугольник, то форма фигуры совпадает с ограничивающим прямоугольником)

	Текстура накладывается на ограничивающий прямоугольник таким образом, чтобы их левый верхний угол совпадал

	Заполняются пиксели изображения, попадающие внутрь формы фигуры

	Пиксели, что находятся на пересечении формы фигуры и текстуры, заполняются пикселями текстуры (если текстура отсутствует, можно считать, что она нулевого размера)

	Остальные пиксели заполняются заливкой по умолчанию - символом "." (точка)

	Если какие-то пиксели выходят за границы изображения, они просто игнорируются

В качестве примера правильной отрисовки следует посмотреть тесты, вызываемые из функции main() в файле main.cpp. В тестах создаётся канва (экземпляр класса Canvas). Канва это по сути автоматизированный редактор графики, который управляется через открытые методы. Например, метод AddShape() добавляет новую фигуру с помощью функции MakeShape(), которую вам нужно реализовать. А метод DuplicateShape() клонирует существующую фигуру, вызывая метод Clone(), который вам, опять же, нужно будет реализовать. Таким образом, с помощью тестов можно будет проверить корректность своей реализации. Однако будьте осторожны - как и в других заданиях, успешное прохождение открытых тестов есть необходимое, но не достаточное условие корректности вашей реализации. Своё решение опишите в файле Solution.cpp и присылайте его на проверку.
Замечание
Вычислить целочисленную форму эллипса можно по-разному, поэтому для определённости воспользуйтесь предоставленной функцией IsPointInEllipse().
*/