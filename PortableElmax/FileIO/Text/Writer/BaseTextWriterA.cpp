#include "BaseTextWriterA.h"
#include <vector>

using namespace Elmax;

#define VECTOR_RESERVE 50000

BaseTextWriterA::BaseTextWriterA(void)
	: fp(NULL)
	, err("")
	, errNum(0)
	, enableException(true)
{
}

BaseTextWriterA::~BaseTextWriterA(void)
{
	Close();
}

void BaseTextWriterA::Close()
{
	if(fp!=NULL)
	{
		fflush(fp);
		fclose(fp);
		fp = NULL;
	}
}

void BaseTextWriterA::Flush()
{
	if(fp!=NULL)
		fflush(fp);
}

bool BaseTextWriterA::ContentsToFile( 
	const char* pszSource, 
	size_t nSource, 
	char*& pszDest,
	size_t& nDest	)
{
	if( !pszSource )
		return false;

	std::vector<char> vwc;

	if( 0 == nSource )
	{
		vwc.reserve( VECTOR_RESERVE );
		const char* pszSource2 = pszSource;

		while( pszSource2 )
		{
			if( '\n' == *pszSource2 )
			{
				vwc.push_back( '\r' );
				vwc.push_back( '\n' );
			}
			else
				vwc.push_back( *pszSource2 );

			pszSource2++;
		}
	}
	else
	{
		vwc.reserve( nSource + 100 );

		for( size_t i=0; i<nSource; ++i )
		{
			if( '\n' == pszSource[i] )
			{
				vwc.push_back( '\r' );
				vwc.push_back( '\n' );
			}
			else
				vwc.push_back( pszSource[i] );
		}
	}

	pszDest = new char[vwc.size()+1];
	memset(pszDest, 0, sizeof(char)*(vwc.size()+1));

	if( !pszDest )
		return false;

	nDest = vwc.size();
	for( size_t i=0; i<nDest; ++i )
	{
		pszDest[i] = vwc[i];
	}

	return true;
}

bool BaseTextWriterA::ContainsNewline(const char* text, size_t len)
{
	for(size_t i=0; i<len; ++i)
	{
		if(text[i]=='\n')
		{
			if(i!=0)
			{
				if(text[i-1]!='\r') // not \r\n
					return true; // true is single \n
			}
		}
	}

	return false;
}

int BaseTextWriterA::GetLastError(std::string& msg)
{
	msg = err;
	return errNum;
}


void BaseTextWriterA::ClearLastError()
{
	err = "";
	errNum = 0;
}

bool BaseTextWriterA::EnableException(bool enable)
{
	bool prev = enableException;

	enableException = enable;

	return prev;
}
