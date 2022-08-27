#pragma once
class WindowImp {

public:
	virtual void impTop() = 0;
	virtual void impBottom() = 0;
	virtual void impSetExtent() = 0;
	virtual void impSetOrigin() = 0;

	virtual void deviceRect() = 0;
	virtual void deviceText() = 0;
	virtual void deviceBitMap() = 0;
protected:
	WindowImp();
};

