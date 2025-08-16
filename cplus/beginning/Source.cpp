#include <stdexcept>
#include <iostream>
#include <thread>
#include <limits>
#include <sstream>
using namespace std;


int add(int, int);

void test2();

template<typename T>
struct simple_allocate
{
	using value_type = T;
	
	simple_allocate() {};

	T* allocate(size_t size = 1)
	{
		return reinterpret_cast<T*>(new char[size * sizeof(T)]);
	}

	void deallocate(T* ptr, size_t size = 1)
	{
		delete[] reinterpret_cast<char*>(ptr);
	}
};

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
T*  begin(Vector<T>& element) {
	return element.size() ? &element[0] : nullptr;
};
template<typename T>
T* end(Vector<T>& element) {
	return begin(element) + element.size();
};

typedef Vector<int>intArray;
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

struct S
{
	enum a {CHAR,INT,DOUBLE} tag;
	union
	{
		char c;
		int i = 0;
		double d;
	};

	S check() {
		return *this;
	}

	void action()
	{
		cout << c << std::endl << i << std::endl << d;
	}
};


void print_s(const S& s) 
{
	switch (s.tag) 
	{
	case S::CHAR: cout << s.c; 
		break;
	case S::INT: cout << s.i; 
		break;
	case S::DOUBLE: cout << s.d;
		break;
	}
	cout << endl;
}



int main() {

	Vector<int> a(5);

	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	a[3] = 4;
	test2();

	S s = { S::CHAR, {'c'} };
	print_s(s);
	s.tag = S::INT;
	s.i = 100;
	print_s(s);
	s.tag = S::DOUBLE;
	s.d = 0.5;
	print_s(s);

	simple_allocate<S> sa;
	S* newS = sa.allocate();
	newS->c = 'C';
	newS->d = 22.1;
	newS->i = 12;
	sa.deallocate(newS);

	std::wstringstream wos;

	wos << L"float, " << std::numeric_limits<float>::max()
		<< L"Int, " << static_cast<float>(std::numeric_limits<int>::max());

}
