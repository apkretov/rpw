#ifdef EX_16_11

#include <iostream>
#include <string>
#include "../../stdafx.h"
using namespace std;

//template <typename elemType> class ListItem;
template <typename> class ListItem;

template <typename elemType> class List {
public:
	//List<elemType>();
	List() = default;
	//List<elemType>(const List<elemType> &);
	List(const List &) = default;
	//List<elemType> &operator=(const List<elemType> &);
	List &operator=(const List &) { return *this; }
	//~List();
	~List() = default;
	//void insert(ListItem *ptr, elemType value);
	void insert(ListItem<elemType> *ptr, elemType value) {}
private:
	//ListItem *front, *end;
	ListItem<elemType> *front, *end;
};

int main(int argc, char *argv[]) {
	print_file_line();

	List<string> l;

	return 0;
}
#endif