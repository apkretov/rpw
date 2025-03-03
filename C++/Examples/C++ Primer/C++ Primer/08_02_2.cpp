#ifdef ON

#include <iostream>
#include <fstream>
using namespace std;

void Opening_a_File_in_out_Mode_Discards_Existing_Data() {
	// file1 is truncated in each of these cases
	ofstream out("file1"); // out and trunc are implicit
	ofstream out2("file1", ofstream::out); // trunc is implicit
	ofstream out3("file1", ofstream::out | ofstream::trunc);
	//																																																to preserve the file’s contents, we must explicitly specify app mode
	//TEST! ofstream app("file2", ofstream::app); //																																				out is implicit
	ofstream app2("file2", ofstream::out | ofstream::app);
}

void File_Mode_Is_Determined_Each_Time_open_Is_Called() {
	ofstream out; // no file mode is set
	out.open("scratchpad"); // mode implicitly out and trunc
#ifdef OFF
	//TEST! out.close(); //																																											close out so we can use it for a different file
	out.open("precious", ofstream::app); // mode is out and app
#endif
	out.close();
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif