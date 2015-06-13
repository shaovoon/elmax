#include "UTF8WriterA.h"
#include "../Utils/StrUtil.h"

using namespace Elmax;

UTF8WriterA::UTF8WriterA(void)
	: BOMWritten(false)
{
}

UTF8WriterA::UTF8WriterA(const std::string& file, FILE_OP op)
	: BOMWritten(false)
{
	Open(file, op);
}

UTF8WriterA::~UTF8WriterA(void)
{
	Close();
}

bool UTF8WriterA::Open(const std::string& file, FILE_OP op)
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

bool UTF8WriterA::WriteBOM()
{
	if( !fp )
		return false;

	unsigned char bom[3] = { 0xEF, 0xBB, 0xBF };

	size_t len = fwrite( bom, 1, 3, fp );
	if(len!=3)
	{
		errNum = ELMAX_WRITE_ERROR;
		err = GetErrorMsgA(errNum);
		if(enableException)
			throw std::runtime_error("Write error");

		return false;
	}

	return true;
}

bool UTF8WriterA::Write( const std::string& text )
{
	if(BOMWritten == false)
	{
		WriteBOM();
		BOMWritten = true;
	}

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

bool UTF8WriterA::WriteLine( const std::string& text )
{
	if(BOMWritten == false)
	{
		WriteBOM();
		BOMWritten = true;
	}

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

bool UTF8WriterA::Write( const char* text )
{
	if(BOMWritten == false)
	{
		WriteBOM();
		BOMWritten = true;
	}

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

bool UTF8WriterA::WriteLine( const char* text )
{
	if(BOMWritten == false)
	{
		WriteBOM();
		BOMWritten = true;
	}

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

bool UTF8WriterA::Write( const char* text, size_t nBufLen )
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


bool UTF8WriterA::WriteLine( const char* text, size_t nBufLen )
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

