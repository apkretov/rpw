#pragma once

#include <vector>
using namespace std;

#define MINE
#undef GITHUB

#ifdef MINE

/*
c:{
	-> {},	//0		= f
	-> }	//2000	= l
c:{
	-> {},	//2000	= f
	-> }	//4000	= l
c:{
	-> {},	//4000	= f
	-> }	//6000	= l
c:{
	-> {},	//6000	= f
	-> }	//7000	= l
*/
template <typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator f, Iterator l) : first(f), last(l) {}
	Iterator begin() const { return first; }
	Iterator end() const { return last; }
	size_t size() const { return distance(first, last); }
private:
	Iterator first;
	Iterator last;
};

/*  
page_size = 2000
c:{
	-> {},	//0		= f
	-> }	//7000	= l
*/
template <typename Iterator>
class Paginator {
public:
	Paginator(Iterator f, Iterator l, size_t page_size) { // пара итераторов begin и end задают полуинтервал begin; end, который мы будем нарезать на страницы // page_size - размер одной страницы
		for (auto first = f, last = f; first != l; first = last) {
			last = next(first, min(static_cast<iterator_traits<Iterator>::difference_type>(page_size), distance(first, l)));
			iter_ranges.push_back(IteratorRange{first, last});
		}
	}

	auto begin() const { return iter_ranges.begin(); } // auto stands both for vector<PageRange<Iterator>>::iterator and vector<PageRange<Iterator>>::const_iterator.
	auto end() const { return iter_ranges.end(); }
	size_t size() const { return iter_ranges.size(); } // количество страниц, на которые был разбит переданный контейнер
private:
	vector<IteratorRange<Iterator>> iter_ranges;
};

/*
page_size = 2000
c:{
	{},	//0
	{},	//1
	{},	//2
	...
	{}	//6999
}		//7000
*/
template <typename C>
auto Paginate(C &c, size_t page_size) { //TEST // More explicitly: auto Paginate(C &c, size_t page_size) -> decltype(Paginator<decltype(c.begin())>(c.begin(), c.end(), page_size))
	return Paginator{c.begin(), c.end(), page_size};
}
#endif //MINE

#ifdef GITHUB //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_1/09%20Programming%20Assignment/Solution/paginator.cpp
template <typename Iterator>
struct IteratorRange {
public:
	IteratorRange(Iterator begin, Iterator end) : first(begin), last(end) {}
	Iterator begin() const { return first; }
	Iterator end() const { return last; }
	size_t size() const { return last - first; }
private:
	Iterator first;
	Iterator last;
};

template <typename Iterator>
class Paginator {
public:
	Paginator(Iterator begin, Iterator end, size_t page_size) {
		auto min_value = [&](Iterator itr) { return min<size_t>(distance(itr, end), page_size); };

		for (auto ptr = begin; ptr != end; ptr = next(ptr, min_value(ptr)))
			pages.push_back(IteratorRange{ptr, next(ptr, min_value(ptr))});
	}

	auto begin() const { return pages.begin(); }
	auto end() const { return pages.end(); }
	size_t size() const { return pages.size(); }
private:
	vector<IteratorRange<Iterator>> pages;
};

template <typename C>
auto Paginate(C &c, size_t page_size) {
	return Paginator(c.begin(), c.end(), page_size);
}
#endif //GITHUB