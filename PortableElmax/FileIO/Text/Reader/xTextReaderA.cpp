#include "xTextReaderA.h"
#include "UTF8ReaderA.h"
#include "AsciiReaderA.h"
#include "../../Common/Enumeration.h"

using namespace Elmax;

xTextReaderA::xTextReaderA(void)
	:	pReader(NULL)
{
}

xTextReaderA::~xTextReaderA(void)
{
	Close();
}

bool xTextReaderA::Open(const std::string& file)
{
	Close();
	if(UTF8ReaderA::IsValid(file))
	{
		pReader = new UTF8ReaderA();
		return pReader->Open(file);
	}
	if(AsciiReaderA::IsValid(file))
	{
		pReader = new AsciiReaderA();
		return pReader->Open(file);
	}

	return false;
}

bool xTextReaderA::Open(const std::string& file, FILE_TYPE ftype)
{
	Close();
	if(UTF8ReaderA::IsValid(file))
	{
		pReader = new UTF8ReaderA();
		return pReader->Open(file);
	}
	else
	{
		switch(ftype)
		{
		case FT_UTF8:
			pReader = new UTF8ReaderA();
			return pReader->Open(file);
			break;
		case FT_UNICODE:
			throw std::logic_error("No unicode reader for Non-Unicode project");
			break;
		case FT_BEUNICODE:
			throw std::logic_error("No be-unicode reader for Non-Unicode project");
			break;
		case FT_ASCII:
			pReader = new AsciiReaderA();
			return pReader->Open(file);
			break;
		default:
			pReader = new AsciiReaderA();
			return pReader->Open(file);
			break;
		}
	}

	return false;
}

void xTextReaderA::Close()
{
	if(pReader != NULL)
	{
		pReader->Close();
		delete pReader;
		pReader = NULL;
	}

	return;
}

bool xTextReaderA::IsEOF()
{
	if(pReader!=NULL)
	{
		return pReader->IsEOF();
	}

	return true;
}

size_t xTextReaderA::Read( size_t len, std::string& text )
{
	if(pReader!=NULL)
	{
		bool b = pReader->Read(text, len);
		return b ? 1 : 0;
	}

	return 0;
}

size_t xTextReaderA::ReadLine( std::string& text )
{
	if(pReader!=NULL)
	{
		bool b = pReader->ReadLine(text);
		return b ? 1 : 0;
	}

	return 0;
}

bool xTextReaderA::ReadAll( std::string& text )
{
	if(pReader!=NULL)
	{
		return pReader->ReadAll(text);
	}

	return false;
}

int xTextReaderA::GetLastError(std::string& msg)
{
	if(pReader!=NULL)
	{
		return pReader->GetLastError(msg);
	}

	msg = GetErrorMsgA(ELMAX_NULL_POINTER);
	return ELMAX_NULL_POINTER;
}


void xTextReaderA::ClearLastError()
{
	if(pReader!=NULL)
	{
		pReader->ClearLastError();
	}
}

bool xTextReaderA::EnableException(bool enable)
{
	bool prev = enableException;

	enableException = enable;

	return prev;
}
