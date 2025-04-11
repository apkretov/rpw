#pragma once

#include "Iterator.h"
#include <vector>
using std::vector;

#pragma region Trae
template <typename T>
class VectorIterator : public Iterator<T> {
    vector<T*>& items;
    int position = 0;

public:
    VectorIterator(vector<T*>& items) : items(items) {}

    T& next() override {
        if (hasNext())
            return *items[position++];
        throw std::runtime_error("No more items");
    }

    bool hasNext() noexcept override { return position < items.size(); }
};
#pragma endregion //Trae
