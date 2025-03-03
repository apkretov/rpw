#ifdef ON

#include <iostream>
using namespace std;

void Order_of_Evaluation() {
	int i = 0;
	//TEST! cout << i << " " << ++i << endl; //																																										undefined
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Order_of_Evaluation();

	return 0;
}
#endif