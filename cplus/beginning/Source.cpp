#include <stdexcept>
#include <iostream>
#include <thread>
#include <limits>
#include <sstream>
#include "boost/signals2.hpp"

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
		if (size < 0) throw std::length_error{ "Vector Constructor size" };
		element = new T[size];
		length = size;
	}

	~Vector() { delete[] element; };

	T& operator[](int i) {
		if (i < 0 || size() <= i) throw std::out_of_range{ "Vector::operator[]" };
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
	std::cout << "hello";
};
struct F {
	void operator()() { std::cout << "Munashe!\n"; };
};

void test() {
	std::thread t1{ f };
	std::thread t2{ F() };

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
};

struct signalTest
{
	void operator()() 
	{
		std::cout << "This is me sending out a signal";
	}
};


void print_s(const S& s) 
{
	switch (s.tag) 
	{
	case S::CHAR: std::cout << s.c; 
		break;
	case S::INT: std::cout << s.i; 
		break;
	case S::DOUBLE: std::cout << s.d;
		break;
	}
	std::cout << std::endl;
}

class Document
{
public:
	typedef boost::signals2::signal<void()>  signal_t;

public:
	Document()
	{}

	/* Connect a slot to the signal which will be emitted whenever
	  text is appended to the document. */
	boost::signals2::connection connect(const signal_t::slot_type& subscriber)
	{
		return m_sig.connect(subscriber);
	}

	void append(const char* s)
	{
		m_text += s;
		m_sig();
	}

	const std::string& getText() const
	{
		return m_text;
	}

private:
	signal_t    m_sig;
	std::string m_text;
};


class TextView
{
public:
	TextView(Document& doc) : m_document(doc)
	{
		m_connection = m_document.connect(boost::bind(&TextView::refresh, this));
	}

	~TextView()
	{
		m_connection.disconnect();
	}

	void refresh() const
	{
		std::cout << "TextView: " << m_document.getText() << std::endl;
	}
private:
	Document& m_document;
	boost::signals2::connection  m_connection;
};

class HexView
{
public:
	HexView(Document& doc) : m_document(doc)
	{
		m_connection = m_document.connect(boost::bind(&HexView::refresh,this));
	}

	~HexView()
	{
		m_connection.disconnect();
	}

	void refresh() const
	{
		const std::string& s = m_document.getText();

		std::cout << "HexView:";

		for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
			std::cout << ' ' << std::hex << static_cast<int>(*it);

		std::cout << std::endl;
	}
private:
	Document& m_document;
	boost::signals2::connection  m_connection;
};

int main() {
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

	Document    doc;
	TextView    v1(doc);
	HexView     v2(doc);

	doc.append("Hello world!");
}
