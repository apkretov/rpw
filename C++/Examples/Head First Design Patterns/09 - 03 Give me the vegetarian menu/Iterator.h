#pragma once

#pragma region Trae
template <typename T>
class Iterator {
public:
    virtual T& next() = 0;
    virtual bool hasNext() noexcept = 0;
    virtual ~Iterator() = 0;
};

template <typename T>
inline Iterator<T>::~Iterator() = default;
#pragma endregion //Trae