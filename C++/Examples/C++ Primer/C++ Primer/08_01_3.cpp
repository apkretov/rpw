#ifdef ON

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLIne: " << __LINE__ << "\n\n";

#ifdef Flushing_the_Output_Buffer
	cout << "hi!" << endl; //																																										writes hi and a newline, then flushes the buffer 
	//TEST! cout << "hi!" << flush; //																																								writes hi, then flushes the buffer; adds no data 
	//TEST! cout << "hi!" << ends; //																																								writes hi and a null, then flushes the buffer 
#endif

#ifdef The_unitbuf_Manipulator
	//TEST! cout << unitbuf; //																																										all writes will be flushed immediately 
	//																																																any output is flushed immediately, no buffering
	cout << "Hi after unitbuf!"; //MINE
	//TEST! cout << nounitbuf; //																																									returns to normal buffering 
#endif

#ifndef Tying_Input_and_Output_Streams_Together //TEST
	cin.tie(&cout); // illustration only: the library ties cin and cout for us 
	// !old_tie points to the stream(if any) currently tied to cin
	ostream *old_tie = cin.tie(nullptr); // cin is no longer tied 
	// I ties cin and cerr; not a good idea because cin should be tied to cout
	cin.tie(&cerr); // reading cin flushes cerr, not cout 
	cin.tie(old_tie); // reestablish normal tie between cin and cout 
#endif

	return 0;
}
#endif