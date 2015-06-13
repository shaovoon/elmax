#include "AsciiReaderA.h"
//#include "../Utils/StrUtilA.h"
#include <vector>

using namespace Elmax;

#define VECTOR_RESERVE 50000

AsciiReaderA::AsciiReaderA(void)
{
}

AsciiReaderA::AsciiReaderA(const std::string& file)
{
	Open(file);
}

AsciiReaderA::~AsciiReaderA(void)
{
	Close();
}

bool AsciiReaderA::IsValid(const std::string&)
{
	return true;
}

bool AsciiReaderA::Open(const std::string& file)
{
	filename = file;

	fp = FileOpen(file, "rb");

	if(fp == NULL)
	{
		errNum = ELMAX_FILE_NOT_OPENED;
		err = GetErrorMsgA(errNum);
		if(enableException)
			throw std::runtime_error(file+ ": file cannot be opened!");
	}

	return fp != NULL;
}

bool AsciiReaderA::Read( std::string& text, size_t len )
{
	if(fp == NULL)
		return false;

	RAII_Array<char> buf(len+1);

	size_t lenRead = fread(buf.GetPtr(), 1, len, fp);
	if(lenRead!=len)
	{
		errNum = ELMAX_READ_ERROR;
		std::stringstream stm;
		stm << ": Read " << lenRead << " bytes out of " << len << " required!";
		err = GetErrorMsgA(errNum) + stm.str();
		
		if(enableException)
			throw std::runtime_error(err);

		return false;
	}
	text = buf.GetPtr();

#ifdef _MICROSOFT
	if(ContainsNewline(text.c_str(), text.length()))
	{
		char* pszDest = NULL;
		size_t nDest = 0;

		if(FileToContents( text.c_str(), text.length(), pszDest, nDest ))
		{
			text = pszDest;
		}

		if( pszDest )
		{
			delete [] pszDest;
			pszDest = NULL;
		}
	}
#endif

	return true;
}

bool AsciiReaderA::ReadAll( std::string& text )
{
	size_t size = GetFileSize(filename);

	if(size==0)
		return false;

	if(fp == NULL)
		return false;

	RAII_Array<char> buf(size+1);
	size_t lenRead = fread(buf.GetPtr(), 1, size, fp);
	if(lenRead!=size)
	{
		errNum = ELMAX_READ_ERROR;
		std::stringstream stm;
		stm << ": Read " << lenRead << " bytes out of " << size << " required!";
		err = GetErrorMsgA(errNum) + stm.str();

		if(enableException)
			throw std::runtime_error(err);

		return false;
	}

	text = buf.GetPtr();

#ifdef _MICROSOFT
	if(ContainsNewline(text.c_str(), text.length()))
	{
		char* pszDest = NULL;
		size_t nDest = 0;

		if(FileToContents( text.c_str(), text.length(), pszDest, nDest ))
		{
			text = pszDest;
		}

		if( pszDest )
		{
			delete [] pszDest;
			pszDest = NULL;
		}
	}
#endif

	return true;
}

bool AsciiReaderA::ReadLine( std::string& text )
{
	if(fp == NULL)
		return false;

	text = "";
	char ch = '\0';

	while (!feof(fp))
	{
		ch = fgetc(fp);

		if(ch != '\r' && ch != '\n')
			text += ch;

		if(ch == '\n')
			break;
	}

	return true;
}

bool AsciiReaderA::IsEOF()
{
	if(fp!=NULL)
	{
		return feof(fp) != 0; // not eof yet
	}

	return true;
}
