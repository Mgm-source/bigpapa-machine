#include <stdexcept>
#include <iostream>
#include <thread>
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


void f() {
	cout << "hello";
};
struct F {
	void operator()() { cout << "Munashe!\n"; };
};

void test() {
	thread t1{ f };
	thread t2{ F() };

	t1.join();
	t2.join();
}


int main() {

	int five = 5; 

	int* test = &five;

	//cout << "pointer to memory address:" << test << "\nmemory address value:" << *test;

	int someArray[10] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	int* pointer = someArray;
	int* pointer2 = &someArray[0];

	char c = 255;
	int a = c;
	
	cout << c << a;
	cout <<"\n" << pointer << " " << *pointer2;

	//for (; *pointer != 0; pointer++) {
	//	cout << "\n" << *pointer << pointer;
	//}

	//test();

}

