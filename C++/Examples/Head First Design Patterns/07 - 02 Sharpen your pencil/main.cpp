#include "../../stdafx.h"
#include "DuckMallard.h"
#include "TurkeyWild.h"
#include "AdapterDuck.h"
#include "AdapterTurkey.h"
using std::cout;
using std::make_shared;
using std::shared_ptr;

#pragma region Sharpen your pencil
//void testDuck(shared_ptr<Duck> duck) {
//	duck->quack();
//	duck->fly();
//}

int main() {
	print_file_line();

	//shared_ptr<MallardDuck> duck = make_shared<MallardDuck>();

	//shared_ptr<WildTurkey> turkey = make_shared<WildTurkey>();
	//shared_ptr<Duck> turkeyAdapter = make_shared<TurkeyAdapter>(turkey);

	//cout << "The Turkey says...\n";
	//turkey->gobble();
	//turkey->fly();

	//cout << "\nThe Duck says...\n";
	//testDuck(duck);

	//cout << "\nThe TurkeyAdapter says...\n";
	//testDuck(turkeyAdapter);

	return 0;
}
#pragma endregion //Sharpen your pencil
