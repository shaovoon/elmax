#include "UTF8ReaderA.h"
//#include "../Utils/StrUtilA.h"
#include <vector>

using namespace Elmax;

#define VECTOR_RESERVE 50000

UTF8ReaderA::UTF8ReaderA(void)
{
}

UTF8ReaderA::UTF8ReaderA(const std::string& file)
{
	Open(file);
}

UTF8ReaderA::~UTF8ReaderA(void)
{
	Close();
}

bool UTF8ReaderA::IsValid(const std::string& file)
{
	FILE* f = FileOpen(file, "rb");

	if(f==NULL)
		return false;

	unsigned char tt[3] = {0,0,0};

	fseek( f, 0, SEEK_SET );

	fread( tt, 1, 3, f );

	if( tt[0] != 0xEF || tt[1] != 0xBB || tt[2] != 0xBF )
	{
		fclose( f );

		return false; // not a unicode file
	}

	fclose( f );

	return true;
}

void UTF8ReaderA::ReadBOM()
{
	if(fp==NULL)
		return;

	unsigned char tt[3] = {0,0,0};

	fseek( fp, 0, SEEK_SET );

	fread( tt, 1, 3, fp );

	if( tt[0] != 0xEF || tt[1] != 0xBB || tt[2] != 0xBF ) // not the correct BOM, so reset the pos to beginning (file might not have BOM)
	{
		fseek( fp, 0, SEEK_SET );
		hasBOM = false;
	}
	else
		hasBOM = true;
}

bool UTF8ReaderA::Open(const std::string& file)
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

	if(fp!=NULL)
	{
		ReadBOM();
	}

	return fp != NULL;
}

bool UTF8ReaderA::Read( std::string& text, size_t len )
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

bool UTF8ReaderA::ReadAll( std::string& text )
{
	size_t size = GetFileSize(filename);

	if(hasBOM)
		size -= 3;

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

bool UTF8ReaderA::ReadLine( std::string& text )
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

bool UTF8ReaderA::IsEOF()
{
	if(fp!=NULL)
	{
		return feof(fp) != 0; // not eof yet
	}

	return true;
}
