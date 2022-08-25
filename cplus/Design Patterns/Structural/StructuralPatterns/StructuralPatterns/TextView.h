#pragma once
class TextView {
public:
	TextView() = default;
	// adaptee class
	void GetOrigin(float& x,float& y) const;
	void GetExtent(float& width,float& height) const;
	virtual bool isEmpty() const;
};

