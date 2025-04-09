#include <memory>
#include "../../stdafx.h"
#include "Coffee.h"
#include "Tea.h"
using std::cout;
using std::make_unique;
using std::unique_ptr;

int main() {
	print_file_line();

#pragma region Lets make some tea... //Let's make some tea...
	/* Java
	Tea myTea = new Tea();
	myTea.prepareRecipe();
	*/
	Tea tea;
	tea.prepareRecipe();
#pragma endregion //Lets make some tea...

	return 0;
}
