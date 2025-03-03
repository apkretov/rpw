#ifdef EX_13_22

#include <iostream>
using namespace std;

class HasPtr {
	friend ostream &operator<<(ostream &, const HasPtr &);
public:
	HasPtr(const string & = string());
	HasPtr(const HasPtr &);
	HasPtr &operator=(const HasPtr &);
	~HasPtr();
	void setStr(const string &);
private:
	string *ps;
	int i;
};

HasPtr::HasPtr(const string &s) : ps(new string(s)), i(0) {}

#ifdef ORIG
HasPtr::HasPtr(const HasPtr &hp) {
	ps = new string(*hp.ps);
	i = hp.i;
}
#elif! MINE
HasPtr::HasPtr(const HasPtr &hp) : ps(new string(*hp.ps)), i(hp.i) {} //MINE
#endif

HasPtr &HasPtr::operator=(const HasPtr &hp) {
	auto newPs = new string(*hp.ps);
	i = hp.i;
	delete ps;
	ps = newPs;
	return *this;
}

HasPtr::~HasPtr() {
	delete ps;
}

void HasPtr::setStr(const string &s) {
	*ps = s;
}

ostream &operator<<(ostream &out, const HasPtr &hp) {
	out << *hp.ps << '\t' << hp.i;
	return out;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	HasPtr hp1, hp2("hp2"), hp3;
	hp3 = hp2;
	cout << hp1 << '\n' << hp2 << '\n' << hp3 << '\n';

	hp3.setStr("hp3");
	cout << '\n' << hp1 << '\n' << hp2 << '\n' << hp3 << '\n';

	hp2 = hp2;
	cout << '\n' << hp1 << '\n' << hp2 << '\n' << hp3 << '\n';

	return 0;
}
#endif
