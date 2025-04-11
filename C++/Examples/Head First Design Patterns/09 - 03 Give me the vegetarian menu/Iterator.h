#pragma once

#pragma region Trae
template <typename T>
class Iterator {
public:
    virtual T* next() = 0;
    virtual bool hasNext() = 0;
    virtual ~Iterator() {}
};
#pragma endregion //Trae