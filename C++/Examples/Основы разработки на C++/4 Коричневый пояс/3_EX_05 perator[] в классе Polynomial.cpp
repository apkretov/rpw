﻿#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week3/05%20Programming%20Assingment

#include "../../stdafx.h"
#include "../test_runner.h" 
using namespace std;

constexpr size_t test_count = 50'000; //MINE

template<typename T>
void PrintCoeff(ostream &out, int i, const T &coef, bool printed) {
	bool coeffPrinted = false;
	if (coef == 1 && i > 0)
		out << (printed ? "+" : "");
	else if (coef == -1 && i > 0)
		out << "-";
	else if (coef >= 0 && printed) {
		out << "+" << coef;
		coeffPrinted = true;
	} else {
		out << coef;
		coeffPrinted = true;
	}
	if (i > 0)
		out << (coeffPrinted ? "*" : "") << "x";
	if (i > 1)
		out << "^" << i;
}

template <typename T>
class Polynomial {
	vector<T> coeffs_ = {0};
	void Shrink();

	/* @ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week3/05%20Programming%20Assingment/source/AtA3c_ZAEeiAgQrXx6bp4g_0387c750f64011e88717b75766913400__________-4.pdf
	Прокси-объект
	Мы можем возвращать из неконстантного operator[] не T& , а объект специального класса -
	- назовём его IndexProxy, -- у которого будет перегруженный operator= . Этот оператор будет
	выполнять запись в поле coeffs_ класса Polynomial<T> , изменяя его размер при
	необходимости.
	P.S. Класс IndexProxy проще сделать внутри класса Polynomial , а не отдельным шаблоном
	класса.
	*/
	class IndexProxy { //TEST!!
		Polynomial &poly_;
		size_t degree_;
	public:
#ifdef MINE
		IndexProxy(Polynomial &poly, size_t degree) : poly_(poly), degree_(degree) {
			if (degree_ >= poly_.coeffs_.size())
				poly_.coeffs_.resize(degree_ + 1);
		}

		~IndexProxy() { poly_.Shrink(); }

		IndexProxy &operator=(const T &value) {
			poly_.coeffs_[degree_] = value; //TEST!! //																										Perplexity: Instead of my poly_[degree_] = value; directly access coeffs_ instead of using [] to prevent the infinite recursion that eventually causes a stack overflow.
			return *this;
		}
#else //GITHUB @ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week3/05%20Programming%20Assingment/solution.cpp
		IndexProxy(Polynomial &poly, size_t degree) : poly_(poly), degree_(degree) {}

		IndexProxy &operator=(T value) { //TEST!!
			auto &coeffs = poly_.coeffs_;
			if (degree_ >= coeffs.size())
				coeffs.resize(degree_ + 1);
			coeffs[degree_] = value; //TEST!! //																											Perplexity: Instead of my poly_[degree_] = value; directly access coeffs_ instead of using [] to prevent the infinite recursion that eventually causes a stack overflow.
			poly_.Shrink();
			return *this;
		}
#endif //GITHUB
		/* @ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week3/05%20Programming%20Assingment/source/As0qMfZAEeiAgQrXx6bp4g_03792150f64011e8842eedff8ee7b80d__________-5.pdf
		Оператор приведения к типу
		После того, как мы сделали внутренний класс IndexProxy , у которого есть operator= ,
		казалось бы, всё должно быть хорошо. Однако ваш код вряд ли будет компилироваться,
		например, при выполнении такого теста:

		Polynomial<int> poly;
		ASSERT_EQUAL(poly[0], 1); // Здесь не компилируется, потому что мы сравниваем IndexProxy и int
		int x = poly[1]; // Тоже не компилируется — мы присваиваем IndexProxy в int

		Нам нужно сделать так, чтобы код выше работал. Для успешной компиляции и работы
		ассерта можно перегрузить operator== для IndexProxy и T ( T -- тип, с которым мы
		инстанцируем шаблон Polynomial ). Кроме того, нам придётся перегрузить operator<< для
		IndexProxy, чтобы он умел выводиться в поток.
		Это будет работать, однако команда int x = poly[1]; все равно не будет компилироваться.
		Универсальным решением здесь будет добавить в класс IndexProxy оператор приведения к
		типу T . Это довольно экзотическая возможность C++, о которой мы не рассказывали в
		лекциях. Поэтому мы просто приведём его реализацию:
		*/
		operator T() const { return as_const(poly_)[degree_]; } //TEST!! //																					Вызываем константную версию Polynomial::operator[]
	};
public:
	Polynomial() = default;
	Polynomial(vector<T> coeffs) : coeffs_(std::move(coeffs)) { Shrink(); }
	template<typename Iterator>	Polynomial(Iterator first, Iterator last) : coeffs_(first, last) { Shrink(); }
	bool operator==(const Polynomial &other) const { return coeffs_ == other.coeffs_; }
	bool operator!=(const Polynomial &other) const { return !operator==(other); }
	int Degree() const { return coeffs_.size() - 1; }
	Polynomial &operator+=(const Polynomial &r);
	Polynomial &operator-=(const Polynomial &r);
	T operator[](size_t degree) const { return degree < coeffs_.size() ? coeffs_[degree] : 0; }

	/* @ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week3/05%20Programming%20Assingment/source/AtA3c_ZAEeiAgQrXx6bp4g_0387c750f64011e88717b75766913400__________-4.pdf
	Прокси-объект
	Мы можем возвращать из неконстантного operator[] не T& , а объект специального класса -
	- назовём его IndexProxy, -- у которого будет перегруженный operator= . Этот оператор будет
	выполнять запись в поле coeffs_ класса Polynomial<T> , изменяя его размер при
	необходимости.
	P.S. Класс IndexProxy проще сделать внутри класса Polynomial , а не отдельным шаблоном
	класса.
	*/
	IndexProxy operator[](size_t degree) { return {*this, degree}; } //TEST!!
	T operator()(const T &x) const;
	using const_iterator = typename vector<T>::const_iterator;
	const_iterator begin() const { return coeffs_.cbegin(); }
	const_iterator end() const { return coeffs_.cend(); }

};

template <typename T>
void Polynomial<T>::Shrink() {
	while (coeffs_.size() > 1 && coeffs_.back() == 0)
		coeffs_.pop_back();
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator+=(const Polynomial &r) {
	if (r.coeffs_.size() > coeffs_.size())
		coeffs_.resize(r.coeffs_.size());
	for (size_t i = 0; i != r.coeffs_.size(); ++i)
		coeffs_[i] += r.coeffs_[i];
	Shrink();
	return *this;
}

template<typename T>
Polynomial<T> &Polynomial<T>::operator-=(const Polynomial &r) {
	if (r.coeffs_.size() > coeffs_.size())
		coeffs_.resize(r.coeffs_.size());
	for (size_t i = 0; i != r.coeffs_.size(); ++i)
		coeffs_[i] -= r.coeffs_[i];
	Shrink();
	return *this;
}

template<typename T>
T Polynomial<T>::operator()(const T &x) const {
	T res = 0;
	for (auto it = coeffs_.rbegin(); it != coeffs_.rend(); ++it) {
		res *= x;
		res += *it;
	}
	return res;
}

template <typename T>
ostream &operator<<(ostream &out, const Polynomial<T> &p) {
	bool printed = false;
	for (int i = p.Degree(); i >= 0; --i) {
		if (p[i] != 0) {
			PrintCoeff(out, i, p[i], printed);
			printed = true;
		}
	}
	return out;
}

template <typename T>
Polynomial<T> operator+(Polynomial<T> lhs, const Polynomial<T> &rhs) {
	lhs += rhs;
	return lhs;
}

template <typename T>
Polynomial<T> operator-(Polynomial<T> lhs, const Polynomial<T> &rhs) {
	lhs -= rhs;
	return lhs;
}

void TestCreation() {
	{
		Polynomial<int> default_constructed;
		ASSERT_EQUAL(default_constructed.Degree(), 0);
		ASSERT_EQUAL(default_constructed[0], 0);
	}
	{
		Polynomial<double> from_vector({1.0, 2.0, 3.0, 4.0});
		ASSERT_EQUAL(from_vector.Degree(), 3);
		ASSERT_EQUAL(from_vector[0], 1.0);
		ASSERT_EQUAL(from_vector[1], 2.0);
		ASSERT_EQUAL(from_vector[2], 3.0);
		ASSERT_EQUAL(from_vector[3], 4.0);
	}
	{
		const vector<int> coeffs = {4, 9, 7, 8, 12};
		Polynomial<int> from_iterators(begin(coeffs), end(coeffs));
		ASSERT_EQUAL(from_iterators.Degree(), coeffs.size() - 1);
		ASSERT(equal(cbegin(from_iterators), cend(from_iterators), begin(coeffs)));
	}
}

void TestEqualComparability() {
	Polynomial<int> p1({9, 3, 2, 8});
	Polynomial<int> p2({9, 3, 2, 8});
	Polynomial<int> p3({1, 2, 4, 8});

	ASSERT_EQUAL(p1, p2);
	ASSERT(p1 != p3);
}

void TestAddition() {
	Polynomial<int> p1({9, 3, 2, 8});
	Polynomial<int> p2({1, 2, 4});

	p1 += p2;
	ASSERT_EQUAL(p1, Polynomial<int>({10, 5, 6, 8}));

	auto p3 = p1 + p2;
	ASSERT_EQUAL(p3, Polynomial<int>({11, 7, 10, 8}));

	p3 += Polynomial<int>({-11, 1, -10, -8});
	ASSERT_EQUAL(p3.Degree(), 1);
	const Polynomial<int> expected{{0, 8}};
	ASSERT_EQUAL(p3, expected);
}

void TestSubtraction() {
	Polynomial<int> p1({9, 3, 2, 8});
	Polynomial<int> p2({1, 2, 4});

	p1 -= p2;
	ASSERT_EQUAL(p1, Polynomial<int>({8, 1, -2, 8}));

	auto p3 = p1 - p2;
	ASSERT_EQUAL(p3, Polynomial<int>({7, -1, -6, 8}));

	p3 -= Polynomial<int>({7, -5, -6, 8});
	ASSERT_EQUAL(p3.Degree(), 1);
	const Polynomial<int> expected{{0, 4}};
	ASSERT_EQUAL(p3, expected);
}

void TestEvaluation() {
	const Polynomial<int> default_constructed;
	ASSERT_EQUAL(default_constructed(0), 0);
	ASSERT_EQUAL(default_constructed(1), 0);
	ASSERT_EQUAL(default_constructed(-1), 0);
	ASSERT_EQUAL(default_constructed(198632), 0);

	const Polynomial<int64_t> cubic({1, 1, 1, 1});
	ASSERT_EQUAL(cubic(0), 1);
	ASSERT_EQUAL(cubic(1), 4);
	ASSERT_EQUAL(cubic(2), 15);
	ASSERT_EQUAL(cubic(21), 9724);
}

void TestConstAccess() {
	const Polynomial<int> poly(initializer_list<int> {1, 2, 3, 4, 5});

	ASSERT_EQUAL(poly[0], 1);
	ASSERT_EQUAL(poly[1], 2);
	ASSERT_EQUAL(poly[2], 3);
	ASSERT_EQUAL(poly[3], 4);
	ASSERT_EQUAL(poly[4], 5);
	ASSERT_EQUAL(poly[5], 0);
	ASSERT_EQUAL(poly[6], 0);
	ASSERT_EQUAL(poly[608], 0);
}

void TestMine() {
	Polynomial<int> p;
	p[2] = 1;
	ASSERT_EQUAL(p.Degree(), 2);
	int x = p[5];
	ASSERT_EQUAL(x, 0);
	ASSERT_EQUAL(p.Degree(), 2); // Мы ничего не записали в p[5], поэтому степень многочлена не изменилась
	//int x = static_cast<int>(p[5]);
}

void TestNonconstAccess() {
	Polynomial<int> poly;

	poly[0] = 1;
	poly[3] = 12;
	poly[5] = 4;
	ASSERT_EQUAL(poly.Degree(), 5);

	ASSERT_EQUAL(poly[0], 1);
	ASSERT_EQUAL(poly[1], 0);
	ASSERT_EQUAL(poly[2], 0);
	ASSERT_EQUAL(poly[3], 12);
	ASSERT_EQUAL(poly[4], 0);
	ASSERT_EQUAL(poly[5], 4);
	ASSERT_EQUAL(poly[6], 0);
	ASSERT_EQUAL(poly[608], 0);

	ASSERT_EQUAL(poly.Degree(), 5);
	poly[608] = 0;
	ASSERT_EQUAL(poly.Degree(), 5);

	{
		LOG_DURATION("Iteration over const");
		for (size_t i = 10; i < test_count; ++i) { //ORIG for (size_t i = 10; i < 50000; ++i) {
			ASSERT_EQUAL(as_const(poly)[i], 0);
			ASSERT_EQUAL(poly.Degree(), 5);
		}
	}
	{
		LOG_DURATION("Iteration over non-const");
		for (size_t i = 10; i < test_count; ++i) { //ORIG for (size_t i = 10; i < 50000; ++i) {
			ASSERT_EQUAL(poly[i], 0);
			ASSERT_EQUAL(poly.Degree(), 5);
		}
	}
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestCreation);
	RUN_TEST(tr, TestEqualComparability);
	RUN_TEST(tr, TestAddition);
	RUN_TEST(tr, TestSubtraction);
	RUN_TEST(tr, TestEvaluation);
	RUN_TEST(tr, TestConstAccess);
	RUN_TEST(tr, TestMine);
	RUN_TEST(tr, TestNonconstAccess);

	return 0;
}
#endif //1

/*
operator[] в классе Polynomial

В лекциях мы наглядно продемонстрировали, что константность ограничивает набор операций, которые можно выполнять с объектом, защищая его от нежелательного изменения. Однако возможности константности ограничены, и в некоторых случаях она не позволяет достичь желаемого эффекта. В таких ситуациях на помощь приходит система типов, которая позволяет создавать классы с требуемыми свойствами. Мы рассмотрим такую ситуацию в этой задаче.

Вам дана реализация шаблона Polynomial, который представляет собой многочлен от одной переменной. Тип T этого шаблона задаёт тип коэффициентов и переменной. То есть Polynomial -- это многочлен с целочисленными коэффициентами от целочисленной переменной, Polynomial -- это многочлен с вещественными коэффициентами от вещественной переменной. Рассмотрим интерфейс класса Polynomial:

template<typename T>
class Polynomial {
private:
  ...
public:
  // Принимает вектор коэффициентов (коэффициенты задаются от младшего к старшим)
  // Например, Polynomial({10, 2, 3, 4}) создаёт многочлен 4*x^3 + 3*x^2 + 2*x + 10
  Polynomial(vector<T> coeffs);

  // Создаёт многочлен, все коэффициенты которого равны нулю
  Polynomial();

  // Аналогичен конструктору от вектора, но принимает пару итераторов
  template<typename Iterator>
  Polynomial(Iterator first, Iterator last);

  // Операторы проверки на равенство и неравенство. Два многочлена равны тогда и только тогда,
  // когда их соответствующие коэффициенты попарно равны
  bool operator ==(const Polynomial& other) const;
  bool operator !=(const Polynomial& other) const;

  // Возвращает степень многочлена -- максимальную степень, коэффициент при которой не равен нулю.
  // Например, степень многочлена 2*x равна 1, степень многочлена 4*x^5 + x^3 - 10 равна 5,
  // степень многочлена 5 равна нулю.
  // Метод работает за O(1)
  int Degree() const;

  Polynomial& operator +=(const Polynomial& r);
  Polynomial& operator -=(const Polynomial& r);

  // Возвращает значение коэффициента при заданной степени.
  // Если переданное значение больше степени многочлена, метод возвращает 0
  T operator [](size_t degree) const;
  // Вычисляет значение многочлена в точке с переданным значением
  T operator ()(const T& x) const;

  using const_iterator = typename std::vector<T>::const_iterator;

  // Итераторы на коэффициенты многочлена
  const_iterator begin() const;
  const_iterator end() const;
};

В приведённой выше реализации есть только одна возможность задать значения коэффициентов многочлена — передать их в конструктор. Однако на практике может оказаться полезной возможность задавать коэффициенты по одному (эта возможность особенно полезна для сильно разреженных полиномов):

Polynomial<int> p;
p[1] = 5;
p[24] = -8;
p[61] = 12;
p[314] = 272;

Ваша задача -- добавить эту возможность, а именно реализовать неконстантный operator[] для шаблона Polynomial, который

	будет позволять задавать значение коэффициента заданной степени (как в примере выше)

	будет позволять читать значение коэффициента заданной степени (то есть должен работать код int cv = p[4];)

	будет работать за O(1) в случае, если не меняется степень многочлена

	не будет менять степень многочлена, если запись не была произведена

Последнее требование можно выразить вот таким тестом:

Polynomial<int> p;
p[2] = 1;
ASSERT_EQUAL(p.Degree(), 2);
int x = p[5];
ASSERT_EQUAL(x, 0);
ASSERT_EQUAL(p.Degree(), 2); // Мы ничего не записали в p[5], поэтому степень многочлена не изменилась

См. также юнит-тесты в заготовке решения

На проверку пришлите cpp-файл с полной реализацией шаблона Polynomial.
*/