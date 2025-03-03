#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_2/03%20Practice%20Programming%20Assignment

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "../../stdafx.h"
using namespace std;

#undef GITHUB_VECTOR 
#define MINE
#undef GITHUB_SET

#ifdef GITHUB_VECTOR //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_2/03%20Practice%20Programming%20Assignment/Source/slow.cpp
class RouteManager {
public:
	void AddRoute(int start, int finish) {
		reachable_lists_[start].push_back(finish);
		reachable_lists_[finish].push_back(start);
	}

	int FindNearestFinish(int start, int finish) const {
		int result = abs(start - finish);
		if (reachable_lists_.count(start) < 1) {
			return result;
		}

		const vector<int> &reachable_stations = reachable_lists_.at(start);
		if (!reachable_stations.empty()) {
			result = min(
				result,
				abs(finish - *min_element(
					begin(reachable_stations), end(reachable_stations),
					[finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); }
				))
			);
		}
		return result;
	}
private:
	map<int, vector<int>> reachable_lists_;
};
#endif //GITHUB_VECTOR

#ifdef MINE
class RouteManager {
public:
	void AddRoute(int start, int finish) {
		reachable_lists_[start].insert(finish);
		reachable_lists_[finish].insert(start);
	}

	int FindNearestFinish(int start, int finish) const {
		int result = abs(start - finish);

		if (!reachable_lists_.contains(start)) //ORIG if (reachable_lists_.count(start) < 1)
			return result;

		if (const set<int> &reachable_stations = reachable_lists_.at(start); !reachable_stations.empty()) {
			result = min(
				result,
				//abs(finish - *min_element(
				//	begin(reachable_stations), end(reachable_stations),
				//	[finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); }
				//))
				abs(finish - *reachable_stations.cbegin())
			);
		}
		
		return result;
	}
private:
	map<int, set<int>> reachable_lists_;
};
#endif //MINE

#ifdef GITHUB_SET
class RouteManager {
public:
	void AddRoute(int start, int finish) {
		reachable_lists_[start].insert(finish);
		reachable_lists_[finish].insert(start);
	}

	int FindNearestFinish(int start, int finish) const {
		int result = abs(start - finish);

		if (reachable_lists_.count(start) < 1) {
			return result;
		}

		const set<int> &reachable_stations = reachable_lists_.at(start);
		const auto finish_pos = reachable_stations.lower_bound(finish);
		if (finish_pos != end(reachable_stations)) {
			result = min(result, abs(finish - *finish_pos));
		}
		if (finish_pos != begin(reachable_stations)) {
			result = min(result, abs(finish - *prev(finish_pos)));
		}
		return result;
	}
private:
	map<int, set<int>> reachable_lists_;
};
#endif // GITHUB_SET

int main() {
#ifdef MINE
	cin.tie(nullptr);
#endif //MINE

	PRINT_FILE_LINE();

	LOG_DURATION("Total");
	RouteManager routes;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int start, finish;
		cin >> start >> finish;
		if (query_type == "ADD") {
			routes.AddRoute(start, finish);
		} else if (query_type == "GO") {
			cout << routes.FindNearestFinish(start, finish) << "\n";
		}
	}

	return 0;
}
#endif //1

/*
Таблица

Вам даны задача и её решение — верное, но не удовлетворяющее заданным ограничениям на время работы. Переработайте это решение и сдайте в систему.
Условие

Разработайте простейшую систему маршрутизации экспрессов, курсирующих по одному железнодорожному направлению, представляющему собой прямую. Ваша программа должна уметь обрабатывать запросы двух типов:

	ADD start finish — добавить в систему маршрутов экспресс, следующий со станции start до станции finish и обратно. Экспресс не делает промежуточных остановок. Станции задаются целыми числами, равными их расстоянию от вокзала (он имеет номер 0).
	GO start finish — попытаться проложить беспересадочный маршрут от станции start до станции finish. Если существует экспресс между этими двумя станциями, в ответ на данный запрос выведите 0. В противном случае выведите положительное число — минимальное расстояние, на которое можно приблизиться к станции finish, стартовав строго на станции start и использовав не более одного экспресса.

Формат входных данных

В первой строке вводится количество запросов Q — натуральное число, не превосходящее 10^5. В следующих Q строках в соответствии с описанным выше форматом вводятся запросы. Гарантируется, что номера станций являются целыми числами, по модулю не превосходящими 10^9.
Формат выходных данных

Для каждого запроса GO выведите единственное целое неотрицательное число — минимальное расстояние до конечной станции маршрута, вычисляемое в соответствии с описанными выше правилами.
Ограничения

1 секунда на выполнение всех запросов. Все описанные в условии гарантии действительно справедливы для всех тестов, на которых будет запускаться ваша программа. Проверять корректность тестов не нужно.
Пример

Ввод

7
ADD -2 5
ADD 10 4
ADD 5 8
GO 4 10
GO 4 -2
GO 5 0
GO 5 100

Вывод

0
6
2
92

Комментарий к примеру В первом запросе GO выгодно воспользоваться экспрессом 10 4. Во втором выгоднее остаться на месте, чем пользоваться экспрессом. В третьем и четвёртом запросах GO необходимо воспользоваться экспрессами -2 5 и 5 8.
Правильное, но медленное решение

slow.cpp
*/