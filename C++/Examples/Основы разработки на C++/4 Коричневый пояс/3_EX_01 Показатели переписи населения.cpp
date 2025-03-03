#if 0 // I suspended solving the task to compare the solution I had designed (see the TO DO's) with github's one. But it turned out incorrect... So, I did not have much new to learn. @ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week3/01%20Practice%20Assignment

#include <numeric>
#include <sstream>
#include "../3 Красный пояс/1_10 Автоматический вывод типа возвращаемого функцией.h" //MINE
#include "../../stdafx.h"
using namespace std;

struct Person {
	string name;
	int age;
	int income;
	bool is_male;
};

vector<Person> ReadPeople(istream &input) {
	int count;
	input >> count;
	vector<Person> result(count); //TO DO: Substitute this with reserve(count).
	for (Person &p : result) {
		char gender;
		input >> p.name >> p.age >> p.income >> gender;
		p.is_male = gender == 'M';
	}
	return result;
}

int main() {
#ifdef ORIG
	vector<Person> people = ReadPeople(cin);  
#else //MINE
	istringstream in_people{
		"11"
		"Ivan 25 1000 M"
		"Olga 30 623 W"
		"Sergey 24 825 M"
		"Maria 42 1254 W"
		"Mikhail 15 215 M"
		"Oleg 18 230 M"
		"Denis 53 8965 M"
		"Maxim 37 9050 M"
		"Ivan 47 19050 M"
		"Ivan 17 50 M"
		"Olga 23 550 W"
	};
	vector<Person> people = ReadPeople(in_people);
#endif //MINE
	sort(begin(people), end(people), [](const Person &lhs, const Person &rhs) {	return lhs.age < rhs.age; });

#ifdef ORIG
	for (string command; cin >> command; ) { //TO DO: Add caches for all of the commands with the same parameters.  
#else //MINE
	istringstream in_comands{
		"AGE 18"
		"WEALTHY 5"
		"POPULAR_NAME M"
		//MINE "POPULAR_NAME W"
	};
	for (string command; in_comands >> command; ) { //TO DO: Add caches for all of the commands with the same parameters.
#endif //MINE
		if (command == "AGE") { //TO DO: Split this into the commands.
			int adult_age;
			in_comands >> adult_age; //ORIG cin >> adult_age;
			auto adult_begin = lower_bound(begin(people), end(people), adult_age, [](const Person &lhs, int age) { return lhs.age < age; });
			cout << "There are " << distance(adult_begin, end(people)) << " adult people for maturity age " << adult_age << '\n'; //TO DO: Think about a separate result class with an output stream.
		} else if (command == "WEALTHY") { //TO DO: 1) A cache with results. 2) A copy vector with the queried partitions. 3) A mix of the two.
			int count;
			in_comands >> count; //ORIG cin >> count;
			auto head = Head(people, count); //TEST!
			partial_sort(head.begin(), head.end(), end(people), [](const Person &lhs, const Person &rhs) { return lhs.income > rhs.income; });
			int total_income = accumulate(head.begin(), head.end(), 0, [](int cur, Person &p) { return p.income += cur; });
			cout << "Top-" << count << " people have total income " << total_income << '\n';
		}
#ifndef OFF
		else if (command == "POPULAR_NAME") {
			char gender;
			in_comands >> gender; //ORIG cin >> gender;
			IteratorRange range{begin(people), partition(begin(people), end(people), [gender](Person &p) { return p.is_male = (gender == 'M'); })};
			if (range.begin() == range.end()) {
				cout << "No people of gender " << gender << '\n';
			} else {
				sort(range.begin(), range.end(), [](const Person &lhs, const Person &rhs) { return lhs.name < rhs.name; });
				const string *most_popular_name = &range.begin()->name;
				int count = 1;
				for (auto i = range.begin(); i != range.end(); ) {
					auto same_name_end = find_if_not(i, range.end(), [i](const Person &p) { return p.name == i->name; });
					auto cur_name_count = distance(i, same_name_end);
					if (cur_name_count > count) {
						count = cur_name_count;
						most_popular_name = &i->name;
					}
					i = same_name_end;
				}
				cout << "Most popular name among people of gender " << gender << " is " << *most_popular_name << '\n';
			}
		} //TO DO: Perhaps else is needed.  
#endif //OFF
	}
}
#endif

#ifdef GITHUB // The solution does not correctly computes the top-5 wealth (39319), which is 116278. @ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week3/01%20Practice%20Assignment/solution.cpp

#include <numeric>
#include <optional>
#include <sstream>
#include "../3 Красный пояс/1_10 Автоматический вывод типа возвращаемого функцией.h" //MINE
#include "../../stdafx.h"
using namespace std;

struct Person {
	string name;
	int age, income;
	bool is_male;
};

vector<Person> ReadPeople(istream &input) {
	int count;
	input >> count;

	vector<Person> result(count);
	for (Person &p : result) {
		char gender;
		input >> p.name >> p.age >> p.income >> gender;
		p.is_male = gender == 'M';
	}

	return result;
}

template <typename Iter>
optional<string> FindMostPopularName(IteratorRange<Iter> range) {
	if (range.begin() == range.end()) {
		return nullopt;
	} else {
		sort(range.begin(), range.end(), [](const Person &lhs, const Person &rhs) {
			return lhs.name < rhs.name;
			});
		const string *most_popular_name = &range.begin()->name;
		int count = 1;
		for (auto i = range.begin(); i != range.end(); ) {
			auto same_name_end = find_if_not(i, range.end(), [i](const Person &p) {
				return p.name == i->name;
				});
			const auto cur_name_count = distance(i, same_name_end);
			if (
				cur_name_count > count ||
				(cur_name_count == count && i->name < *most_popular_name)
				) {
				count = cur_name_count;
				most_popular_name = &i->name;
			}
			i = same_name_end;
		}
		return *most_popular_name;
	}
}

struct StatsData {
	optional<string> most_popular_male_name;
	optional<string> most_popular_female_name;
	vector<int> cumulative_wealth;
	vector<Person> sorted_by_age;
};

StatsData BuildStatsData(vector<Person> people) {
	StatsData result;

	{
		IteratorRange males{
		  begin(people),
		  partition(begin(people), end(people), [](const Person &p) {
			return p.is_male;
		  })
		};
		IteratorRange females{males.end(), end(people)};

		// По мере обработки запросов список людей не меняется, так что мы можем
		// один раз найти самые популярные женское и мужское имена
		result.most_popular_male_name = FindMostPopularName(males);
		result.most_popular_female_name = FindMostPopularName(females);
	}

	// Запросы WEALTHY можно тоже обрабатывать за О(1), один раз отсортировав всех
	// людей по достатку и посчитав массив префиксных сумм
	{
		sort(people.begin(), people.end(), [](const Person &lhs, const Person &rhs) {
			return lhs.income > rhs.income;
			});

		auto &wealth = result.cumulative_wealth;
		wealth.resize(people.size());
		if (!people.empty()) {
			wealth[0] = people[0].income;
			for (size_t i = 1; i < people.size(); ++i) {
				wealth[i] = wealth[i - 1] + people[i].income;
			}
		}
	}

	sort(begin(people), end(people), [](const Person &lhs, const Person &rhs) {
		return lhs.age < rhs.age;
		});
	result.sorted_by_age = std::move(people);

	return result;
}

int main() {
	PRINT_FILE_LINE();

	// Основной проблемой исходного решения было то, что в нём случайно изменялись
	// входные данные. Чтобы гарантировать, что этого не произойдёт, мы организовываем код
	// так, чтобы в месте обработки запросов были видны только константные данные.
	//
	// Для этого всю их предобработку мы вынесли в отдельную функцию, результат которой
	// сохраняем в константной переменной.
#ifdef ORIG
	const StatsData stats = BuildStatsData(ReadPeople(cin));
	for (string command; cin >> command; ) {
#else //MINE
	istringstream in_people{
		"11"
		"Ivan 25 1000 M"
		"Olga 30 623 W"
		"Sergey 24 825 M"
		"Maria 42 1254 W"
		"Mikhail 15 215 M"
		"Oleg 18 230 M"
		"Denis 53 8965 M"
		"Maxim 37 9050 M"
		"Ivan 47 19050 M"
		"Ivan 17 50 M"
		"Olga 23 550 W"
	};
	const StatsData stats = BuildStatsData(ReadPeople(in_people));

	istringstream in_comands{
	"AGE 18"
	"WEALTHY 5"
	"POPULAR_NAME M"
	//MINE "POPULAR_NAME W"
	};
	for (string command; in_comands >> command; ) { 
#endif //ORIG
		if (command == "AGE") {
			int adult_age;
			in_comands >> adult_age; //ORIG cin >> adult_age;

			auto adult_begin = lower_bound(
				begin(stats.sorted_by_age),
				end(stats.sorted_by_age),
				adult_age,
				[](const Person &lhs, int age) {
					return lhs.age < age;
				}
			);

			cout << "There are " << distance(adult_begin, end(stats.sorted_by_age))
				<< " adult people for maturity age " << adult_age << '\n';
		} else if (command == "WEALTHY") {
			int count;
			in_comands >> count; //ORIG cin >> count;
			cout << "Top-" << count << " people have total income "
				<< stats.cumulative_wealth[count - 1] << '\n';
		} else if (command == "POPULAR_NAME") {
			char gender;
			in_comands >> gender; //ORIG cin >> gender;
			const auto &most_popular_name = gender == 'M' ? stats.most_popular_male_name
				: stats.most_popular_female_name;
			if (most_popular_name) {
				cout << "Most popular name among people of gender " << gender << " is "
					<< *most_popular_name << '\n';
			} else {
				cout << "No people of gender " << gender << '\n';
			}
		}
	}
}
#endif

/*
Вы устроились на новую работу и подключились к давно существующему проекту. Проект состоит в исследовании различных показателей по результатам переписи населения. Как это часто бывает, проект начинался как простая система, которая решала одну задачу, но со временем в неё стали добавлять новые функции. Делалось это как обычно — в аврале и в последний момент.

Первой задачей, с которой начинался проект, было моделирование изменения возраста совершеннолетия. Экспериментаторы вводили различный возраст совершеннолетия и изучали, сколько в таком случае в обществе будет совершеннолетних людей. От этого рассчитывались годовые бюджеты, планы по сбору налога на доходы физических лиц и т.д.

Первая версия программы принимала на вход список всех людей, которые живут в государстве, полученный с помощью переписи населения. Затем ей на вход подавался поток команд вида "AGE N". Для каждой такой строки программа выводила в стандартный вывод сообщение "There are X adult people for maturity age N". Программа отлично работала и справлялась со списком в несколько миллионов людей.

Но потом начальство срочно захотело больше функций. Появилась новая команда — «WEALTHY M», в ответ на которую программа должна была выводить суммарный доход M богатейших людей общества в виде "Top-M people have total income X".

Когда тестирование новой функциональности ещё не было окончено, руководство потребовало немедленно поддержать команду «POPULAR_NAME M/W», в ответ на которую программа сообщала самое популярное женское или мужское имя в виде "Most popular name among people of gender M is Ivan".

Предыдущая команда быстро реализовала эту функциональность за 2 часа до дедлайна, убедилась, что на простейших тестах она корректно работает и поставила программу заказчику. Естественно, программа у заказчика не заработала, и он попросил её исправить, прислав подробнейшее описание найденных ошибок со всеми деталями. Выглядело оно так: «Ваша программа вообще не работает! Срочно исправьте, а то засужу».

Прежнюю команду, естественно, тут же уволили и наняли вас =) Итак, вам дана программа и единственный тест, на котором её тестировали. Вам надо сделать всё хорошо.
Формат ввода

На вход программе поступает число N — количество людей. Далее идут N строк в формате Имя Возраст Доход Пол. Далее идут сами команды, по одной в строке.

Виды команд:

	AGE N — в ответ на неё в отдельной строке программа должна вывести сообщение "There are X adult people for maturity age N", где X — количество людей, возраст которых не меньше N

	WEALTHY M — в ответ на неё в отдельной строке программа должна вывести сообщение "Top-M people have total income X", где X — суммарный доход первых M богатейших людей.

	POPULAR_NAME M — в ответ на неё в отдельной строке программа должна вывести сообщение "Most popular name among people of gender M is S", где S — мужское имя, которое встречается больше всего раз. Если таких имён несколько, программа должна вывести лексикографически минимальное. Если таких имён нет, должно быть выведено "No people of gender M".

	POPULAR_NAME W — в ответ на неё в отдельной строке программа должна вывести сообщение "Most popular name among people of gender W is S", где S — женское имя, которое встречается больше всего раз. Если таких имён несколько, программа должна вывести лексикографически минимальное. Если таких имён нет, должно быть выведено "No people of gender W".

Пример
Ввод

11
Ivan 25 1000 M
Olga 30 623 W
Sergey 24 825 M
Maria 42 1254 W
Mikhail 15 215 M
Oleg 18 230 M
Denis 53 8965 M
Maxim 37 9050 M
Ivan 47 19050 M
Ivan 17 50 M
Olga 23 550 W
AGE 18
AGE 25
WEALTHY 5
POPULAR_NAME M

Вывод

There are 9 adult people for maturity age 18
There are 6 adult people for maturity age 25
Top-5 people have total income 39319
Most popular name among people of gender M is Ivan
*/