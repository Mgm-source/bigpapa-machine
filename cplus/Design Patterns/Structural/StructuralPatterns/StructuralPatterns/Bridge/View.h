#pragma once
#include "Window.h"

class Window;

class View {
public:
	View() = default;
	void DrawOn(const Window*);

};

