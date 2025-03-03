//template <typename T>
//class SimpleVector { //VER2 Size, Capacity, PushBack & copy-constructor are added.
//public:
//	explicit SimpleVector(size_t size) {
//		data = new T[size];
//		end_ = data + size;
//	}
//
//	~SimpleVector() {
//		delete[] data;
//	}
//
//	T &operator[](size_t index) const {
//		return data[index]; // *(data + index)
//	}
//
//	const T *begin() const {
//		return data;
//	}
//
//	const T *end() const {
//		return end_;
//	}
//
//	T *begin() {
//		return data;
//	}
//
//	T *end() {
//		return end_;
//	}
//private:
//	T *data;
//	T *end_;
//};
//
//template <typename T>
//SimpleVector::SimpleVector(size_t size) {
//		data = new T[size];
//		end_ = data + size;
//	}
//
//	~SimpleVector() {
//		delete[] data;
//	}
//
//	T &operator[](size_t index) const {
//		return data[index]; // *(data + index)
//	}
//
//	const T *begin() const {
//		return data;
//	}
//
//	const T *end() const {
//		return end_;
//	}
//
//	T *begin() {
//		return data;
//	}
//
//	T *end() {
//		return end_;
//	}
