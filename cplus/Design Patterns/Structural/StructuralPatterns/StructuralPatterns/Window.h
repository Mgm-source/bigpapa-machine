#pragma once
#include "View.h"
#include "WindowImp.h"

class Window {
	WindowImp* _imp;
	View* _contents;
public:
	Window(View* view);

	virtual void DrawContents();

	virtual void Open();
	virtual void Close();
	virtual void Iconifiy();
	virtual void Deiconify();

	// forward request to implementation

	virtual void setOrigin();
	virtual void setExtent();
	virtual void Raise();
	virtual void Lower();

	virtual void drawLine();
	virtual void drawRect();
	virtual void drawPoly();
	virtual void drawText();
protected:
	WindowImp* getWindowImp();
	View* getView();
};

