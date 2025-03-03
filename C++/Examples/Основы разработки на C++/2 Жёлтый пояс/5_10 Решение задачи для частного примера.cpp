#if 0

#include <iostream>
#include "../../stdafx.h"
using namespace std;

class Node {
public:
	virtual ~Node() = default; //MINE
	virtual int Evaluate() = 0;
};

class Digit : public Node {
public:
	explicit Digit(int d) : d_(d) {}

	int Evaluate() final {
		return d_;
	}
private:
	int d_;
};

class Variable : public Node {
public:
	explicit Variable(const int &x) : x_(x) {}

	int Evaluate() final {
		return x_;
	}
private:
	const int &x_;
};

class Operation : public Node {
public:
	Operation(char op, shared_ptr<Node> left, shared_ptr<Node> right) : op_(op), left_(left), right_(right) {}

	int Evaluate() final {
		if (op_ == '*')
			return left_->Evaluate() * right_->Evaluate();
		else if (op_ == '+')
			return left_->Evaluate() + right_->Evaluate();
		else if (op_ == '-')
			return left_->Evaluate() - right_->Evaluate();
		return 0;
	}
private:
	char op_;
	shared_ptr<Node> left_;
	shared_ptr<Node> right_;
};

#ifdef OFF
Node Parse(const string &tokens, int x) {
	return {};
}
#endif //OFF

int main() {
	string tokens = "5+7-x*x+x";

	int x;
#ifdef OFF
	cout << "Enter expression: ";
	cin >> tokens;
	auto expr = Parse(tokens, x);
#endif //OFF

	shared_ptr<Node> var1 = make_shared<Variable>(x);
	shared_ptr<Node> var2 = make_shared<Variable>(x);
	shared_ptr<Node> mul1 = make_shared<Operation>('*', var1, var2);

	shared_ptr<Node> dig1 = make_shared<Digit>(5);
	shared_ptr<Node> dig2 = make_shared<Digit>(7);

	shared_ptr<Node> var3 = make_shared<Variable>(x);

	shared_ptr<Node> plus1 = make_shared<Operation>('+', dig1, dig2);
	shared_ptr<Node> minus1 = make_shared<Operation>('-', plus1, mul1);
	shared_ptr<Node> plus2 = make_shared<Operation>('+', minus1, var3);

	cout << "Enter x: ";
	while (cin >> x) {
		cout << plus2->Evaluate() << '\n';
		cout << "Enter x: ";
	}
}
#endif //1

#ifdef MINE

#include <iostream>
#include "../../stdafx.h"
using namespace std;

struct invalid_operation : invalid_argument {
	invalid_operation() : invalid_argument("Invalid operation") {}
};

struct node {
	virtual double evaluate() const = 0;
	virtual ~node() = default;
};

using pnode = unique_ptr<node>;

class digit : public node {
public:
	explicit digit(double n) : num(n) {}

	double evaluate() const final {
		return num;
	}
private:
	double num;
};

class operation: public node {
public:
	operation(char op, pnode l, pnode r) : oper(op), lhs(std::move(l)), rhs(std::move(r)) {}

	double evaluate() const final {
		if (oper == '*')
			return lhs->evaluate() * rhs->evaluate();
		else if (oper == '/')
			return lhs->evaluate() / rhs->evaluate();
		else if (oper == '+')
			return lhs->evaluate() + rhs->evaluate();
		else if (oper == '-')
			return lhs->evaluate() - rhs->evaluate();
		else
			throw(invalid_operation());
		return 0;
	}
private:
	char oper;
	pnode lhs;
	pnode rhs;
};

int main() {
	PRINT_FILE_LINE();
	
	try {
		const string expr = "5+7*3";
		pnode num1 = make_unique<digit>(7);
		pnode num2 = make_unique<digit>(3);
	 	pnode mult1 = make_unique<operation>('*', std::move(num1), std::move(num2));
		cout << AS_KV(mult1->evaluate()) << '\n';

		pnode num3 = make_unique<digit>(5);
		pnode add1 = make_unique<operation>('+', std::move(num3), std::move(mult1));
		cout << AS_KV(add1->evaluate()) << '\n';

	}
	catch (const invalid_operation &e) {
		cerr << "Error: " << e.what() << '\n';
	}	
	catch (const exception &e) {
		cerr << "Error: " << e.what() << '\n';
	}
}
#endif //MINE
