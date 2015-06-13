#include "XMLWriter.h"
#include "../Utils/StrConv.h"

using namespace SequelMax;

XMLWriter::XMLWriter(void)
{
}


XMLWriter::~XMLWriter(void)
{
	Writer.Close();
}

bool XMLWriter::Open(const TSTR& file, FILE_TYPE ft, FILE_OP op, const TSTR& indentation)
{
	this->indentation = indentation;
#if defined ELMAX_USE_MFC_CSTRING || ELMAX_USE_CUSTOM_STRING
	bool res = Writer.Open(GET_CONST_PTR(file), ft, op);
#else
	bool res = Writer.Open(file, ft, op);
#endif
	return res;
}

void XMLWriter::Flush()
{
	Writer.Flush();
}

void XMLWriter::Close()
{
	if(StackElem.size()>0)
		PrintStack("Some elements not closed yet", StackElem);

	Writer.Close();
}

void XMLWriter::WriteProcessingInstruction(const TSTR& prep)
{
	Writer.Write(prep);
}

void XMLWriter::WriteStartElem(const TSTR& elem_name)
{
	if(StackElem.size()>0)
	{
		if(StackElem.top().StartElementClosed==false)
		{
			Writer.Write(_TS(">"));

			StackElem.top().StartElementClosed = true;
		}
		if(IS_EMPTY(indentation)==false)
			Writer.WriteLine();
		WriteIndentation(0);
		TSTR start = _TS("<");
		start += elem_name;
		Writer.Write(start);
		StackElem.top().HasChild = true;

		stElem st;
		st.Name = elem_name;
		StackElem.push(st);
	}
	else
	{
		if(IS_EMPTY(indentation)==false)
			Writer.WriteLine();
		TSTR start = _TS("<");
		start += elem_name;
		Writer.Write(start);

		stElem st;
		st.Name = elem_name;
		StackElem.push(st);
	}
}

void XMLWriter::WriteComment(const TSTR& text)
{
	if(StackElem.size()>0)
	{
		if(StackElem.top().StartElementClosed==false)
		{
			Writer.Write(_TS(">"));

			StackElem.top().StartElementClosed = true;
		}
		if(IS_EMPTY(indentation)==false)
			Writer.WriteLine();
		WriteIndentation(0);
		TSTR comment = _TS("<!--");
		comment += text;
		comment += _TS("-->");
		Writer.Write(comment);

		StackElem.top().HasChild = true;
	}
	else
	{
		if(IS_EMPTY(indentation)==false)
			Writer.WriteLine();
		TSTR comment = _TS("<!--");
		comment += text;
		comment += _TS("-->");
		Writer.Write(comment);
	}
}

void XMLWriter::WriteCData(const TSTR& text)
{
	if(StackElem.size()>0)
	{
		if(StackElem.top().StartElementClosed==false)
		{
			Writer.Write(_TS(">"));

			StackElem.top().StartElementClosed = true;
		}
		WriteIndentation(0);
		TSTR comment = _TS("<![CDATA[");
		comment += text;
		comment += _TS("]]>");
		if(IS_EMPTY(indentation))
			Writer.Write(comment);
		else
			Writer.WriteLine(comment);

		StackElem.top().HasChild = true;
	}
	else
	{
		TSTR comment = _TS("<![CDATA[");
		comment += text;
		comment += _TS("]]>");
		if(IS_EMPTY(indentation))
			Writer.Write(comment);
		else
			Writer.WriteLine(comment);
	}
}

void XMLWriter::WriteEndElem()
{
	if(StackElem.size()==0)
		throw std::runtime_error("No element is opened");

	if(StackElem.top().HasChild)
	{
		if(IS_EMPTY(indentation)==false)
			Writer.WriteLine();

		WriteIndentation(1);

		TSTR end = _TS("</");
		end += StackElem.top().Name;
		end += _TS(">");
		Writer.Write(end);
	}
	else if(StackElem.top().HasText)
	{
		TSTR end = _TS("</");
		end += StackElem.top().Name;
		end += _TS(">");
		Writer.Write(end);
	}
	else // no children
	{
		TSTR end = _TS("/>");
		Writer.Write(end);
	}

	StackElem.pop();
}

void XMLWriter::WriteIndentation(size_t minus)
{
	if(IS_EMPTY(indentation))
		return;

	if(StackElem.size()==0)
		return;

	TSTR indent = _TS("");
	for(size_t i=0; i<StackElem.size()-minus; ++i)
		indent += this->indentation;

	Writer.Write(indent);
}

void XMLWriter::PrintStack(const std::string& error, std::stack<XMLWriter::stElem>& StackElem)
{
	// print all the stack names
	std::vector<TSTR> vecTemp;
	while(StackElem.size()>0)
	{
		TSTR name = StackElem.top().Name;
		vecTemp.push_back(name);
		StackElem.pop();
	}
	std::vector<TSTR>::const_reverse_iterator it = vecTemp.rbegin();
	std::string err=error+":";

#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	for(;it!=vecTemp.rend();++it)
		err += "<" + StrConv::ConvToAString(*it) +  ">";
#else
	for(;it!=vecTemp.rend();++it)
	{
		err += "<";
		err += GET_CONST_PTR(*it);
		err += ">";
	}
#endif
#else
#ifdef ELMAX_USE_UNICODE
	for(;it!=vecTemp.rend();++it)
		err += "<" + StrConv::ConvToAString(*it) +  ">";
#else
	for(;it!=vecTemp.rend();++it)
		err += "<" + *it +  ">";
#endif
#endif
	throw std::runtime_error(err);

}

TSTR XMLWriter::Replace( 
	const TSTR& fmtstr, 
	const TSTR& anchor,
	const TSTR& replace )
{
	TSTR fmtstrReturn = fmtstr;

#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	int pos = 0;
	while( -1 != pos )
	{
		pos = fmtstrReturn.Find( anchor, pos );

		if( -1 != pos )
		{
			fmtstrReturn.Replace(anchor, replace);

			pos += GET_SIZE(replace);
		}
	}
#else
	size_t pos = 0;
	while( STDSTR::npos != pos )
	{
		pos = fmtstrReturn.find( anchor, pos );

		if( STDSTR::npos != pos )
		{
			fmtstrReturn.erase( pos, GET_SIZE(anchor) );
			fmtstrReturn.insert( pos, replace );
			pos += GET_SIZE(replace);
		}
	}
#endif
	return fmtstrReturn;
}

TSTR XMLWriter::EscapeXML( 
	const TSTR& fmtstr)
{
	TSTR fmtstr1 = Replace(fmtstr, _TS("&"), _TS("&amp;"));
	fmtstr1 = Replace(fmtstr1, _TS("\""), _TS("&quot;"));
	fmtstr1 = Replace(fmtstr1, _TS("\'"), _TS("&apos;"));
	fmtstr1 = Replace(fmtstr1, _TS("<"), _TS("&lt;"));
	fmtstr1 = Replace(fmtstr1, _TS(">"), _TS("&gt;"));

	return fmtstr1;
}
