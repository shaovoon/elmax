#pragma once
#include "../SequelMax/Elmax/istream.h"
#include "../SequelMax/Elmax/ostream.h"


struct MyRect
{
	MyRect() : m_x(0), m_y(0), m_width(0), m_height(0) {}
	MyRect(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height) {}
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

SequelMax::ostream operator <<(SequelMax::ostream& os, const MyRect& val);
SequelMax::istream operator >>(SequelMax::istream& is, MyRect& val);
