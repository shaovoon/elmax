#include "xTextWriterA.h"
//#include "../Utils/StrUtilRef.h"
#include "UTF8WriterA.h"
#include "AsciiWriterA.h"
#include "../../Common/Enumeration.h"

using namespace Elmax;

xTextWriterA::xTextWriterA(void)
	: pWriter(NULL),
	  BOMWritten(false)
{
}

xTextWriterA::~xTextWriterA(void)
{
	Close();
}

bool xTextWriterA::Open(const std::string& file, FILE_TYPE ft, FILE_OP op)
{
	Close();

	switch(ft)
	{
	case FT_ASCII:
		pWriter = new AsciiWriterA();
		return pWriter->Open(file, op);
	case FT_UTF8:
		pWriter = new UTF8WriterA();
		return pWriter->Open(file, op);
	case FT_UNICODE:
		pWriter = NULL;
		throw std::logic_error("No unicode writer for Non-Unicode project");
	case FT_BEUNICODE:
		pWriter = NULL;
		throw std::logic_error("No be-unicode writer for Non-Unicode project");
	}

	return false;
}

void xTextWriterA::Close()
{
	if(pWriter != NULL)
	{
		pWriter->Close();
		delete pWriter;
		pWriter = NULL;
		BOMWritten = false;
	}

	return;
}

bool xTextWriterA::Write( const std::string& str )
{
	if(pWriter!=NULL)
	{
		return pWriter->Write(str);
	}

	return false;
}

bool xTextWriterA::WriteLine()
{
	if(pWriter!=NULL)
	{
		return pWriter->Write("\n");
	}

	return false;
}

bool xTextWriterA::WriteLine( const std::string& str )
{
	if(pWriter!=NULL)
	{
		return pWriter->WriteLine(str);
	}

	return false;
}

bool xTextWriterA::Write( const char* text )
{
	std::string temp = text;
	return Write(temp);
}

bool xTextWriterA::WriteLine( const char* text )
{
	std::string temp = text;
	return WriteLine(temp);
}

void xTextWriterA::Flush()
{
	if(pWriter!=NULL)
		pWriter->Flush();
}

int xTextWriterA::GetLastError(std::string& msg)
{
	if(pWriter!=NULL)
	{
		return pWriter->GetLastError(msg);
	}

	msg = GetErrorMsgA(ELMAX_NULL_POINTER);
	return ELMAX_NULL_POINTER;
}


void xTextWriterA::ClearLastError()
{
	if(pWriter!=NULL)
	{
		pWriter->ClearLastError();
	}
}

bool xTextWriterA::EnableException(bool enable)
{
	bool prev = enableException;

	enableException = enable;

	return prev;
}
