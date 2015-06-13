#include "BaseTextReaderA.h"
#include <vector>
#include <sys/stat.h>
#include "../../Common/RAII_Array.h"

using namespace Elmax;

#define VECTOR_RESERVE 50000

BaseTextReaderA::BaseTextReaderA(void)
	: fp(NULL)
	, err("")
	, errNum(0)
	, enableException(true)
	, hasBOM(false)
{
}

BaseTextReaderA::~BaseTextReaderA(void)
{
	Close();
}

void BaseTextReaderA::Close()
{
	if(fp!=NULL)
	{
		fclose(fp);
		fp = NULL;
	}
}

bool BaseTextReaderA::FileToContents( 
	const char* pszSource, 
	size_t nSource, 
	char*& pszDest,
	size_t& nDest	)
{
	if( !pszSource )
		return false;

	std::vector<char> vwc;
	vwc.reserve( VECTOR_RESERVE );

	if( 0 == nSource )
	{
		const char* pszSource2 = pszSource;

		while( pszSource2 )
		{
			if( '\r' == *pszSource2 && '\n' == *(pszSource2+1) )
			{
				vwc.push_back( '\n' );
				pszSource2++;
			}
			else
				vwc.push_back( *pszSource2 );

			pszSource2++;
		}
	}
	else
	{
		for( size_t i=0; i<nSource; ++i )
		{
			if( i+1 < nSource && '\r' == pszSource[i] && '\n' == pszSource[i+1] )
			{
				vwc.push_back( '\n' );
				++i;
			}
			else
				vwc.push_back( pszSource[i] );
		}
	}

	if( !vwc.empty() )
		vwc.push_back( '\0' );
	else
		return false;

	pszDest = new char[vwc.size()];
	RAII_Array<char> raii = pszDest;
	
	if( !pszDest )
		return false;

	nDest = vwc.size();
	for( size_t i=0; i<nDest; ++i )
	{
		pszDest[i] = vwc[i];
	}

	raii.Detach();

	return true;
}

#ifdef _MICROSOFT
size_t BaseTextReaderA::GetFileSize(const std::string& file)
{
	struct stat st;
	stat(file.c_str(), &st);
	return st.st_size;
}
#else
size_t BaseTextReaderA::GetFileSize(const std::string& file)
{
	struct stat st;
	stat(file.c_str(), &st);
	return st.st_size;
}
#endif

bool BaseTextReaderA::ContainsNewline(const char* text, size_t len)
{
	for(size_t i=0; i<len; ++i)
	{
#ifdef _MICROSOFT
		if(text[i]=='\n')
		{
			if(i!=0)
			{
				if(text[i-1]=='\r') // is \r\n
					return true; // true if \r\n
			}
		}
#else
		if(text[i]=='\n')
		{
			return true; // true if \r\n
		}
#endif
	}

	return false;
}

// For Linux use
bool BaseTextReaderA::ContainsReturnCarriage(const char* text, size_t len)
{
	for(size_t i=0; i<len; ++i)
	{
		if(text[i]=='\r')
			return true; // true if \r
	}

	return false;
}

bool BaseTextReaderA::ContainsReturnCarriage(const std::string& text)
{
	for(size_t i=0; i<text.size(); ++i)
	{
		if(text[i] == '\r')
			return true; // true if \r
	}

	return false;
}

std::string BaseTextReaderA::RemoveReturnCarriage(const std::string& text)
{
	std::string dest = "";
	for(size_t i=0; i<text.size(); ++i)
	{
		if(text[i] != '\r')
			dest += text[i];
	}

	return dest;
}

int BaseTextReaderA::GetLastError(std::string& msg)
{
	msg = err;
	return errNum;
}


void BaseTextReaderA::ClearLastError()
{
	err = "";
	errNum = 0;
}

bool BaseTextReaderA::EnableException(bool enable)
{
	bool prev = enableException;

	enableException = enable;

	return prev;
}
