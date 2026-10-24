#if 0

#include "../../stdafx.h"
import std;

std::generator<int> natural_nums() {
	int num = 0;
	for (;;) {
		co_yield num;
		num += 1;
	}
}

int main() {
	print_file_line();

	auto gen = natural_nums(); // std::generator is not a viewable_range, so it must be wrapped in ranges::ref_view before piping into views::take. // nums is a view, so the generator itself must outlive it: keep it in a named variable.
	auto nums = std::ranges::ref_view(gen) | std::views::take(14);

	for (const auto i : nums)
		std::cout << AS_KV(i) << '\n';

	return 0;
}
#endif // 1
