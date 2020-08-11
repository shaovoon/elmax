// Elmax.h
// written by Wong Shao Voon and PJ Arends
//
// Simply include this file in your stdafx.h file
// Make sure ElmaxD.lib and Elmax.lib are in your VC/lib folder

#pragma once
#if _MSC_VER == 1400
#	ifdef _DEBUG
#		pragma comment(lib, "../Debug/PortableElmax_VS2005D.lib")
#		pragma comment(lib, "../Debug/FileIO_VS2005D.lib")
#	else 
#		pragma comment(lib, "../Release/PortableElmax_VS2005.lib")
#		pragma comment(lib, "../Release/FileIO_VS2005.lib")
#	endif
#elif _MSC_VER == 1500
#	ifdef _DEBUG
#		pragma comment(lib, "../Debug/PortableElmax_VS2008D.lib")
#		pragma comment(lib, "../Debug/FileIO_VS2008D.lib")
#	else 
#		pragma comment(lib, "../Release/PortableElmax_VS2008.lib")
#		pragma comment(lib, "../Release/FileIO_VS2008.lib")
#	endif
#elif _MSC_VER == 1600
#	ifdef _DEBUG
#		pragma comment(lib, "../Debug/PortableElmax_VS2010D.lib")
#		pragma comment(lib, "../Debug/FileIO_VS2010D.lib")
#	else 
#		pragma comment(lib, "../Release/PortableElmax_VS2010.lib")
#		pragma comment(lib, "../Release/FileIO_VS2010.lib")
#	endif
#elif _MSC_VER == 1700
#	ifdef _DEBUG
#		pragma comment(lib, "../Debug/PortableElmaxD.lib")
#		pragma comment(lib, "../Debug/FileIO.lib")
#	else 
#		pragma comment(lib, "../Release/PortableElmax.lib")
#		pragma comment(lib, "../Release/FileIO.lib")
#   endif
#elif _MSC_VER == 1800
#	ifdef _DEBUG
#		pragma comment(lib, "../Debug/PortableElmax_VS2013D.lib")
#		pragma comment(lib, "../Debug/FileIO_VS2013D.lib")
#	else 
#		pragma comment(lib, "../Release/PortableElmax_VS2013.lib")
#		pragma comment(lib, "../Release/FileIO_VS2013.lib")
#	endif
#else
#	ifdef _DEBUG
#		pragma comment(lib, "../Debug/PortableElmaxD.lib")
#		pragma comment(lib, "../Debug/FileIO.lib")
#	else 
#		pragma comment(lib, "../Release/PortableElmax.lib")
#		pragma comment(lib, "../Release/FileIO.lib")
#   endif
#endif

#include "Elmax/CData.h"
#include "Elmax/Comment.h"
#include "Elmax/Element.h"

