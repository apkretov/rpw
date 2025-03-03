#include "16_01_1.h"
#include "16_01_4_1.h"

template int compare(const int &, const int &); // instantiation file must provide a (nonextern) definition for every // type and function that other files declare as extern
template class Blob<string>; // instantiates all members of the class template