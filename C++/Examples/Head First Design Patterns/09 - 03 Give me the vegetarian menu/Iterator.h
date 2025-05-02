#pragma once

#pragma region Trae
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    
	virtual T& next() = 0;
    virtual bool hasNext() const = 0;
};
#pragma endregion //Trae