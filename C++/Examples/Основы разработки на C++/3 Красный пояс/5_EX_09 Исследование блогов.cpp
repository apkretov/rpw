#if 1 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_5/09%20Programming%20Assignment

#ifdef MINE_1 

#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

struct Stats {
#pragma region cpp:S5018
	Stats() = default;
	Stats(const Stats &) = default;
	Stats &operator=(const Stats &) = default;
	Stats(Stats &&) noexcept = default; // cpp:S5018: Move and swap operations should be "noexcept". //MINE: This is because of the std::map member.
	Stats &operator=(Stats &&) noexcept = default;
#pragma endregion //cpp:S5018
	map<string, int, less<>> word_frequencies;

	void operator+=(const Stats &other) {
		for (const auto &[word, count] : other.word_frequencies) {
#ifdef MINE
			if (auto word_iter = word_frequencies.find(word); word_iter != word_frequencies.end())
				word_iter->second += count;
			else
				word_frequencies[word] = count;
#else //GITHUB
			word_frequencies[word] += count; //TEST!
#endif //GITHUB
		}
	}
};

Stats ExploreLine(const set<string> &key_words, const string &line) {
	Stats result;
	auto &word_frequencies = result.word_frequencies;
	stringstream words(line);

	for (string word; words >> word;) {
		if (key_words.contains(word)) {
#ifdef MINE
			if (auto word_iter = word_frequencies.find(word); word_iter == word_frequencies.end())
				word_frequencies[std::move(word)] = 1;
			else
				++word_iter->second;
#else //GITHUB
			++word_frequencies[std::move(word)]; //TEST!
#endif //MINE
		}
	}

	return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input) {
	vector<future<Stats>> futures;
	for (string line; getline(input, line);)
#ifdef MINE
		futures.push_back(async(launch::async, ExploreLine, ref(key_words), line));
#else //PERPLEXITY: emplace_back constructs the std::future directly in place and invokes the move constructor when transferring from a temporary. This approach is generally more efficient than using push_back, which would involve creating a temporary and then moving or copying it into the vector.
		futures.emplace_back(async(launch::async, ExploreLine, ref(key_words), line));
#endif //PERPLEXITY

	Stats result;
	for (auto &f : futures)
		result += f.get();
	return result;
}

Stats ExploreKeyWordsSingleThread(const set<string> &key_words, istream &input) {
	Stats result;
	for (string line; getline(input, line);)
		result += ExploreLine(key_words, line);
	return result;
}

void TestBasic() {
	const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
	  {"yangle", 6},
	  {"rocks", 2},
	  {"sucks", 1}
	};
	//ORIG ASSERT_EQUAL(stats.word_frequencies, expected);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestBasic);

	return 0;
}
#endif //MINE_1

#ifndef MINE_2

#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

struct Stats {
#pragma region cpp:S5018
	Stats() = default;
	Stats(const Stats &) = default;
	Stats &operator=(const Stats &) = default;
	Stats(Stats &&) noexcept = default; // cpp:S5018: Move and swap operations should be "noexcept". //MINE: This is because of the std::map member.
	Stats &operator=(Stats &&) noexcept = default;
#pragma endregion //cpp:S5018
	map<string, int, less<>> word_frequencies;

	void operator+=(const Stats &other) {
		for (const auto &[word, count] : other.word_frequencies)
			word_frequencies[word] += count;
	}
};

Stats ExploreLine(const set<string> &key_words, const string &line) {
	Stats result;
	auto &word_frequencies = result.word_frequencies;
	stringstream words(line);

	for (string word; words >> word;)
		if (key_words.contains(word))
			++word_frequencies[std::move(word)];

	return result;
}

Stats ExploreBatch(const set<string> &key_words, vector<string> &&batch) {
	Stats result;
	for (const auto &line : batch)
		result += ExploreLine(key_words, line);
	return result;
}

template <typename T>
Stats ExploreKeyWords(const set<string> &key_words, T &input) {
	vector<future<Stats>> futures;
	constexpr size_t batch_size = 5000;
	vector<string> batch;
	batch.reserve(batch_size);

	for (string line; getline(input, line);) {
		batch.emplace_back(std::move(line));
		if (batch.size() == batch_size) {
			futures.emplace_back(async(launch::async, ExploreBatch, ref(key_words), std::move(batch)));
			batch.reserve(batch_size);
		}
	}
	Stats result;
	if (!batch.empty())
		result += ExploreBatch(key_words, std::move(batch));

	for (auto &f : futures)
		result += f.get();
	return result;
}

template <typename T>
Stats ExploreKeyWordsSingleThread(const set<string> &key_words, T &input) {
	Stats result;
	for (string line; getline(input, line);)
		result += ExploreLine(key_words, line);
	return result;
}

void TestBasic() {
	const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	{
		LOG_DURATION("ExploreKeyWords");
		const auto stats = ExploreKeyWords(key_words, ss);
	}
	const map<string, int> expected = {
	  {"yangle", 6},
	  {"rocks", 2},
	  {"sucks", 1}
	};
	//ORIG ASSERT_EQUAL(stats.word_frequencies, expected);
}

void TestMine() {
	const set<string> key_words = {"yangle", "rocks", "sucks", "all"};
#ifndef SMALL_FILE
	const string file_name = __FILE__;
#else //LARGE_FILE
	const string file_name = "5_EX_09 - Input.txt";
#endif //LARGE_FILE
	ifstream fs(file_name);
	if (!fs.good()) {
		filesystem::path current_path = filesystem::current_path();
		current_path = current_path.make_preferred(); // Eliminate double backslashes "\\".
		throw(runtime_error(file_name + " does not exist in " + current_path.string() + "!"));
	}
	if (!fs.is_open())
		throw(runtime_error(file_name + " is not opened!"));

	{
		LOG_DURATION("ExploreKeyWords");
		const auto stats = ExploreKeyWords(key_words, fs); // No performance boost with a small file.
	}
	{
		fs.close();
		fs.open(file_name);
		LOG_DURATION("ExploreKeyWordsSingleThread");
		const auto stats = ExploreKeyWordsSingleThread(key_words, fs);
	}
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestBasic);
	RUN_TEST(tr, TestMine);

	return 0;
}
#endif //MINE_2

#ifdef GITHUB_1 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_5/09%20Programming%20Assignment/Solution/explore_key_words.cpp

#include <algorithm>
#include <future>
#include <map>
#include <set>
#include <string>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

struct Stats {
	map<string, int> word_frequences;
	void operator += (const Stats &other);
};

void Stats::operator += (const Stats &other) {
	for (auto &[word, frequency] : other.word_frequences) {
		word_frequences[word] += frequency;
	}
}

Stats ExploreLine(const set<string> &key_words, const string &line) {
	Stats words;
	string_view line_view(line);

	auto pos_view = line_view.find_first_not_of(" ");
	line_view.remove_prefix(pos_view);

	while (pos_view != string_view::npos) {

		pos_view = line_view.find_first_of(" ");
		auto key = string(line_view.substr(0, pos_view));

		if (key_words.count(key) > 0) {
			words.word_frequences[std::move(key)]++;
		}

		if (pos_view == string::npos) {
			break;
		} else {
			line_view.remove_prefix(pos_view + 1);
		}
	}
	return words;
}

Stats ExploreKeyWordsSingleThread(const set<string> &key_words, istream &input) {
	Stats result;
	for (string line; getline(input, line); ) {
		result += ExploreLine(key_words, line);
	}
	return result;
}

Stats ExploreBatch(const set<string> &key_words, vector<string> lines) {
	Stats result;
	for (const string &line : lines) {
		result += ExploreLine(key_words, line);
	}
	return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input) {
	Stats result;
	vector<future<Stats>> futures;
	const size_t max_batch_size = 5000;

	vector<string> batch;
	batch.reserve(max_batch_size);

	for (string line; getline(input, line); ) {
		batch.push_back(std::move(line));
		if (batch.size() >= max_batch_size) {
			futures.push_back(async(ExploreBatch, ref(key_words), std::move(batch))); //TEST!
			batch.reserve(max_batch_size);
		}
	}

	if (!batch.empty()) {
		result += ExploreBatch(key_words, std::move(batch));
	}

	for (auto &f : futures) {
		result += f.get();
	}
	return result;
}

void TestBasic() {
	const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {{"yangle", 6},
									  {"rocks", 2},
									  {"sucks", 1}};
	//ORIG ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	LOG_DURATION("All tests");
	tr.RunTest(TestBasic, "TestBasic");
}
#endif //GITHUB_1

#ifdef GITHUB_2

#include <algorithm>
#include <map>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <sstream>
#include <future>
#include <iterator>
#include <set>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

struct Stats {
	map<string, int> word_frequences;

	void operator += (const Stats &other) {
		for (auto &[word, frequency] : other.word_frequences) {
			word_frequences[word] += frequency;
		}
	}
};

set<string> ReadKeyWords(istream &is) {
	return {istream_iterator<string>(is), istream_iterator<string>()}; //TEST!
}

vector<string> Split(const string &line) {
	istringstream line_splitter(line); // http://en.cppreference.com/w/cpp/iterator/istream_iterator
	return {istream_iterator<string>(line_splitter), istream_iterator<string>()}; //TEST!
}

Stats ExploreLine(const set<string> &key_words, const string &line) {
	Stats result;
	for (const string &word : Split(line)) {
		if (key_words.count(word) > 0)
			result.word_frequences[word]++;
	}
	return result;
}

Stats ExploreKeyWordsSingleThread(const set<string> &key_words, istream &input) {
	Stats result;
	for (string line; getline(input, line); )
		result += ExploreLine(key_words, line);
	return result;
}

Stats ExploreBatch(const set<string> &key_words, vector<string> lines) {
	Stats result;
	for (const string &line : lines)
		result += ExploreLine(key_words, line);
	return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input) {
	const size_t max_batch_size = 5000;
	vector<string> batch;
	batch.reserve(max_batch_size);
	vector<future<Stats>> futures;

	for (string line; getline(input, line); ) {
		batch.push_back(std::move(line));
		if (batch.size() >= max_batch_size) {
			futures.push_back(async(ExploreBatch, ref(key_words), std::move(batch)));
			batch.reserve(max_batch_size);
		}
	}

	Stats result;
	if (!batch.empty())
		result += ExploreBatch(key_words, std::move(batch));

	for (auto &f : futures)
		result += f.get();
	return result;
}

void TestSplit() {
	const vector<string> expected1 = {
	  "abc", "def", "ghi,", "!", "jklmnop-qrs,", "tuv"
	};
	//ORIG ASSERT_EQUAL(Split("  abc def ghi, !  jklmnop-qrs, tuv"), expected1);

	const vector<string> expected2 = {"a", "b"};
	//ORIG ASSERT_EQUAL(Split("a b      "), expected2);
	//ORIG ASSERT_EQUAL(Split(""), vector<string>());
}

void TestBasic() {
	const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
	  {"yangle", 6},
	  {"rocks", 2},
	  {"sucks", 1}
	};
	//ORIG ASSERT_EQUAL(stats.word_frequences, expected);
}

void TestMtAgainstSt() {
	ifstream key_words_input("key_words.txt");
	const auto key_words_data = ReadKeyWords(key_words_input);
	const set<string> key_words(key_words_data.begin(), key_words_data.end());

	Stats st_stats, mt_stats;
	{
		ifstream text_input("text.txt");
		LOG_DURATION("Single thread");
		st_stats = ExploreKeyWordsSingleThread(key_words, text_input);
	}
	{
		ifstream text_input("text.txt");
		LOG_DURATION("Multi thread");
		mt_stats = ExploreKeyWords(key_words, text_input);
	}

	//ORIG ASSERT_EQUAL(st_stats.word_frequences, mt_stats.word_frequences);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestSplit);
	RUN_TEST(tr, TestBasic);
	RUN_TEST(tr, TestMtAgainstSt);
}
#endif //GITHUB_2

#endif //1

/*
Исследование блогов
Условие

Крупная IT-компания Янгл проводит исследование упоминаемости своего бренда в блогах и социальных сетях. Аналитики компании уже выгрузили интересующие их публикации и сформировали набор ключевых слов. Их интересует, сколько раз каждое ключевое слово входит в набор публикаций.

Помогите им это сделать — напишите функцию Stats ExploreKeyWords(const set& key_words, istream& input). Её параметры:

	key_words — множество ключевых слов
	input — входной поток, содержащий исследуемые публикации в блогах и соц. сетях, одна строка — одна публикация.

Функция ExploreKeyWords должна возвращать структуру Stats, в которой хранится, сколько раз каждое слово из key_words суммарно встретилось в потоке input:

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other);
};

При подсчёте вхождения ключевых слов в текст нужно учитывать только вхождения в виде отдельных слов. Слова друг от друга отделяются одним или несколькими пробелами. В качестве примера допустим, что key_words = {"yangle", "rocks", "sucks", "all"} и у нас есть публикация из соц. сети Switter: "Goondex really sucks, but yangle rocks ! Use yangle". Слово «yangle» входит в неё 2 раза, «rocks» — один раз, а слова «all» и «sucks» — ни разу. Слово «sucks» не входит ни разу, потому что в данном примере оно является префиксом слова «sucks,» (по условию, слова друг от друга отделяются только пробелами). Несмотря на то, что слово «all» является частью слова «really», его вхождение тоже нельзя засчитывать, так как это не отдельное слово.

Чтобы уложиться в Time Limit, подумайте, можно ли эту задачу распараллелить.
Замечание

До этого в лекциях мы показывали, как использовать функцию async для асинхронного запуска лямбда-функций без параметров. Однако её можно использовать и для запуска функций, у которых есть параметры. Например,

string Join(string s, string t) {
  return s + t;
}

string a = "Hello";
string b = " world";
future<string> f = async(Join, a, b);

Как видите, чтобы передать параметры в функцию, запускаемую асинхронно, их надо указать в качестве параметров функции async после самой функции. Важно отметить, что при таком вызове будут созданы копии фактических параметров (т.е. в нашем примере выше строки a и b будут скопированы). Это не всегда желательно. Например, если у нас есть константный объект, который потоки только читают, у нас нет необходимости создавать его копию, и можно передать его по ссылке. Для этого надо воспользоваться функцией ref ref из заголовочного файла .

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, istream& input);

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  // key_words и input будут переданы по ссылке, а не скопированы
  return async(ExploreKeyWordsSingleThread, ref(key_words), ref(input)).get();
}

Файл с заготовкой решения

explore_key_words.cpp
*/