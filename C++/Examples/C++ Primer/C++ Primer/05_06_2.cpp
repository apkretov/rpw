#include <iostream>
using namespace std;
#include "05_06_2.h"

string Sales_item::isbn() const {
	return isbn_;
};

void Sales_item::setIsbn(string isbn__) {
	isbn_ = isbn__;
}

bool Sales_item::operator!=(const Sales_item &item) const {
	return item.isbn() != isbn();
};

int Sales_item::operator+(const Sales_item &item) const {
	return item.count + count;
};

istream &operator>>(istream &in, Sales_item &item) {
	string isbn;
	in >> isbn >> item.count;
	item.setIsbn(isbn);
	return in;
}

ostream &operator<<(ostream &out, const Sales_item &item) { //MINE
	out << item.isbn() << ' ' << item.count;
	return out;
}

#ifdef ON
void Writing_a_Handler() {
	Sales_item item1, item2; //MINE

	while (cin >> item1 >> item2) {
		try {
			if (item1.isbn() != item2.isbn()) // first check that the data are for the same item
				throw runtime_error("Data must refer to same ISBN");

			cout << item1 + item2 << endl; // if we’re still here, the ISBNs are the same
		}
		catch (runtime_error err) {
			cout << err.what() << "\nTry Again? Enter y or n" << endl; // remind the user that the ISBNs must match and prompt for another pair
			char c;
			cin >> c;
			if (!cin || c == 'n')
				break; // break out of the while loop
		}
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Writing_a_Handler();

	return 0;
}
#endif