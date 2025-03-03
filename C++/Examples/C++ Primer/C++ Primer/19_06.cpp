#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

void Defining_a_union() {
union Token { // objects of type Token have a single member, which could be of any of the listed types
	char cval; // members are public by default
	int ival;
	double dval;
};

#pragma region Using a union Type
	Token first_token = {'a'}; // initializes the cval member
	Token second_token = {2.2}; //MINE
	Token last_token; // uninitialized Token object
	Token *pt = new Token; // pointer to an uninitialized Token object

	last_token.cval = 'z';
	pt->ival = 42;
#pragma endregion
}

void Anonymous_unions() {
	union { // anonymous union
		char cval;
		int ival;
		double dval;
	}; // defines an unnamed object, whose members we can access directly
	cval = 'c'; //TEST! //																																assigns a new value to the unnamed, anonymous union object
	ival = 42; //TEST //																																that object now holds the value 42
}

#pragma region Using a Class to Manage union Members
class Token {
public:
	Token() : tok(INT), ival{0} {} // copy control needed because our class has a union with a string member // defining the move constructor and move-assignment operator is left as an exercise
	
	Token(const Token &t) : tok(t.tok) { 
		copyUnion(t); 
	}
	
	Token &operator=(const Token &);

	~Token() { // if the union holds a string, we must destroy it; see § 19.1.2 (p. 824)
		if (tok == STR) 
			sval.~string(); //TEST!
	}

	Token &operator=(const string &); // assignment operators to set the differing members of the union
	Token &operator=(char);
	Token &operator=(int);
	Token &operator=(double);
private:
	enum { INT, CHAR, DBL, STR } tok; //TEST! //																										discriminant

	union { // anonymous union
		char cval;
		int ival;
		double dval;
		string sval;
	}; // each Token object has an unnamed member of this unnamed union type
	
	void copyUnion(const Token &); // check the discriminant and copy the union member as appropriate
};
#pragma endregion

#pragma region Managing the Discriminant and Destroying the string
Token &Token::operator=(int i) {
	if (tok == STR) // if we have a string, free it
		sval.~string(); 
	ival = i; // assign to the appropriate member
	tok = INT; // update the discriminant
	return *this;
}

Token &Token::operator=(const string &s) {
	if (tok == STR) // if we already hold a string, just do an assignment
		sval = s;
	else
		new(&sval) string(s); //TEST! //																												otherwise construct a string
	tok = STR; // update the discriminant
	return *this;
}
#pragma endregion

#pragma region Managing Union Members That Require Copy Control
void Token::copyUnion(const Token &t) {
	switch (t.tok) {
		case Token::INT: ival = t.ival; break;
		case Token::CHAR: cval = t.cval; break;
		case Token::DBL: dval = t.dval; break;
		case Token::STR: new(&sval) string(t.sval); break; // to copy a string, construct it using placement new; see (§ 19.1.2 (p. 824))
	}
}

Token &Token::operator=(const Token &t) {
	if (tok == STR && t.tok != STR) // if this object holds a string and t doesn’t, we have to free the old string
		sval.~string();
	if (tok == STR && t.tok == STR)
		sval = t.sval; // no need to construct a new string
	else
		copyUnion(t); // will construct a string if t.tok is STR
	tok = t.tok;
	return *this;
}
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif