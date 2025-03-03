#pragma once

#include <algorithm>
#include <vector>

std::vector<int> Sorted(std::vector<int> data) {
	std::sort(data.begin(), data.end());
	return data;
}
