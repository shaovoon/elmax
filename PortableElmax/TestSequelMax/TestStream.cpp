#include "TestStream.h"

SequelMax::ostream operator <<(SequelMax::ostream& os, const MyRect& val)
{
	os << val.m_x;
	os << _TS(",");
	os << val.m_y;
	os << _TS(",");
	os << val.m_width;
	os << _TS(",");
	os << val.m_height;

	return os;
}

SequelMax::istream operator >>(SequelMax::istream& is, MyRect& val)
{
	is >> val.m_x;
	is >> val.m_y;
	is >> val.m_width;
	is >> val.m_height;

	return is;
}
