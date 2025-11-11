#if 0

#include <future>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

struct Account { //VER1
	int balance = 0;

	bool Spend(int value) {
		if (value <= balance) {
			balance -= value;
			return true;
		}
		return false;
	}
};

int SpendMoney(Account &account) {
	int total_spent = 0;
	for (int i = 0; i < 100'000; ++i)
		if (account.Spend(1))
			++total_spent;
	return total_spent;
}

void func1() {
	Account my_account{100'000}; //TEST! //																													MINE: No constructor argument: balance = {100'000}.
	cout << "Total spent: " << SpendMoney(my_account) << endl 
		<< "Balance: " << my_account.balance << endl;
}

void func2() {
	Account family_account{100'000};
	auto husband  = async(SpendMoney, ref(family_account));
	auto wife	  = async(SpendMoney, ref(family_account));
	auto son	  = async(SpendMoney, ref(family_account));
	auto daughter = async(SpendMoney, ref(family_account));

	int spent = husband.get() + wife.get() + son.get() + daughter.get();
	cout << "Total spent: " << spent << endl //TEST //																										MINE: Total spent: 306464		Balance : 0
		<< "Balance: " << family_account.balance << endl;

}

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	//func1();
	func2();

	return 0;
}
#endif //1