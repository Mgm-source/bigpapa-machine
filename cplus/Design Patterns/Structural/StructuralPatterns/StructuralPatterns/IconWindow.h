#pragma once
#include "Window.h"
class IconWindow : public Window {
	const wchar_t* _bitMapName;
public:
	virtual void DrawContents();
};

