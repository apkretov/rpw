#include "../../stdafx.h"
#include "AdapterTurkey.h"
#include "DuckMallard.h"
#include "TurkeyWild.h"
using std::cout;

#pragma region Test drive the adapter
/* Java
public class DuckTestDrive {
	public static void main(String[] args) {
		MallardDuck duck = new MallardDuck(); // Let's create a Duck...

		WildTurkey turkey = new WildTurkey(); // and a Turkey.
		Duck turkeyAdapter = new TurkeyAdapter(turkey); // And then wrap the turkey in a TurkeyAdapter, which makes it look like a Duck.

		System.out.println("The Turkey says..."); // Then, let's test the Turkey: make it gobble, make it fly.
		turkey.gobble();
		turkey.fly();

		System.out.println("\nThe Duck says..."); // Now let's test the duck by calling the testDuck() method, which expects a Duck object.
		testDuck(duck);

		System.out.println("\nThe TurkeyAdapter says...");
		testDuck(turkeyAdapter); // Now the big test: we try to pass off the turkey as a duck...
	}

	static void testDuck(Duck duck) { // Here's our testDuck() method; it gets a duck and calls its quack() and fly() methods.
		duck.quack();
		duck.fly();
	}
}
*/
void testDuck(Duck &duck) { // Here's our testDuck() method; it gets a duck and calls its quack() and fly() methods.
    duck.quack();
    duck.fly();
}

int main() {
	print_file_line();

	MallardDuck duck; // Let's create a Duck...
	WildTurkey turkey; // and a Turkey.
	TurkeyAdapter turkeyAdapter{turkey}; // And then wrap the turkey in a TurkeyAdapter, which makes it look like a Duck.

    cout << "The Turkey says...\n"; // Then, let's test the Turkey: make it gobble, make it fly.
    turkey.gobble();
    turkey.fly();

    cout << "\nThe Duck says...\n"; // Now let's test the duck by calling the testDuck() method, which expects a Duck object.
    testDuck(duck);

    cout << "\nThe TurkeyAdapter says...\n";
    testDuck(turkeyAdapter); // Now the big test: we try to pass off the turkey as a duck...

    return 0;
}
#pragma endregion //Test drive the adapter
