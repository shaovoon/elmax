// SequelMax.h
// written by Wong Shao Voon and PJ Arends
//
// Simply include this file in your stdafx.h file
// Make sure SequelMaxD.lib and SequelMax.lib are in your VC/lib folder

#pragma once

#if _MSC_VER == 1600
#   if defined(_WIN64)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../x64/Debug/SequelMax_VS2010D.lib")
#		    pragma comment(lib, "../x64/Debug/FileIO_VS2010D.lib")
#	    else 
#		    pragma comment(lib, "../x64/Release/SequelMax_VS2010.lib")
#		    pragma comment(lib, "../x64/Release/FileIO_VS2010.lib")
#	    endif
#   elif defined(_WIN32)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../Debug/SequelMax_VS2010D.lib")
#		    pragma comment(lib, "../Debug/FileIO_VS2010D.lib")
#	    else 
#		    pragma comment(lib, "../Release/SequelMax_VS2010.lib")
#		    pragma comment(lib, "../Release/FileIO_VS2010.lib")
#	    endif
#	endif
#elif _MSC_VER == 1700
#   if defined(_WIN64)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../x64/Debug/SequelMax_VS2012D.lib")
#		    pragma comment(lib, "../x64/Debug/FileIO.lib")
#	    else 
#		    pragma comment(lib, "../x64/Release/SequelMax_VS2012.lib")
#		    pragma comment(lib, "../x64/Release/FileIO.lib")
#       endif
#   elif defined(_WIN32)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../Debug/SequelMax_VS2012D.lib")
#		    pragma comment(lib, "../Debug/FileIO.lib")
#	    else 
#		    pragma comment(lib, "../Release/SequelMax_VS2012.lib")
#		    pragma comment(lib, "../Release/FileIO.lib")
#       endif
#	endif
#elif _MSC_VER == 1800
#   if defined(_WIN64)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../x64/Debug/SequelMax_VS2013D.lib")
#		    pragma comment(lib, "../x64/Debug/FileIO_VS2013D.lib")
#	    else 
#		    pragma comment(lib, "../x64/Release/SequelMax_VS2013.lib")
#		    pragma comment(lib, "../x64/Release/FileIO_VS2013.lib")
#	    endif
#   elif defined(_WIN32)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../Debug/SequelMax_VS2013D.lib")
#		    pragma comment(lib, "../Debug/FileIO_VS2013D.lib")
#	    else 
#		    pragma comment(lib, "../Release/SequelMax_VS2013.lib")
#		    pragma comment(lib, "../Release/FileIO_VS2013.lib")
#	    endif
#	endif
#else
#   if defined(_WIN64)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../x64/Debug/SequelMaxD.lib")
#		    pragma comment(lib, "../x64/Debug/FileIO.lib")
#	    else 
#		    pragma comment(lib, "../x64/Release/SequelMax.lib")
#		    pragma comment(lib, "../x64/Release/FileIO.lib")
#	    endif
#   elif defined(_WIN32)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../Debug/SequelMaxD.lib")
#		    pragma comment(lib, "../Debug/FileIOD.lib")
#	    else 
#		    pragma comment(lib, "../Release/SequelMax.lib")
#		    pragma comment(lib, "../Release/FileIO.lib")
#	    endif
#	endif
#endif

#include "Elmax/Element.h"
#include "Elmax/Document.h"
#include "Elmax/XMLWriter.h"

