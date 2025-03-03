#if 0

#include <fstream>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

pair<ifstream, ofstream> MakeStreams(const string &prefix) {
#ifndef _1
	ifstream input(prefix + ".in");
	ofstream output(prefix + ".out");
	//TEST! return {input, output}; //																													Error.
	return {move(input), move(output)}; //TEST!
#else // _2
	return {ifstream(prefix + ".in"),  ofstream(prefix + ".out")}; //TEST! //																			RVO for an ifstream object whose copy constructor is deleted (see <fstream>: basic_ifstream(const basic_ifstream&) = delete;)
#endif // _2
}

ifstream Mine(const string &prefix) {
	ifstream input(prefix + ".in");
	return input; //TEST! //																															NRVO for an ifstream object whose copy constructor is deleted (see <fstream>: basic_ifstream(const basic_ifstream&) = delete;)
}

ifstream MakeIntputStream(const string &prefix) {
#ifndef _1
	auto streams = MakeStreams(prefix);
	//TEST! return streams.first; //																													Error.
#ifdef _1_1
	return move(streams).first; //TEST!
#else //_1_2
	return move(streams.first); //TEST!
#endif //_1_2
#else //_2
	return MakeStreams(prefix).first; //TEST!
#endif //_2
}

int main() {
	PRINT_FILE_LINE();
}
#endif