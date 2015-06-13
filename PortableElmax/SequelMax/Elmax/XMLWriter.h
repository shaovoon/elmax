#pragma once
#include <vector>
#include <stack>
#include "../Configuration/Configuration.h"
#include "../../FileIO/ElmaxFile.h"
#include "ostream.h"

namespace SequelMax
{

class XMLWriter
{
public:
	XMLWriter(void);
	~XMLWriter(void);

	bool Open(const TSTR& file, FILE_TYPE ft, FILE_OP op, const TSTR& indentation);
	void Flush();
	void Close();
	void WriteProcessingInstruction(const TSTR& prep);
	void WriteStartElem(const TSTR& elem_name);
	template<typename T>
	void WriteElemText(const T& val)
	{
		if(StackElem.size()==0)
			throw std::runtime_error("No element is opened!");
		if(StackElem.top().StartElementClosed==false)
		{
			Writer.Write(_TS(">"));

			StackElem.top().StartElementClosed = true;
		}

		ostream os;
		os << val;
		Writer.Write(EscapeXML(os.str()));
		StackElem.top().HasText = true;
	}
	template<typename T>
	void WriteElement(const TSTR& elem_name, const T& val)
	{
		if(StackElem.size()>0)
		{
			if(StackElem.top().StartElementClosed==false)
			{
				Writer.Write(_TS(">"));

				StackElem.top().StartElementClosed = true;
			}

			StackElem.top().HasChild = true;
		}
		if(IS_EMPTY(indentation)==false)
			Writer.WriteLine();

		WriteIndentation(0);

		TSTR start = _TS("<");
		start += elem_name;
		start += _TS(">");
		TSTR end = _TS("</");
		end += elem_name;
		end += _TS(">");

		ostream os;
		os << val;

		TSTR elem = start;
		elem += EscapeXML(os.str());
		elem += end;
		Writer.Write(elem);

		
	}
	void WriteComment(const TSTR& text);
	void WriteCData(const TSTR& text);
	void WriteEndElem();
	template<typename T>
	void WriteAttr(const TSTR& name, const T& val)
	{
		if(StackElem.size()==0)
			throw std::runtime_error("No element is opened!");
		if(StackElem.top().StartElementClosed)
			throw std::runtime_error("Start element is closed!");

		TSTR attr = _TS(" ");
		attr += name;
		attr += _TS("=\"");
		ostream os;
		os << val;
		attr += EscapeXML(os.str());
		attr += _TS("\"");
		Writer.Write(attr);
	}
private:
	struct stElem
	{
		stElem() : Name(_TS("")), StartElementClosed(false), HasChild(false), HasText(false) {}
		TSTR Name;
		bool StartElementClosed;
		bool HasChild;
		bool HasText;
	};

	void WriteIndentation(size_t minus);
	static void PrintStack(const std::string& error, std::stack<stElem>& StackElem);
	static TSTR Replace(const TSTR& fmtstr, const TSTR& anchor, const TSTR& replace);
	static TSTR EscapeXML(const TSTR& fmtstr);

	TSTR indentation;
	std::stack<stElem> StackElem;
	TEXT_WRITER Writer;
};

}