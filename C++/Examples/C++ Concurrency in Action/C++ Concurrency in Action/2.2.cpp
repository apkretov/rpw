#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <thread>
#include "../../stdafx.h"

#if 0

void f(int i, std::string const& s) {/**/}

void oops(int some_param) {
	char buffer[1024];
	sprintf(buffer, "%i", some_param);
	std::thread t(f, 3, buffer);
	t.detach();
}

int main() {
	print_file_line();
	oops(0);
}
#endif //1

#if 0

struct widget_data {};

using widget_id = int;

//TEST! void update_data_for_widget(widget_id w, widget_data& data) {}
void update_data_for_widget(widget_id w, const widget_data& data) {} //MINE

void oops_again(widget_id w) {
	widget_data data;
	std::thread t(update_data_for_widget, w, data);
	t.join();
}

int main() {
	print_file_line();
	oops_again(widget_id{});
}
#endif // 1

#if 0

class X {
public:
	void do_lengthy_work() {}
};

int main() {
	print_file_line();
	
	X my_x;
	std::thread t(&X::do_lengthy_work, &my_x);
	t.join(); //MINE
}
#endif // 1

#if 0

#include <memory>

struct big_object {
	void prepare_data(int) const {/**/}
};

void process_big_object(std::unique_ptr<big_object>) {/**/}

void process_big_shapred_object(std::shared_ptr<big_object>) {/**/} //MINE

int main() {
	print_file_line();

	std::unique_ptr<big_object> p(new big_object);
	p->prepare_data(42);
	std::thread t(process_big_object, std::move(p));
	t.join(); //MINE

	auto sp = std::make_shared<big_object>(); //MINE
	std::jthread t2(process_big_shapred_object, sp);
}
#endif // 1
