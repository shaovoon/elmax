// Elmax.h
// written by Wong Shao Voon and PJ Arends
//
// Simply include this file in your stdafx.h file
// Make sure ElmaxD.lib and Elmax.lib are in your VC/lib folder

#pragma once
#if _MSC_VER == 1400
#   if defined(_WIN64)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../x64/Debug/PortableElmax_VS2005D.lib")
#		    pragma comment(lib, "../x64/Debug/FileIO_VS2005D.lib")
#	    else 
#		    pragma comment(lib, "../x64/Release/PortableElmax_VS2005.lib")
#		    pragma comment(lib, "../x64/Release/FileIO_VS2005.lib")
#       endif
#   elif defined(_WIN32)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../Debug/PortableElmax_VS2005D.lib")
#		    pragma comment(lib, "../Debug/FileIO_VS2005D.lib")
#	    else 
#		    pragma comment(lib, "../Release/PortableElmax_VS2005.lib")
#		    pragma comment(lib, "../Release/FileIO_VS2005.lib")
#       endif
#	endif
#elif _MSC_VER == 1500
#   if defined(_WIN64)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../x64/Debug/PortableElmax_VS2008D.lib")
#		    pragma comment(lib, "../x64/Debug/FileIO_VS2008D.lib")
#	    else 
#		    pragma comment(lib, "../x64/Release/PortableElmax_VS2008.lib")
#		    pragma comment(lib, "../x64/Release/FileIO_VS2008.lib")
#       endif
#   elif defined(_WIN32)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../Debug/PortableElmax_VS2008D.lib")
#		    pragma comment(lib, "../Debug/FileIO_VS2008D.lib")
#	    else 
#		    pragma comment(lib, "../Release/PortableElmax_VS2008.lib")
#		    pragma comment(lib, "../Release/FileIO_VS2008.lib")
#       endif
#	endif
#elif _MSC_VER == 1600
#   if defined(_WIN64)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../x64/Debug/PortableElmax_VS2010D.lib")
#		    pragma comment(lib, "../x64/Debug/FileIO_VS2010D.lib")
#	    else 
#		    pragma comment(lib, "../x64/Release/PortableElmax_VS2010.lib")
#		    pragma comment(lib, "../x64/Release/FileIO_VS2010.lib")
#       endif
#   elif defined(_WIN32)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../Debug/PortableElmax_VS2010D.lib")
#		    pragma comment(lib, "../Debug/FileIO_VS2010D.lib")
#	    else 
#		    pragma comment(lib, "../Release/PortableElmax_VS2010.lib")
#		    pragma comment(lib, "../Release/FileIO_VS2010.lib")
#       endif
#	endif
#elif _MSC_VER == 1700
#   if defined(_WIN64)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../x64/Debug/PortableElmaxD.lib")
#		    pragma comment(lib, "../x64/Debug/FileIO.lib")
#	    else 
#		    pragma comment(lib, "../x64/Release/PortableElmax.lib")
#		    pragma comment(lib, "../x64/Release/FileIO.lib")
#       endif
#   elif defined(_WIN32)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../Debug/PortableElmaxD.lib")
#		    pragma comment(lib, "../Debug/FileIO.lib")
#	    else 
#		    pragma comment(lib, "../Release/PortableElmax.lib")
#		    pragma comment(lib, "../Release/FileIO.lib")
#       endif
#   endif
#elif _MSC_VER == 1800
#   if defined(_WIN64)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../x64/Debug/PortableElmax_VS2013D.lib")
#		    pragma comment(lib, "../x64/Debug/FileIO_VS2013D.lib")
#	    else 
#		    pragma comment(lib, "../x64/Release/PortableElmax_VS2013.lib")
#		    pragma comment(lib, "../x64/Release/FileIO_VS2013.lib")
#	    endif
#   elif defined(_WIN32)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../Debug/PortableElmax_VS2013D.lib")
#		    pragma comment(lib, "../Debug/FileIO_VS2013D.lib")
#	    else 
#		    pragma comment(lib, "../Release/PortableElmax_VS2013.lib")
#		    pragma comment(lib, "../Release/FileIO_VS2013.lib")
#	    endif
#    endif
#else
#   if defined(_WIN64)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../x64/Debug/PortableElmaxD.lib")
#		    pragma comment(lib, "../x64/Debug/FileIO.lib")
#	    else 
#		    pragma comment(lib, "../x64/Release/PortableElmax.lib")
#		    pragma comment(lib, "../x64/Release/FileIO.lib")
#       endif
#   elif defined(_WIN32)
#	    ifdef _DEBUG
#		    pragma comment(lib, "../Debug/PortableElmaxD.lib")
#		    pragma comment(lib, "../Debug/FileIO.lib")
#	    else 
#		    pragma comment(lib, "../Release/PortableElmax.lib")
#		    pragma comment(lib, "../Release/FileIO.lib")
#       endif
#   endif
#endif

#include "Elmax/CData.h"
#include "Elmax/Comment.h"
#include "Elmax/Element.h"

