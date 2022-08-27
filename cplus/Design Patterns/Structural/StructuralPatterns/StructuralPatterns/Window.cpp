#include "Window.h"

Window::Window(View* view) : _contents {view}, _imp {nullptr}
{
}

void Window::DrawContents()
{
}

void Window::Open()
{
}

void Window::Close()
{
}

void Window::Iconifiy()
{
}

void Window::Deiconify()
{
}

void Window::setOrigin()
{
}

void Window::setExtent()
{
}

void Window::Raise()
{
}

void Window::Lower()
{
}

void Window::drawLine()
{
}

void Window::drawRect()
{
}

void Window::drawPoly()
{
}

void Window::drawText()
{
}

WindowImp* Window::getWindowImp()
{
	return nullptr;
}

View* Window::getView()
{
	return nullptr;
}
