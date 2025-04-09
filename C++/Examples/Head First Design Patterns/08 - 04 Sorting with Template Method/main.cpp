#include "../../stdafx.h"
#include "Duck.h"
#include "Sort.h"
using std::cout;
using std::vector;

#pragma region Lets sort some Ducks //Let's sort some Ducks
/* Java
public class DuckSortTestDrive {
	public static void main(String[] args) {
		Duck[] ducks = {
			new Duck("Daffy", 8),
			new Duck("Dewey", 2),
			new Duck("Howard", 7),
			new Duck("Louie", 2),
			new Duck("Donald", 10),
			new Duck("Huey", 2)
		};

		System.out.println("Before sorting:");
		display(ducks);

		Arrays.sort(ducks);

		System.out.println("\nAfter sorting:");
		display(ducks);
	}

	public static void display(Duck[] ducks) {
		for (int i = 0; i < ducks.length; i++)
			System.out.println(ducks[i]);
	}
}
*/

void display(const vector<Duck> &ducks) { // Notice that we call Arrays' static method sort, and pass it our Ducks
	for (const auto &duck : ducks)
		cout << duck.toString() << "\n";
}

int main() {
	print_file_line();

	vector<Duck> ducks = { // We need an array of Ducks; these look good
		Duck("Daffy", 8),
		Duck("Dewey", 2),
		Duck("Howard", 7),
		Duck("Louie", 2),
		Duck("Donald", 10),
		Duck("Huey", 2)
	};

	cout << "Before sorting:\n"; // Let's print them to see their names and weights
	display(ducks);

	Sort<Duck>::sort(ducks); // It's sort time!

	cout << "\nAfter sorting:\n"; // Let's print them (again) to see their names and weights
	display(ducks);

	return 0;
}
#pragma endregion //Lets sort some Ducks