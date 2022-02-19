#include <stdexcept>
#include <iostream>
using namespace std;

template<typename T>
class Vector {
public:
	Vector(int size) {
		if (size < 0) throw length_error{ "Vector Constructor size" };
		element = new T[size];
		length = size;
	}

	~Vector() { delete[] element; };

	T& operator[](int i) {
		if (i < 0 || size() <= i) throw out_of_range{ "Vector::operator[]" };
		return element[i]; 
	}
	int size() const{ 
		return length;
	}
private:
	T* element;
	int length;
};

template<typename T>
T* begin(Vector<T>& element) {
	return element.size() ? &element[0] : nullptr;
};
template<typename T>
T* end(Vector<T>& element) {
	return begin(element) + element.size();
};

Vector<int> v(10);

int main() {
	for (int i = 0; i < v.size(); i++) {
		v[i] = i;
	}

	for (auto element : v) {
		cout << element << "\n";
	}

	return 0;
}