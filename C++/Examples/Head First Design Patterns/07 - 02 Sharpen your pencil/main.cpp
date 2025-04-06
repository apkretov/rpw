#include "../../stdafx.h"
#include "AdapterDuck.h"
#include "DuckMallard.h"
#include "TurkeyWild.h"
using std::cout;

#pragma region Sharpen your pencil
void testTurkey(Turkey &turkey) {                
	turkey.gobble();
	turkey.fly();
}

int main() {
	print_file_line();

	MallardDuck duck;     
	WildTurkey turkey;    
	DuckAdapter duckAdapter{duck};                

	cout << "The Duck says...\n";            
	duck.quack();
	duck.fly();

	cout << "\nThe Turkey says...\n";                
	testTurkey(turkey);

	cout << "\nThe DuckAdapter says...\n";
	testTurkey(duckAdapter);               

	return 0;
}
#pragma endregion //Sharpen your pencil
