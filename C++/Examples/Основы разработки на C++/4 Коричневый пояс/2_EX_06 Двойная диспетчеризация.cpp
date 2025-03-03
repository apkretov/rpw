#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week2/06%20Programming%20Assignment

#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#pragma region game_object.h //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/06%20Programming%20Assignment/source/game_object.h
class Unit;
class Building;
class Tower;
class Fence;

struct GameObject {
	virtual ~GameObject() = default;
	virtual bool Collide(const GameObject &that) const = 0;
	virtual bool CollideWith(const Unit &that) const = 0;
	virtual bool CollideWith(const Building &that) const = 0;
	virtual bool CollideWith(const Tower &that) const = 0;
	virtual bool CollideWith(const Fence &that) const = 0;
};

bool Collide(const GameObject &first, const GameObject &second);
#pragma endregion //game_object.h

#pragma region geo2d.h //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/06%20Programming%20Assignment/source/geo2d.h
#include <cstdint>

namespace geo2d {
	struct Point {
		int x, y;
	};

	uint64_t DistanceSquared(Point p1, Point p2);

	struct Vector {
		int x, y;
		Vector(int xx, int yy) : x(xx), y(yy) {}
		Vector(Point from, Point to) : x(to.x - from.x), y(to.y - from.y) {}
	};

	int64_t operator*(Vector lhs, Vector rhs);
	int64_t ScalarProduct(Vector lhs, Vector rhs);

	struct Segment {
		Point p1, p2;
	};

	class Rectangle {
		int x_left, x_right;
		int y_bottom, y_top;
	public:
		Rectangle(Point p1, Point p2);

		int Left() const { return x_left; }
		int Right() const { return x_right; }
		int Top() const { return y_top; }
		int Bottom() const { return y_bottom; }

		Point BottomLeft() const { return { x_left, y_bottom}; }
		Point BottomRight() const { return { x_right, y_bottom}; }
		Point TopRight() const { return { x_right, y_top}; }
		Point TopLeft() const { return { x_left, y_top}; }
	};

	struct Circle {
		Point center;
		uint32_t radius;
	};

	bool Collide(Point p, Point q);
	bool Collide(Point p, Segment s);
	bool Collide(Point p, Rectangle r);
	bool Collide(Point p, Circle c);
	bool Collide(Rectangle r, Point p);
	bool Collide(Rectangle r, Segment s);
	bool Collide(Rectangle r1, Rectangle r2);
	bool Collide(Rectangle r, Circle c);
	bool Collide(Segment s, Point p);
	bool Collide(Segment s1, Segment s2);
	bool Collide(Segment s, Rectangle r);
	bool Collide(Segment s, Circle c);
	bool Collide(Circle c, Point p);
	bool Collide(Circle c, Rectangle r);
	bool Collide(Circle c, Segment s);
	bool Collide(Circle c1, Circle c2);

}
#pragma endregion //geo2d.h

#pragma region geo2d.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/06%20Programming%20Assignment/source/geo2d.cpp
#include <cmath>

namespace geo2d {
	Rectangle::Rectangle(Point p1, Point p2) : x_left(min(p1.x, p2.x)), x_right(max(p1.x, p2.x)), y_bottom(min(p1.y, p2.y)), y_top(max(p1.y, p2.y)) {}

	template <typename T>
	T Sqr(T x) { 
		return x * x; 
	}

	template <typename T>
	T Sign(T x) { 
		return x != 0 ? x / abs(x) : 0; 
	}

	uint64_t DistanceSquared(Point p1, Point p2) {
		int64_t diff_x = p1.x - p2.x;
		int64_t diff_y = p1.y - p2.y;

		uint64_t result = Sqr(diff_x);
		result += Sqr(diff_y);

		return result;
	}

	int64_t operator*(Vector lhs, Vector rhs) {
		return static_cast<int64_t>(lhs.x) * rhs.y - static_cast<int64_t>(rhs.x) * lhs.y;
	}

	int64_t ScalarProduct(Vector lhs, Vector rhs) {
		return static_cast<int64_t>(lhs.x) * rhs.x + static_cast<int64_t>(lhs.y) * rhs.y;
	}

	bool Collide(Point p, Point q) {
		return p.x == q.x && p.y == q.y;
	}

	bool Collide(Point p, Segment s) {
		const Vector v1{s.p1, p};
		const Vector v2{s.p2, p};

		return ScalarProduct(v1, Vector{s.p1, s.p2}) >= 0 &&
			ScalarProduct(v2, Vector{s.p2, s.p1}) >= 0 &&
			v1 * Vector{s.p1, s.p2} == 0;
	}

	bool Collide(Point p, Rectangle r) {
		return r.Left() <= p.x && p.x <= r.Right() &&
			r.Bottom() <= p.y && p.y <= r.Top();
	}

	bool Collide(Point p, Circle c) {
		return DistanceSquared(p, c.center) <= Sqr<uint64_t>(c.radius);
	}

	bool Collide(Segment s1, Segment s2);
	bool Collide(Circle c, Segment s);

	bool Collide(Rectangle r, Point p) { return Collide(p, r); }
	bool Collide(Rectangle r, Segment s) {
		return Collide(s.p1, r) ||
			Collide(s.p2, r) ||
			Collide(s, Segment{r.BottomLeft(), r.BottomRight()}) ||
			Collide(s, Segment{r.BottomRight(), r.TopRight()}) ||
			Collide(s, Segment{r.TopRight(), r.TopLeft()}) ||
			Collide(s, Segment{r.TopLeft(), r.BottomLeft()});
	}

	bool Collide(Rectangle r1, Rectangle r2) {
		auto max_left = max(r1.Left(), r2.Left());
		auto min_right = min(r1.Right(), r2.Right());
		auto max_bottom = max(r1.Bottom(), r2.Bottom());
		auto min_top = min(r1.Top(), r2.Top());
		return min_right >= max_left && min_top >= max_bottom;
	}

	bool Collide(Rectangle r, Circle c) {
		return Collide(c.center, r) ||
			Collide(c, Segment{r.BottomLeft(), r.BottomRight()}) ||
			Collide(c, Segment{r.BottomRight(), r.TopRight()}) ||
			Collide(c, Segment{r.TopRight(), r.TopLeft()}) ||
			Collide(c, Segment{r.TopLeft(), r.BottomLeft()});
	}

	bool Collide(Segment s, Point p) { return Collide(p, s); }

	bool Collide(Segment s1, Segment s2) {
		const Rectangle first_bounding_box(s1.p1, s1.p2);
		const Rectangle second_bounding_box(s2.p1, s2.p2);
		if (!Collide(first_bounding_box, second_bounding_box)) {
			return false;
		}

		const Vector v1{s1.p1, s1.p2};
		const Vector v2{s2.p1, s2.p2};

		return Sign(v1 * Vector{s1.p1, s2.p1}) * Sign(v1 * Vector{s1.p1, s2.p2}) <= 0 &&
			Sign(v2 * Vector{s2.p1, s1.p1}) * Sign(v2 * Vector{s2.p1, s1.p2}) <= 0;
	}

	bool Collide(Segment s, Rectangle r) { return Collide(r, s); }
	bool Collide(Segment s, Circle c) { return Collide(c, s); }

	bool Collide(Circle c, Point p) { return Collide(p, c); }
	bool Collide(Circle c, Rectangle r) { return Collide(r, c); }

	bool Collide(Circle c, Segment s) {
		if (
			ScalarProduct(Vector{s.p1, s.p2}, Vector{s.p1, c.center}) >= 0 &&
			ScalarProduct(Vector{s.p2, s.p1}, Vector{s.p2, c.center}) >= 0
			) {
			// Высота треугольника (s.p1, s.p2, c.center), проведённая из c.center,
			// попадает на отрезок (s.p1, s.p2).
			//
			// Удвоенная площадь треугольника (s.p1, s.p2, c.center) равна модулю
			// векторного произведения ниже, обозначим её 2S. Высота этого треугольника,
			// проведённая из c.center, равна 2S / |s.p1, s.p2|. Чтобы остаться в целых
			// числах, возведём сравниваемые величины в квадрат и сравним (2S)^ 2 с
			// R^2 * |s.p1, s.p2|^2
			uint64_t double_triangle_square = abs(Vector{s.p1, s.p2} *Vector{s.p1, c.center});
			return Sqr(double_triangle_square) <= Sqr<uint64_t>(c.radius) * DistanceSquared(s.p1, s.p2);
		} else {
			auto d = min(DistanceSquared(c.center, s.p1), DistanceSquared(c.center, s.p2));
			return d <= Sqr<uint64_t>(c.radius);
		}
	}

	bool Collide(Circle c1, Circle c2) {
		return DistanceSquared(c1.center, c2.center) <= Sqr<uint64_t>(c1.radius + c2.radius);
	}
}
#pragma endregion //geo2d.cpp

#pragma region collide.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/06%20Programming%20Assignment/source/collide.cpp
#include <memory>

#pragma region GameObject classes
/* @ file:///C:/_/My_Docs/oESE3vYzEeiaxBKyA9PBAg_a0d21e50f63311e89aa295b2bbe8221e__________-4.pdf
CRTP как способ избежать дублирования кода
	Вы можете задуматься, как избежать дублирования кода, переопределяя метод Collide для
	классов Unit, Building, Tower и Fence, ведь все эти реализации выглядят абсолютно
	одинаково — отличие состоит только в типе указателя this.Помочь в этом может слегка
	нетривиальная идиома CRTP — Curiously recurring template pattern:
// Создаём шаблон класса Collider, только в нём будет переопределяться метод Collide
template <typename T>
struct Collider : GameObject {
	bool Collide(const GameObject &that) const final {
		// Статически приводим тип *this к типу const T&, потому что мы знаем,
		// что T — наш наследник (см. ниже)
		return that.CollideWith(static_cast<const T &>(*this));
	}
};
// Наследуем класс Unit от класса Collider<Unit>, который в свою очередь
// наследуется от GameObject.
class Unit final : public Collider<Unit> {
public:
	Unit(geo2d::Point position);
	// Переопределения методов CollideWith — метод Collide переопределять уже не нужно
	bool CollideWith(const Unit &that) const override;
	bool CollideWith(const Building &that) const override;
	bool CollideWith(const Tower &that) const override;
	bool CollideWith(const Fence &that) const override;
private:
	// ...
};
Конечно, можно просто накопипастить перегрузки метода Collide для каждого класса или
	воспользоваться макросами, но применение CRTP в данном случае избавляет от
	дублирования кода и обладает большей типобезопасностью.
*/
template <typename T>
struct Collider : GameObject { //TEST!!
	bool Collide(const GameObject &that) const final { 
		if (this != &that)
			/* @ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/06%20Programming%20Assignment/Tips/oEQ2kPYzEeilxxL_ZeRz_A_a0cf5f30f63311e8b293a14f8879aaef__________-3.pdf
			Передача динамического типа в метод другого объекта
			Рассмотрим вызов first.Collide(second) в реализации функции bool Collide(const
			GameObject& first, const GameObject& second) . Это виртуальный вызов. Если для каждого из
			четырёх имеющихся у нас классов, мы выполним его перегрузку, то внутри неё
			указатель this будет иметь тип, соответствующий динамическому типу параметра first .
			Например,

			class Unit : public GameObject {
			public:
				explicit Unit(geo2d::Point position);
				bool Collide(const GameObject &that) const override {
					// указатель this в этом методе имеет тип Unit*
				}
			};

			Следовательно, мы можем «передать» этот тип в объект that , вызвав метод CollideWith :

			bool Unit::Collide(const GameObject &that) const {
				return that.CollideWith(*this); // Вызываем виртуальный метод GameObject::CollideWith(cons
			}

			Делаем такую перегрузку для каждого класса Unit , Building , Tower , Fence и двойная
			диспетчеризация готова: первый виртуальный вызов мы делаем,
			вызывая GameObject::Collide из функции Collide , а второй —
			вызывая GameObject::CollideWith(*this) внутри переопределения
			метода Collide для каждого классах-наследника GameObject.
			*/
			return that.CollideWith(static_cast<const T &>(*this)); //TEST!
		else
			return true;
	}
};

class Unit final : public Collider<Unit> {  // Определите классы Unit, Building, Tower и Fence так, чтобы они наследовались от // GameObject и реализовывали его интерфейс.
	geo2d::Point position_;
public:
	explicit Unit(geo2d::Point position) : position_(position) {}
	bool CollideWith(const Unit &that) const override;
	bool CollideWith(const Building &that) const override;
	bool CollideWith(const Tower &that) const override;
	bool CollideWith(const Fence &that) const override;
	const geo2d::Point &GetPosition() const;
};

class Building final : public Collider<Building> {
	geo2d::Rectangle position_;
public:
	explicit Building(geo2d::Rectangle geometry) : position_(geometry) {}
	bool CollideWith(const Unit &that) const override;
	bool CollideWith(const Building &that) const override;
	bool CollideWith(const Tower &that) const override;
	bool CollideWith(const Fence &that) const override;
	const geo2d::Rectangle &GetPosition() const;
};

class Tower final : public Collider<Tower> {
	geo2d::Circle position_;
public:
	explicit Tower(geo2d::Circle geometry) : position_(geometry) {}
	bool CollideWith(const Unit &that) const override;
	bool CollideWith(const Building &that) const override;
	bool CollideWith(const Tower &that) const override;
	bool CollideWith(const Fence &that) const override;
	const geo2d::Circle &GetPosition() const;
};

class Fence final : public Collider<Fence> {
	geo2d::Segment position_;
public:
	explicit Fence(geo2d::Segment geometry) : position_(geometry) {}
	bool CollideWith(const Unit &that) const override;
	bool CollideWith(const Building &that) const override;
	bool CollideWith(const Tower &that) const override;
	bool CollideWith(const Fence &that) const override;
	const geo2d::Segment &GetPosition() const;
};

#define COLLIDE_WITH_IMPL(Class, Type) \
    bool Class::CollideWith(const Type &that) const { \
        return geo2d::Collide(position_, that.GetPosition()); \
    } //TEST

#define COLLIDE_WITH_ALL(Class, PositionType) \
    COLLIDE_WITH_IMPL(Class, Unit) \
    COLLIDE_WITH_IMPL(Class, Building) \
    COLLIDE_WITH_IMPL(Class, Tower) \
    COLLIDE_WITH_IMPL(Class, Fence) \
    const PositionType &Class::GetPosition() const { return position_; }

COLLIDE_WITH_ALL(Unit, geo2d::Point) 
COLLIDE_WITH_ALL(Building, geo2d::Rectangle)
COLLIDE_WITH_ALL(Tower, geo2d::Circle)
COLLIDE_WITH_ALL(Fence, geo2d::Segment)
#pragma endregion //GameObject classes

bool Collide(const GameObject &first, const GameObject &second) { // Реализуйте функцию Collide из файла GameObject.h
	return first.Collide(second);
}

#pragma region soltution.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/06%20Programming%20Assignment/solution.cpp
void TestAddingNewObjectOnMap() {
	// Юнит-тест моделирует ситуацию, когда на игровой карте уже есть какие-то объекты,
	// и мы хотим добавить на неё новый, например, построить новое сдание или башню.
	// Мы можем его добавить, только если он не пересекается ни с одним из существующих.
	using namespace geo2d;

	const vector<shared_ptr<GameObject>> game_map = {
			make_shared<Unit>(Point{3, 3}),
			make_shared<Unit>(Point{5, 5}),
			make_shared<Unit>(Point{3, 7}),
			make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
			make_shared<Tower>(Circle{Point{9, 4}, 1}),
			make_shared<Tower>(Circle{Point{10, 7}, 1}),
			make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
	};

	for (size_t i = 0; i < game_map.size(); ++i) {
		Assert(
			Collide(*game_map[i], *game_map[i]),
			"An object doesn't collide with itself: " + to_string(i)
		);

		for (size_t j = 0; j < i; ++j) {
			Assert(
				!Collide(*game_map[i], *game_map[j]),
				"Unexpected collision found " + to_string(i) + ' ' + to_string(j)
			);
		}
	}

	auto new_warehouse = make_shared<Building>(Rectangle{{4, 3}, {9, 6}});
	ASSERT(!Collide(*new_warehouse, *game_map[0]));
	ASSERT(Collide(*new_warehouse, *game_map[1]));
	ASSERT(!Collide(*new_warehouse, *game_map[2]));
	ASSERT(Collide(*new_warehouse, *game_map[3]));
	ASSERT(Collide(*new_warehouse, *game_map[4]));
	ASSERT(!Collide(*new_warehouse, *game_map[5]));
	ASSERT(!Collide(*new_warehouse, *game_map[6]));

	auto new_defense_tower = make_shared<Tower>(Circle{{8, 2}, 2});
	ASSERT(!Collide(*new_defense_tower, *game_map[0]));
	ASSERT(!Collide(*new_defense_tower, *game_map[1]));
	ASSERT(!Collide(*new_defense_tower, *game_map[2]));
	ASSERT(Collide(*new_defense_tower, *game_map[3]));
	ASSERT(Collide(*new_defense_tower, *game_map[4]));
	ASSERT(!Collide(*new_defense_tower, *game_map[5]));
	ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

void TestVectorProduct() { // Тесты ниже не являются частью решения. Они нужны для отладки!!!
	using geo2d::Vector;
	ASSERT_EQUAL((Vector{1, 0} *Vector{2, 0}), 0);
	ASSERT_EQUAL((Vector{1, 0} *Vector{-1, 0}), 0);
	ASSERT((Vector{1, 0} *Vector{1, 1} > 0));
	ASSERT((Vector{1, 1} *Vector{1, 0} < 0));
	ASSERT((Vector{1, 0} *Vector{-1, 1} > 0));
}

void TestPointSegmentCollide() {
	using geo2d::Point;
	using geo2d::Segment;

	ASSERT(geo2d::Collide(Point{1, 0}, Segment{{0, 0}, {10, 0}}));
	ASSERT(geo2d::Collide(Point{0, 0}, Segment{{0, 0}, {10, 0}}));
	ASSERT(geo2d::Collide(Point{10, 0}, Segment{{0, 0}, {10, 0}}));
	ASSERT(geo2d::Collide(Point{3, 3}, Segment{{0, 0}, {10, 10}}));

	ASSERT(!geo2d::Collide(Point{-1, 0}, Segment{{0, 0}, {10, 0}}));
	ASSERT(!geo2d::Collide(Point{11, 0}, Segment{{0, 0}, {10, 0}}));
	ASSERT(!geo2d::Collide(Point{1, 1}, Segment{{0, 0}, {10, 0}}));
	ASSERT(!geo2d::Collide(Point{5, 5}, Segment{{0, 0}, {10, 0}}));
	ASSERT(!geo2d::Collide(Point{-5, 0}, Segment{{0, 0}, {10, 0}}));
	ASSERT(!geo2d::Collide(Point{5, -1}, Segment{{0, 0}, {10, 0}}));
}

void TestPointRectangleCollide() {
	using geo2d::Point;
	using geo2d::Rectangle;

	const Rectangle r{{0, 0}, {5, 3}};
	ASSERT(geo2d::Collide(Point{0, 0}, r));
	ASSERT(geo2d::Collide(Point{5, 0}, r));
	ASSERT(geo2d::Collide(Point{5, 3}, r));
	ASSERT(geo2d::Collide(Point{0, 3}, r));
	ASSERT(geo2d::Collide(Point{2, 2}, r));
	ASSERT(geo2d::Collide(Point{1, 3}, r));

	ASSERT(!geo2d::Collide(Point{-1, 0}, r));
	ASSERT(!geo2d::Collide(Point{0, -1}, r));
	ASSERT(!geo2d::Collide(Point{0, 4}, r));
	ASSERT(!geo2d::Collide(Point{6, 0}, r));
	ASSERT(!geo2d::Collide(Point{5, 4}, r));
	ASSERT(!geo2d::Collide(Point{6, 3}, r));
	ASSERT(!geo2d::Collide(Point{2, 8}, r));
}

void TestSegmentSegmentCollide() {
	using geo2d::Segment;
	ASSERT(geo2d::Collide(Segment{{0, 0}, {2, 2}}, Segment{{2, 0}, {0, 2}}));
	ASSERT(geo2d::Collide(Segment{{0, 0}, {2, 2}}, Segment{{2, 0}, {1, 1}}));
	ASSERT(geo2d::Collide(Segment{{0, 0}, {10, 6}}, Segment{{5, 3}, {15, 9}}));
	ASSERT(geo2d::Collide(Segment{{0, 0}, {6, 2}}, Segment{{4, 2}, {6, 0}}));
	ASSERT(geo2d::Collide(Segment{{0, 0}, {6, 2}}, Segment{{6, 2}, {6, 3}}));

	ASSERT(!geo2d::Collide(Segment{{0, 0}, {2, 2}}, Segment{{2, 0}, {1, 0}}));
	ASSERT(!geo2d::Collide(Segment{{0, 0}, {10, 6}}, Segment{{5, 4}, {15, 10}}));
	ASSERT(!geo2d::Collide(Segment{{0, 0}, {6, 2}}, Segment{{4, 1}, {6, 0}}));
}

void TestSegmentCircleCollide() {
	using geo2d::Circle;
	using geo2d::Segment;
	const Circle c{{0, 0}, 4};

	ASSERT(geo2d::Collide(c, Segment{{0, 0}, {1, 0}}));
	ASSERT(geo2d::Collide(c, Segment{{3, 1}, {10, 1}}));
	ASSERT(geo2d::Collide(c, Segment{{-5, 2}, {5, 2}}));
	ASSERT(geo2d::Collide(c, Segment{{-5, 3}, {5, 3}}));
	ASSERT(geo2d::Collide(c, Segment{{-5, 4}, {5, 4}}));
	ASSERT(geo2d::Collide(c, Segment{{3, 1}, {4, 5}}));
	ASSERT(geo2d::Collide(c, Segment{{5, 0}, {-2, 4}}));

	ASSERT(!geo2d::Collide(c, Segment{{4, 1}, {4, 5}}));
	ASSERT(!geo2d::Collide(c, Segment{{-5, 5}, {5, 5}}));
	ASSERT(!geo2d::Collide(c, Segment{{4, 4}, {5, 4}}));
	ASSERT(!geo2d::Collide(Circle{{10, 7}, 1}, Segment{{7, 3}, {9, 8}}));
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestAddingNewObjectOnMap);
	RUN_TEST(tr, TestVectorProduct);
	RUN_TEST(tr, TestPointSegmentCollide);
	RUN_TEST(tr, TestPointRectangleCollide);
	RUN_TEST(tr, TestSegmentSegmentCollide);
	RUN_TEST(tr, TestSegmentCircleCollide);

	return 0;
}
#pragma endregion
#pragma endregion //collide.cpp
#endif //1

/*
Двойная диспетчеризация
Теория — статический и динамический тип указателя или ссылки на объект

Рассмотрим простой код

struct Parent {
  virtual string Name() const { return "Parent"; }
};

struct Child : Parent {
  virtual string Name() const override { return "Child"; }
};

void Print(const Parent& object) {
  cout << object.Name() << '\n';
}

int main() {
  Print(Parent());
  Print(Child());
}

Если у вас спросить, какой тип имеет параметр object функции Print, вы наверняка ответите «const Parent&» и будете правы. А если мы спросим, на объект какого типа ссылается параметр object, то правильным будет ответ: «Зависит от того, какой объект передали в функцию Print».

Получается, с одной стороны, мы знаем, какой тип имеет параметер object, но с другой стороны, мы не можем точно сказать, на объект какого типа он ссылается. В этом и состоит разница между статическим и динамическим типом ссылки (или указателя) на класс, у которого могут быть наследники.

Статический тип ссылки — это тип, известный на этапе компиляции. В нашем примере статический тип параметра object — это const Parent&.

Динамический тип ссылки — это тип объекта, на который она ссылается в данный момент времени. Динамическим типом параметра object во время первого вызова функции Print будет const Parent, во время второго вызова функции Print — const Child.
Теория — тип указателя this в классах-наследниках

Теперь давайте рассмотрим другой пример. Как вы думаете, что будет выведено на экран?

struct Parent;
struct Child;

void PrintType(Parent*) { cout << "Parent\n"; }
void PrintType(Child*) { cout << "Child\n"; }

struct Parent {
  virtual void Print() { PrintType(this); }
};

struct Child : Parent {
};

int main() {
  Child().Print();
}

Вариантов, на самом деле, всего два, и правильный — это «Parent». Несмотря на то, что мы создали объект типа Child, указатель this внутри методов класса Parent имеет тип Parent*, а не Child*, как могло бы показаться. И это логично, потому что

	выбор, какая из двух функций PrintType будет вызвана из метода Parent::Print, осуществляется на этапе компиляции; в этот момент компилятор наверняка знает только одно — что указатель this будет указывать на объект класса Parent

	виртуальными (то есть зависящими от динамического типа) в C++ могут быть только методы, а this — это лишь указатель.

Наконец, рассмотрим ещё один пример и снова зададимся вопросом, что он выведет:

struct Parent;
struct Child;

void PrintType(Parent*) { cout << "Parent\n"; }
void PrintType(Child*) { cout << "Child\n"; }

struct Parent {
  virtual void Print() { PrintType(this); }
};

struct Child : Parent {
  void Print() override { PrintType(this); }
};

int main() {
  Child().Print();
}

Мы переопределили метод Print в классе Child, оставив у него точь-в-точь такую же реализацию, какая была в Parent::Print. Но кое-что изменилось — тип указателя this. Внутри метода Child::Print он имеет тип Child*. Причина та же — когда компилятор обрабатывает метод Child::Print, он знает, что this точно будет указывать на объект класса Child.

Итак, главный вывод — this всегда имеет тип указателя на тот класс, в методе которого он используется.
Условие задачи

Из лекций мы узнали, что this всегда указывает на текущий объект класса, а также, что он является неявным параметром всех его методов. Кроме того, мы только что познакомились с понятиями статического и динамического типов ссылки (или указателя). В этой задаче мы объединим эти знания, чтобы реализовать так называемую двойную диспетчеризацию — мы напишем функцию, которая ведёт себя по-разному в зависимости от динамических типов двух объектов, которые в неё переданы.

Представим, что мы пишем движок для классической компьютерной стратегии: игроки строят города, формируют армию, а потом сражаются друг с другом. В нашей игре есть несколько объектов:

	юниты — это солдаты, рабочие, кавалеристы и т.д.

	здания — фабрики, заводы, казармы и т.д.

	башни и стены — защитные сооружения для обороны своего города

Мы работаем над функциональностью размещения новых объектов на игровой карте. Допустим, мы хотим построить новое здание. Мы начинаем искать на карте место, где его можно разместить, а графический интерфейс игры нам в этом помогает. Здание можно построить в том месте карты, где нет других объектов. Если в текущей позиции здание пересекается с каким-то из объектов, то интерфейс рисует наше здание красным цветом, сообщая, что здесь его построить нельзя.

При этом юниты представляются точкой на плоскости, здания — прямоугольником, башни — кругом, а стены — отрезком. Кроме того, для каждого игрового объекта в нашем движке заведён отдельный класс, который наследуется от абстрактного класса GameObject:

class Unit;
class Building;
class Tower;
class Fence;

struct GameObject {
  virtual ~GameObject() = default;

  virtual bool Collide(const GameObject& that) const = 0;
  virtual bool CollideWith(const Unit& that) const = 0;
  virtual bool CollideWith(const Building& that) const = 0;
  virtual bool CollideWith(const Tower& that) const = 0;
  virtual bool CollideWith(const Fence& that) const = 0;
};

Наша задача — реализовать функцию bool Collide(const GameObject& first, const GameObject& second), которая проверяет пересекаются ли два игровых объекта, то есть имеют ли они хотя бы одну общую точку.

Вам даны:

	файл game_object.h, содержащий интерфейс GameObject и объявление функции Collide

	файлы geo2d.h/cpp, содержащие библиотеку для работы с геометрическими фигурами на плоскости; библиотека состоит из классов Point, Rectangle, Circle и Segment и набора функций Collide, которые умеют определять пересечение для каждой пары фигур (занимательный факт — все функции реализованы в целых числах, без применения вычислений в типе double)

	файл collide.cpp, содержащий заготовку решения, а также юнит-тест, эмулирующий размещение нового объекта на игровой карте

Пришлите в тестирующую систему файл collide.cpp, который будет:

	подключать game_object.h

	содержать реализации классов Unit, Building, Tower и Fence (все они должны наследоваться от GameObject и реализовывать его интерфейс)

	содержать реализацию функции bool Collide(const GameObject& first, const GameObject& second), которая возвращает true, если объекты first и second имеют на плоскости хотя бы одну общую точку, и false в противном случае.

Замечание
Один из способов реализовать функцию Collide — использовать dynamic_cast. Мы не освещали его в лекциях. Кроме того, этот способ приводит к появлению развесистого кода, подверженного возникновению ошибок. Мы хотим, чтобы в этой задаче вы хорошенько разобрались с понятиями статического и динамического типа, а также поработали с указателем this. Поэтому мы будем компилировать ваши решения с флагом -fno-rtti, который будет приводить к ошибкам компиляции в случае использования dynamic_cast.
*/
