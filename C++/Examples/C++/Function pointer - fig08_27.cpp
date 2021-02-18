#include <iostream> // Fig. 8.27: fig08_27.cpp // Multipurpose sorting program using function pointers.
using std::cout;
using std::cin;
using std::endl;
#include <iomanip>
using std::setw;

void selectionSort( int [], const int, bool (*)( int, int ) ); // prototypes
void swap( int * const, int * const );   
bool ascending( int, int ); // implements ascending order
bool descending( int, int ); // implements descending order

int main() {
   const int arraySize = 10;
   int order; // 1 = ascending, 2 = descending
   int counter; // array index
   int a[ arraySize ] = { 2, 6, 4, 8, 10, 12, 89, 68, 45, 37 };
   cout << "Enter 1 to sort in ascending order,\n" << "Enter 2 to sort in descending order: ";
   cin >> order;
   cout << "\nData items in original order\n";
   for ( counter = 0; counter < arraySize; counter++ ) cout << setw( 4 ) << a[ counter ]; // output original 
   if ( order == 1 ) { // sort array in ascending order; pass function ascending as an argument to specify ascending sorting order
      selectionSort( a, arraySize, ascending );
      cout << "\nData items in ascending order\n";
   }else{ // sort array in descending order; pass function descending as an argument to specify descending sorting order
      selectionSort( a, arraySize, descending );
      cout << "\nData items in descending order\n";
   }
   for ( counter = 0; counter < arraySize; counter++ ) cout << setw( 4 ) << a[ counter ]; // output sorted array
   cout << endl;
   return 0; 
}

void selectionSort( int work[], const int size, bool (*compare)( int, int ) ) { // multipurpose selection sort; the parameter compare is a pointer to the comparison function that determines the sorting order
   int smallestOrLargest; // index of smallest (or largest) 
   for ( int i = 0; i < size - 1; i++ ) { // loop over size - 1 elements
      smallestOrLargest = i; // first index of remaining vector
      for ( int index = i + 1; index < size; index++ ) // loop to find index of smallest (or largest) element
         if ( !(*compare)( work[ smallestOrLargest ], work[ index ] ) ) smallestOrLargest = index;
      swap( &work[ smallestOrLargest ], &work[ i ] );
   }
}

void swap( int * const element1Ptr, int * const element2Ptr ) { // swap values at memory locations to which and element2Ptr point
   int hold = *element1Ptr;
   *element1Ptr = *element2Ptr;
   *element2Ptr = hold;
}

bool ascending( int a, int b ) { return a < b; } // determine whether element a is less than b for an ascending order sort
bool descending( int a, int b ) { return a > b; } // determine whether element a is greater than element b for a descending order sort
