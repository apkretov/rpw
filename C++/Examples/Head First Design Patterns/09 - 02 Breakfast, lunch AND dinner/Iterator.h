#pragma once

#pragma once

/* Java code
public interface Iterator<T> {
	boolean hasNext();
	T next();
}
*/
template<typename T>
class Iterator {
public:
	virtual ~Iterator() = default;
	virtual bool hasNext() = 0;
	virtual T &next() = 0;
};