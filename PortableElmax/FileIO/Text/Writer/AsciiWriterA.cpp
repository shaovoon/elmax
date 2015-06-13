#include "AsciiWriterA.h"
#include "../Utils/StrUtil.h"

using namespace Elmax;

AsciiWriterA::AsciiWriterA(void)
{
}

AsciiWriterA::AsciiWriterA(const std::string& file, FILE_OP op)
{
	Open(file, op);
}

AsciiWriterA::~AsciiWriterA(void)
{
	Close();
}

bool AsciiWriterA::Open(const std::string& file, FILE_OP op)
{
	if(op == APPEND)
	{
		fp = FileOpen(file, "ab");
	}
	else
	{
		fp = FileOpen(file, "wb");
	}

	if(fp == NULL)
	{
		errNum = ELMAX_FILE_NOT_OPENED;
		err = GetErrorMsgA(errNum);
		if(enableException)
			throw std::runtime_error(file+ ": file cannot be opened!");
	}

	return fp != NULL;
}

bool AsciiWriterA::Write( const std::string& text )
{
	bool ret = Write( text.c_str(), text.length() );
	if(ret==false)
	{
		errNum = ELMAX_WRITE_ERROR;
		err = GetErrorMsgA(errNum);
		if(enableException)
			throw std::runtime_error("Write error");
	}
	return ret;
}

bool AsciiWriterA::WriteLine( const std::string& text )
{
	bool ret = WriteLine( text.c_str(), text.length() );
	if(ret==false)
	{
		errNum = ELMAX_WRITE_ERROR;
		err = GetErrorMsgA(errNum);
		if(enableException)
			throw std::runtime_error("Write error");
	}
	return ret;
}

bool AsciiWriterA::Write( const char* text )
{
	bool ret = Write( text, strlen(text) );
	if(ret==false)
	{
		errNum = ELMAX_WRITE_ERROR;
		err = GetErrorMsgA(errNum);
		if(enableException)
			throw std::runtime_error("Write error");
	}
	return ret;
}

bool AsciiWriterA::WriteLine( const char* text )
{
	bool ret = WriteLine( text, strlen(text) );
	if(ret==false)
	{
		errNum = ELMAX_WRITE_ERROR;
		err = GetErrorMsgA(errNum);
		if(enableException)
			throw std::runtime_error("Write error");
	}
	return ret;
}

bool AsciiWriterA::Write( const char* text, size_t nBufLen )
{
	if( !fp )
		return false;

	if( nBufLen == 0 )
		return true;

#ifdef _MICROSOFT

	if(ContainsNewline(text, nBufLen))
	{
		char* pszDest = NULL;
		size_t nDest = 0;

		bool bRet = ContentsToFile( text, nBufLen, pszDest, nDest );
		RAII_Array<char> dest = pszDest;

		if( !bRet )
			return false;

		if( pszDest )
		{
			fwrite( pszDest, 1, strlen(pszDest), fp );
		}
	}
	else
	{
		fwrite( text, 1, strlen(text), fp );
	}

#else
	if( text )
	{
		fwrite( text, 1, strlen(text), fp );
	}
#endif

	return true;
}


bool AsciiWriterA::WriteLine( const char* text, size_t nBufLen )
{
	if( !fp )
		return false;

	if( nBufLen == 0 )
		return true;

#ifdef _MICROSOFT

	if(ContainsNewline(text, nBufLen))
	{
		char* pszDest = NULL;
		size_t nDest = 0;

		bool bRet = ContentsToFile( text, nBufLen, pszDest, nDest );
		RAII_Array<char> dest = pszDest;

		if( !bRet )
			return false;

		if( pszDest )
		{
			fwrite( pszDest, 1, strlen(pszDest), fp );
			char newline[] = "\r\n";
			fwrite( newline, 1, strlen(newline), fp );
		}
	}
	else
	{
		fwrite( text, 1, strlen(text), fp );
		char newline[] = "\r\n";
		fwrite( newline, 1, strlen(newline), fp );
	}

#else
	if( text )
	{
		fwrite( text, 1, strlen(text), fp );
		char newline[] = "\n";
		fwrite( newline, 1, strlen(newline), fp );
	}
#endif

	return true;
}

