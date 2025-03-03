#pragma once

#ifndef EX_15_26

#include <vector>
#include <algorithm>
using namespace std;

void objects() {
	cout << "Bulk_quote b1(\"aaa\", 100, 10, 1):\n";
	Bulk_quote b1("aaa", 100, 10, 1);

	cout << "\ndecltype(b1) b2(b1):\n";
	decltype(b1) b2(b1);
	b2.setBookNo("bbb");

	cout << "\nQuote q(b1):\n";
	Quote q(b1); //TEST!
	string bookNo = "ccc";
	q.setBookNo(bookNo);

	//TEST! Disc_quote d(b1);

	cout << "\nBulk_quote b3:\n";
	Bulk_quote b3;

	cout << "\nb3 = b1:\n";
	b3 = b1;
	b3.setBookNo("ddd");

	cout << "\nauto b4(std::move(b1)):\n";
	auto b4(std::move(b1));
	b4.setBookNo("eee");

	cout << "\n\nreturn from objects():\n\n";
}

void pointers_object() {
	std::cout << "Quote q(\"aaa\", 100):\n";
	Quote q("aaa", 100);

	cout << "\nBulk_quote b(\"bbb\", 200, 20, 2):\n";
	Bulk_quote b("bbb", 200, 20, 2);

	vector<Quote *> v;
	v.push_back(&q);
	v.push_back(&b);

	cout << "\nfor_each(v.cbegin(), v.cend(), [](Quote *p) { p->net_price(1); }):\n";
	for_each(v.cbegin(), v.cend(), [](Quote *p) { p->net_price(1); });

	cout << "\nreturn from pointers():\n\n";
}

void pointers_new() {
	vector<Quote *> v;
	cout << "v.push_back(new Quote(\"aaa\", 100)):\n";
	v.push_back(new Quote("aaa", 100));
	cout << "\nv.push_back(new Bulk_quote(\"bbb\", 200, 20, 2)):\n";
	v.push_back(new Bulk_quote("bbb", 200, 20, 2));

	cout << "\n\nfor_each(v.begin(), v.end(), [](Quote *p) { delete p; }):\n\n";
	for_each(v.begin(), v.end(), [](Quote *p) { delete p; }); //TEST!

	cout << "\nreturn from pointers():\n\n";
}
#endif