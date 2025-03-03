#if 0

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>
#include "../../stdafx.h"
using namespace std;

struct Image {
	double quality;
	double freshness;
	double rating;
};

struct Params {
	double a;
	double b;
	double c;
};

class FunctionPart {
public:
	FunctionPart(char new_operatoin, double new_value) {
		operation = new_operatoin;
		value = new_value;
	}

	double Apply(double source_value) const {
		if (operation == '+')
			return source_value + value;
		else
			return source_value - value;
	}

	void Invert() { //TEST
		if (operation == '+')
			operation = '-';
		else
			operation = '+';
	}
private:
	char operation;
	double value;
};

class Function {
public:
	void AddPart(char operation, double value) {
		parts.push_back({operation, value});
	}

	double Apply(double value) const {
		for (const FunctionPart &part : parts)
			value = part.Apply(value);
		return value;
	}

	void Invert() { //TEST
		for (FunctionPart &part : parts)
			part.Invert();
		reverse(begin(parts), end(parts));
	}
private:
	vector<FunctionPart> parts;
};

Function MakeWeightFunction(const Params &params, const Image &image) {
	Function function;
	function.AddPart('-', image.freshness * params.a + params.b);
	function.AddPart('+', image.rating * params.c);
	return function;
}

double ComputeImageWeight(const Params &params, const Image &image) {
#ifdef _1
	double weight = image.quality;
	weight -= image.freshness * params.a + params.b;
	weight += image.rating * params.c;
	return weight;
#else //_2
	Function function = MakeWeightFunction(params, image);
	return function.Apply(image.quality);
#endif
}

double ComputeQualityByWeight(const Params &params, const Image &image, double weight) {
#ifdef _1
	double quality = weight;
	quality -= image.rating * params.c;
	quality += image.freshness * params.a + params.b;
	return quality;
#else //_2
	Function function = MakeWeightFunction(params, image);
	function.Invert();
	return function.Apply(weight);
#endif
}

int main(int argc, char *[]) {
	PRINT_FILE_LINE();

	constexpr int quality = 10;

	Image image = {quality, 2, 6};
	Params params{4, 2, 6};

	auto w = ComputeImageWeight(params, image);
	cout << "ComputeImageWeight = " << w << '\n';

	auto q = ComputeQualityByWeight(params, image, w);
	cout << "ComputeQualityByWeight = " << q << '\n';

	return 0;
}
#endif