#include <stdexcept>
#include <iostream>
using namespace std;

class Vector {
public:
	Vector(int size) {
		if (size < 0) throw length_error{ "Vector Constructor size" };
		element = new double[size];
		length = size;
	}
	double& operator[](int i) {
		if (i < 0 || size() <= i) throw out_of_range{ "Vector::operator[]" };
		return element[i]; 
	}
	int size() const{ 
		return length;
	}
private:
	double* element;
	int length;
};

Vector v(10);


int main() {
	for (int i = 0; i < v.size(); i++) {
		v[i] = i+0.5;
	}

	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << "\n";
	}

	return 0;
}