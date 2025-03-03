#undef ON
#ifdef ON

#include <iostream>
using std::cout;

class Team {
public:
	int score;
	class Player {
		int score;
	public:
		void GoGoGo() { cout << "Player is going to a goal.\n"; }
		void SetScore(int x) { score = x; }
		void ShowScore() { cout << score << '\n'; }
	};
};

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru-RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
		
	Team::Player p;
	p.GoGoGo();

	return 0;
}

#endif