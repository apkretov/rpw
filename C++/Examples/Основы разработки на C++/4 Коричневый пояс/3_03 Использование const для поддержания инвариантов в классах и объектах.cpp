#if 0

#include "3_03 ������������� const ��� ����������� ����������� � ������� � ��������.h"
#include "../../stdafx.h"
using namespace std;

int main() {
	PRINT_FILE_LINE();

	const vector<int> sorted_numbers = Sorted({5, 4, 2, 1, 5, 1, 3, 4, 5, 6, 8});

	for (int n : sorted_numbers)
		cout << n << ' ';
	cout << '\n';

	// �����-�� ���...

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		cout << x << ' ';
		bool found = binary_search(sorted_numbers.begin(), sorted_numbers.end(), x); //ORIG cout << binary_search(sorted_numbers.begin(), sorted_numbers.end(), x) << '\n';
		cout << format("found: {}\n", found);
	}

	return 0;
}
#endif