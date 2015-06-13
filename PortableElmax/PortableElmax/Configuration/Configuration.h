#pragma once

#include "../config.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#ifdef ELMAX_USE_UNICODE
	typedef wchar_t _ELCHAR;
	#define _TS(x)	L ## x
	#ifdef ELMAX_USE_MFC_CSTRING
		#include <atlstr.h>
		typedef CStringW TSTR;
		#include <string>
		typedef std::wstring STDSTR;
	#else
		#include <string>
		typedef std::wstring TSTR;
		typedef std::wstring STDSTR;
	#endif
	#include <strstream>
	typedef std::wstringstream STRINGSTREAM;
	#define _ITOT_S _itow_s
	#define _I64TOT_S  _i64tow_s
	#define _ULTOT_S _ultow_s
	#define _UI64TOT_S _ui64tow_s
	#define _TTOI _wtoi
	#define _TTOI64  _wtoi64
	#define TCSTOUL wcstoul
	#define _TTOF _wtof
	#define TOLOWER towlower
	#define _TCSTOI64 _wcstoi64

	#include "../../FileIO/Common/Common.h"
	#define STRCPY Wcscpy
	#define STRTOK_S wcstok_s
	#define STRTOK wcstok
	#define STRTOK_R wcstok
	
	#include "../../FileIO/Text/Reader/xTextReader.h"
	#include "../../FileIO/Text/Writer/xTextWriter.h"
	typedef Elmax::xTextReader TEXT_READER;
	typedef Elmax::xTextWriter TEXT_WRITER;

#else
	typedef char _ELCHAR;
	#define _TS(x)	x
	#ifdef ELMAX_USE_MFC_CSTRING
		#include <atlstr.h>
		typedef CStringA TSTR;
		#include <string>
		typedef std::string STDSTR;
	#else
		#include <string>
		typedef std::string TSTR;
		typedef std::string STDSTR;
	#endif
	#include <strstream>
	typedef std::stringstream STRINGSTREAM;

	#define _ITOT_S _itoa_s
	#define _I64TOT_S  _i64toa_s
	#define _ULTOT_S _ultoa_s
	#define _UI64TOT_S _ui64toa_s
	#define _TTOI atoi
	#define _TTOI64 _atoi64
	#define TCSTOUL strtoul
	#define _TTOF atof
	#define TOLOWER tolower
	#define _TCSTOI64 _strtoi64

	#include "../../FileIO/Common/Common.h"
	#define STRCPY Strcpy
	#define STRTOK_S strtok_s
	#define STRTOK strtok
	#define STRTOK_R strtok_r

	#include "../../FileIO/Text/Reader/xTextReaderA.h"
	#include "../../FileIO/Text/Writer/xTextWriterA.h"
	typedef Elmax::xTextReaderA TEXT_READER;
	typedef Elmax::xTextWriterA TEXT_WRITER;

#endif

#ifdef ELMAX_USE_MFC_CSTRING
	#define GET_SIZE(x) (size_t)( ## x ## .GetLength())
	#ifdef ELMAX_USE_UNICODE
		#define GET_CONST_PTR(x) (LPCWSTR) ## x
	#else
		#define GET_CONST_PTR(x) (LPCSTR) ## x
	#endif
	#define IS_EMPTY(x) x ## .IsEmpty()
#else
	#ifdef _MICROSOFT
		#define GET_SIZE(x) x##.size()
		#define GET_CONST_PTR(x) x##.c_str()
		#define IS_EMPTY(x) x##.empty()
	#else
		#define GET_SIZE(x) x.size()
		#define GET_CONST_PTR(x) x.c_str()
		#define IS_EMPTY(x) x.empty()
	#endif
#endif

#define NODE_COLLECTION std::vector<RawTreeNode*>

#if defined ELMAX_USE_MAP_FOR_ATTRS
	#define ATTR_MAP DictMap
	#define ATTR_MAP_COLLECTION std::map<TSTR, TSTR>
#elif defined ELMAX_USE_UNORDERED_MAP_FOR_ATTRS
	#define ATTR_MAP HashMap
	#define ATTR_MAP_COLLECTION std::unordered_map<TSTR, TSTR>
#elif defined ELMAX_USE_LIST_FOR_ATTRS
	#define ATTR_MAP SListMap
	#define ATTR_MAP_COLLECTION std::list<std::pair<TSTR, TSTR> >
#else
	#define ATTR_MAP VectorMap
	#define ATTR_MAP_COLLECTION std::vector<std::pair<TSTR, TSTR> >
#endif




