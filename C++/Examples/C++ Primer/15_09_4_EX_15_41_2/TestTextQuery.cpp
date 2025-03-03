#ifndef ON //MINE

//OFF #include <vld.h> //MINE
#include <iostream> // ch15/15.41 @ https://github.com/jaege/Cpp-Primer-5th-Exercises/tree/master/ch15/15.41
#include <fstream>
#include "TextQuery.h"
#include "QueryResult.h"
#include "../../stdafx.h" //MINE

void runQueries(std::ifstream &infile) {
  TextQuery tq(infile);
  while (true) {
    std::cout << "Enter word to look for, or 'q' to exit: ";
    std::string s;
    if (!(std::cin >> s) || s == "q")
      break;
    print(std::cout, tq.query(s)) << std::endl;
  }
}

int main() {
  print_file_line();

  std::cout << "Enter the file name to look up: ";
  std::string filename;
  std::cin >> filename;
  std::ifstream in(filename);
  if (!in.is_open()) {
    std::cerr << "Cannot open file: " << filename << std::endl;
    return -1;
  }
  runQueries(in);

  return 0;
}
#endif