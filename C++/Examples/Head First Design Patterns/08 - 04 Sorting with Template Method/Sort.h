#pragma once

#include <algorithm> 
#include <vector>
using std::vector;

#pragma region Sorting with Template Method
/* Java
public static void sort(Object[] a) {
    Object aux[] = (Object[])a.clone();
    mergeSort(aux, a, 0, a.length, 0);
}

private static void mergeSort(Object src[], Object dest[],
                            int low, int high, int off) {
    for (int i=low; i<high; i++) {
        for (int j=i; j>low &&
            ((Comparable)dest[j-1]).compareTo((Comparable)dest[j])>0; j--) {
            swap(dest, j, j-1);
        }
    }
    return;
}
*/
template<typename T>
class Sort {
public:
    static void sort(vector<T>& a) { // The first method, sort(), is just a helper method that creates a copy of the array and passes it along as the destination array to the mergeSort() method
        vector<T> aux = a;
        mergeSort(aux, a, 0, a.size(), 0);
    }

private:
    static void mergeSort(vector<T>& src, vector<T>& dest, int low, int high, int off) { // The mergeSort() method contains the sort algorithm, and relies on an implementation of the compareTo() method to complete the algorithm
        for (int i = low; i < high; i++) // Think of this as the template method
            for (int j = i; j > low && dest[j-1].compareTo(&dest[j]) > 0; j--) // compareTo() is the method we need to implement to "fill out" the template method
                std::swap(dest[j], dest[j-1]); // This is a concrete method, already defined in the Arrays class
    }
};
#pragma endregion //Sorting with Template Method