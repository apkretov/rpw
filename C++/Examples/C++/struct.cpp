#include "stdafx.h" // C++ Data Structures @ https://www.tutorialspoint.com/cplusplus/cpp_data_structures.htm
#include <iostream>
#include <cstring>
using namespace std;
#pragma warning(disable: 4996)

struct Books {
	char  title[50];
	char  author[50];
	char  subject[100];
	int   book_id;
};

void defineAccess() { //Defining a Structure. Accessing Structure Members.
	struct Books Book1;        // Declare Book1 of type Book
	struct Books Book2;        // Declare Book2 of type Book
	strcpy(Book1.title, "Learn C++ Programming"); // book 1 specification
	strcpy(Book1.author, "Chand Miyan");
	strcpy(Book1.subject, "C++ Programming");
	Book1.book_id = 6495407;
	strcpy(Book2.title, "Telecom Billing"); // book 2 specification
	strcpy(Book2.author, "Yakit Singha");
	strcpy(Book2.subject, "Telecom");
	Book2.book_id = 6495700;
	cout << "Book 1 title : " << Book1.title << endl; // Print Book1 info
	cout << "Book 1 author : " << Book1.author << endl;
	cout << "Book 1 subject : " << Book1.subject << endl;
	cout << "Book 1 id : " << Book1.book_id << endl;
	cout << "Book 2 title : " << Book2.title << endl; // Print Book2 info
	cout << "Book 2 author : " << Book2.author << endl;
	cout << "Book 2 subject : " << Book2.subject << endl;
	cout << "Book 2 id : " << Book2.book_id << endl << endl;
}

typedef struct { //The typedef Keyword.
	char  title[50];
	char  author[50];
	char  subject[100];
	int   book_id;
} Books_t;

constexpr int mintLength = 3;
struct test { //Uninitialised.
	int i;
	double d;
}; 

void arrayUninitialised() { //An uninitialised array of struct.
	test sttTest[mintLength];
	cout << "sttTest[0].i = " << sttTest[0].i << endl << endl;
}

void arrayUninitialisedNew() { //An uninitialised array of struct created with new
	test* sttTest = new test[mintLength];
	cout << "sttTest[0].i = " << sttTest[0].i << endl << endl;
	delete sttTest;
}

void initialised() {
	struct test { 
		int i = 0;
		double d = 0;
	};
	test sttTest;
	cout << "sttTest.i = " << sttTest.i << endl << endl;
}

void initialisedInitialisationList() {
	struct test {int i;};
}

int main() {
	defineAccess();
	struct Books* struct_pointer; //Pointers to Structures.
	Books_t Book1, Book2; //The typedef Keyword.
	Books_t* struct_pointer_ = &Book1; //Pointers to Structures.
   arrayUninitialised();
	arrayUninitialisedNew();
	initialised();
	return 0;
}
