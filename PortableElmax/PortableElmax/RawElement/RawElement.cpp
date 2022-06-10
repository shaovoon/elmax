#include "RawElement.h"
#include "RawCData.h"
#include "RawComment.h"
#include <vector>
#include <iostream>
#include "../Utils/StrConv.h"

using namespace Elmax;

const size_t RawElement::StartElementEndLength = 2;
const size_t RawElement::EndElementStartLength = 2;
const size_t RawElement::ProcessingInstructionStartLength = 5;
const size_t RawElement::ProcessingInstructionEndLength = 2;
const size_t RawElement::DocTypeStartLength = 9;
const size_t RawElement::DocTypeEndLength = 1;
const size_t RawElement::CDataStartLength = 9;
const size_t RawElement::CDataEndLength = 3;
const size_t RawElement::CommentStartLength = 4;
const size_t RawElement::CommentEndLength = 3;

RawElement::RawElement()
{
	SetXmlType(XML_ELEMENT);
}

RawElement::RawElement(const TSTR& name)
{
	SetXmlType(XML_ELEMENT);
		
	SetName(name);
}

RawElement::RawElement(const TSTR& name, const TSTR& sValue)
{
	SetXmlType(XML_ELEMENT);
		
	SetName(name);
	
	SetValue(sValue);
}

RawElement::RawElement(const RawElement& other)
{
	if(this==&other)
		return;

	this->parent = other.parent;
	this->pAttrs = other.pAttrs;
	this->Name = other.Name;
	this->Value = other.Value;
	this->xmltype = other.xmltype;
	this->pVec = other.pVec;
}

RawElement& RawElement::operator=(const RawElement& other)
{
	if(this==&other)
		return *this;

	this->parent = other.parent;
	this->pAttrs = other.pAttrs;
	this->Name = other.Name;
	this->Value = other.Value;
	this->xmltype = other.xmltype;
	this->pVec = other.pVec;

	return *this;
}

RawElement::~RawElement(void)
{
}

bool RawElement::Append(RawTreeNode* child)
{
	if(!child)
		return false;

	child->SetParent(this);
	GetVec()->push_back(child);

	return true;
}

RawElement RawElement::Add(RawTreeNode* node1)
{
	Append(node1);

	return *this;
}

RawElement RawElement::operator[](const _ELCHAR* name)
{
	return Find(name);
}

RawElement RawElement::Find(const TSTR& names)
{
	std::vector<TSTR> vec;
	bool bMultipleParent = false;

	TSTR temp = names;
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	int size = temp.FindOneOf(_TS("|"));
	if(size!=-1)
	{
		bMultipleParent = true;
	}
#else
	size_t size = temp.find_first_of(_TS('|'));
	if(size!=STDSTR::npos)
	{
		bMultipleParent = true;
	}
#endif
	if(bMultipleParent)
	{
		_ELCHAR seps[]   = _TS("|");
		_ELCHAR *token = NULL;
		_ELCHAR *next_token = NULL;

		const size_t arrSize = GET_SIZE(temp)+1;
		_ELCHAR *p = new _ELCHAR[arrSize];
		RAII_Array<_ELCHAR> raii = p;
		memset(p, 0, arrSize * sizeof(_ELCHAR));
		STRCPY(p, GET_CONST_PTR(temp), arrSize);
#ifdef _MICROSOFT
		token = STRTOK_S(p, seps, &next_token );
#else
	#ifdef _WIN32
		token = STRTOK(p, seps);
	#else
		token = STRTOK_R(p, seps, &next_token );
	#endif
#endif
		while( token != NULL )
		{
			vec.push_back(TSTR(token));
			// Get next token
#ifdef _MICROSOFT
			token = STRTOK_S( NULL, seps, &next_token );
#else
	#ifdef _WIN32
			token = STRTOK( NULL, seps );
	#else
			token = STRTOK_R( NULL, seps, &next_token );
	#endif
#endif
		}
		//delete [] p;
	}

	RawElement elem = *this;

	for(size_t i=0; i<vec.size(); ++i)
	{
		elem = elem.FindFirstChild(vec[i]);

		if(elem.Exists()==false)
			return RawElement();
	}

	return elem;
}

RawElement RawElement::FindFirstChild(const TSTR& name)
{
	size_t cnt = GetVec()->size();
	NODE_COLLECTION* vec = GetVec();
	for(size_t i=0;i<cnt;++i)
	{
		if((*vec)[i]->GetXmlType() == XML_ELEMENT && (*vec)[i]->GetName()==name)
		{
			return *(static_cast<RawElement*>((*vec)[i]));
		}
	}

	return RawElement();
}

bool RawElement::Save(std::map<TSTR, TSTR>& processingInstruction, const TSTR& file, FILE_TYPE fileType)
{
	TEXT_WRITER uf;
	// open for writing
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	STDSTR file2 = GET_CONST_PTR(file);
	bool bRet = uf.Open( file2, fileType, NEW );
#else
	bool bRet = uf.Open( file, fileType, NEW );
#endif
	if(bRet==false)
		return false;

	// write processing instruction

	TSTR procInst;
	FormatProcessingInstruction(processingInstruction, procInst);
	if(procInst!=_TS(""))
	{	
		uf.Write(procInst);
	}

	Traverse(*this, uf);

	uf.Flush();
	uf.Close();

	return true;
}

bool RawElement::PrettySave(std::map<TSTR, TSTR>& processingInstruction, const TSTR& file, FILE_TYPE fileType, const TSTR& indent)
{
	TEXT_WRITER uf;
	// open for writing
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	STDSTR file2 = GET_CONST_PTR(file);
	bool bRet = uf.Open( file2, fileType, NEW );
#else
	bool bRet = uf.Open( file, fileType, NEW );
#endif
	if(bRet==false)
		return false;

	// write processing instruction
	TSTR procInst;
	FormatProcessingInstruction(processingInstruction, procInst);
	if(procInst!=_TS(""))
	{	
		uf.Write(procInst);
		uf.Write(_TS("\n"));
	}

	PrettyTraverse(*this, uf, 0, indent);

	uf.Flush();
	uf.Close();

	return true;
}

void RawElement::FormatProcessingInstruction(const std::map<TSTR, TSTR>& processingInstruction, TSTR& dest)
{
	dest=_TS("");
	if(processingInstruction.size()==0)
	{
		return;
	}

	dest += _TS("<?xml");
	std::map<TSTR, TSTR>::const_iterator it = processingInstruction.find(_TS("version"));
	if(it!=processingInstruction.end())
		dest += _TS(" ") + it->first + _TS("=\"") + it->second + _TS("\"");
	it = processingInstruction.find(_TS("encoding"));
	if(it!=processingInstruction.end())
		dest += _TS(" ") + it->first + _TS("=\"") + it->second + _TS("\"");

	it = processingInstruction.begin();
	for(; it!=processingInstruction.end(); ++it)
	{
		if(it->first!=_TS("version")&&it->first!=_TS("encoding"))
			dest += _TS(" ") + it->first + _TS("=\"") + it->second + _TS("\"");
	}

	dest += _TS("?>");
}

bool RawElement::WriteIndent(TEXT_WRITER& uf, size_t cnt, const TSTR& indent)
{
	for(size_t i=0;i<cnt;++i)
		uf.Write(indent);

	return true;
}

bool RawElement::WriteStartElement(TEXT_WRITER& uf, size_t cnt, const TSTR& elementName, const TSTR& indent)
{
	WriteIndent(uf, cnt, indent);
	TSTR str = _TS("<");
	uf.Write(str+elementName);
	return true;
}

bool RawElement::WriteEndElement(TEXT_WRITER& uf, size_t cnt, const TSTR& elementName, const TSTR& indent)
{
	WriteIndent(uf, cnt, indent);
	TSTR str = _TS("</");
	uf.Write(str+elementName+_TS(">"));
	return true;
}

bool RawElement::WriteIndent(TSTR& uf, size_t cnt, const TSTR& indent)
{
	for(size_t i=0;i<cnt;++i)
		uf += indent;

	return true;
}

bool RawElement::WriteStartElement(TSTR& uf, size_t cnt, const TSTR& elementName, const TSTR& indent)
{
	WriteIndent(uf, cnt, indent);
	TSTR str = _TS("<");
	uf += (str+elementName);
	return true;
}

bool RawElement::WriteEndElement(TSTR& uf, size_t cnt, const TSTR& elementName, const TSTR& indent)
{
	WriteIndent(uf, cnt, indent);
	TSTR str = _TS("</");
	uf += (str+elementName+_TS(">"));
	return true;
}

bool RawElement::PrettyTraverse(RawTreeNode& node, TEXT_WRITER& uf, size_t cnt, const TSTR& indent)
{
	if(node.GetXmlType()==XML_ELEMENT)
	{
		TSTR name = node.GetName();
		TSTR val = node.GetValue();
		bool write_start_element = false;
		if(IS_EMPTY(name)==false)
		{
			WriteStartElement(uf, cnt, name, indent);
			write_start_element = true;
		}

		bool textValueWritten = false;
		bool attrOnly = false;
		bool attrWritten = false;

		if(node.GetAttrCount()>0)
		{
			if(node.GetVec()->size()==0)
				attrOnly = true;

			attrWritten = true;

			size_t cnt = node.GetAttrCount();
			ATTR_MAP* attrs = node.GetAttrs();
			for(size_t i=0;i<cnt;++i)
			{
				TSTR str = _TS(" ");
				str += attrs->At(i).first + _TS("=\"");
				str += EscapeXML(attrs->At(i).second);

				str += _TS("\"");
				uf.Write(str);
			}
		}

		bool closed = false;
		if (write_start_element && ((attrOnly||node.GetVec()->size()==0)&&IS_EMPTY(val)))
		{
			uf.Write(_TS("/>\n"));
			attrWritten = true;
			closed = true;
		}
		else if(false == IS_EMPTY(val))
		{
			uf.Write(_TS(">"));
		}
		else if(write_start_element)
		{
			uf.Write(_TS(">\n"));
		}

		++cnt;
		size_t vecCount = node.GetVec()->size();
		for(size_t i=0;i<vecCount; ++i)
		{
			RawTreeNode* node1 = (*node.GetVec())[i];
			PrettyTraverse(*node1, uf, cnt, indent);
		}
		--cnt;

		if(IS_EMPTY(val)==false)
		{
			//uf.Write(_TS(">"));
			TSTR str = EscapeXML(val);
			uf.Write(str);
			textValueWritten = true;
		}

		if(textValueWritten)
		{
			if(IS_EMPTY(name)==false)
			{
				WriteEndElement(uf, name);

				uf.Write(_TS("\n"));
			}
		}
		else if (false == attrOnly&&false==closed)
		{
			if(IS_EMPTY(name)==false)
			{
				WriteEndElement(uf, cnt, name, indent);

				uf.Write(_TS("\n"));
			}
		}
	}
	else if(node.GetXmlType()==XML_COMMENT)
	{
		WriteIndent(uf, cnt, indent);
		TSTR str = _TS("<!--");

		TSTR val = node.GetValue();

		if(IS_EMPTY(val)==false)
			str += EscapeXML(val);

		str += _TS("-->\n");
		uf.Write(str);
	}
	else if(node.GetXmlType()==XML_CDATA)
	{
		WriteIndent(uf, cnt, indent);
		TSTR str = _TS("<![CDATA[");
		TSTR val = node.GetValue();

		if(IS_EMPTY(val)==false)
			str += val;

		str += _TS("]]>\n");
		uf.Write(str);
	}

	return true;
}

bool RawElement::PrettyTraverse(RawTreeNode& node, TSTR& uf, size_t cnt, const TSTR& indent)
{
	if(node.GetXmlType()==XML_ELEMENT)
	{
		TSTR name = node.GetName();
		TSTR val = node.GetValue();

		if(IS_EMPTY(name)==false)
		{
			WriteStartElement(uf, cnt, name, indent);
		}

		bool textValueWritten = false;
		bool attrOnly = false;
		bool attrWritten = false;

		if(node.GetAttrCount()>0)
		{
			if(node.GetVec()->size()==0)
				attrOnly = true;

			attrWritten = true;

			size_t cnt = node.GetAttrCount();
			ATTR_MAP* attrs = node.GetAttrs();
			for(size_t i=0;i<cnt;++i)
			{
				TSTR str = _TS(" ");
				str += attrs->At(i).first + _TS("=\"");
				str += EscapeXML(attrs->At(i).second);

				str += _TS("\"");
				uf += str;
			}
		}

		bool closed = false;
		if ((attrOnly||node.GetVec()->size()==0)&&IS_EMPTY(val))
		{
			uf += _TS("/>\n");
			attrWritten = true;
			closed = true;
		}
		else if(false == IS_EMPTY(val))
		{
			uf += _TS(">");
		}
		else
		{
			uf += _TS(">\n");
		}

		++cnt;
		size_t vecCount = node.GetVec()->size();
		for(size_t i=0;i<vecCount; ++i)
		{
			RawTreeNode* node1 = (*node.GetVec())[i];
			PrettyTraverse(*node1, uf, cnt, indent);
		}
		--cnt;

		if(IS_EMPTY(val)==false)
		{
			//uf.Write(_TS(">"));
			TSTR str = EscapeXML(val);
			uf += str;
			textValueWritten = true;
		}

		if(textValueWritten)
		{
			if(IS_EMPTY(name)==false)
			{
				WriteEndElement(uf, name);

				uf += _TS("\n");
			}
		}
		else if (false == attrOnly&&false==closed)
		{
			if(IS_EMPTY(name)==false)
			{
				WriteEndElement(uf, cnt, name, indent);

				uf += _TS("\n");
			}
		}
	}
	else if(node.GetXmlType()==XML_COMMENT)
	{
		WriteIndent(uf, cnt, indent);
		TSTR str = _TS("<!--");

		TSTR val = node.GetValue();

		if(IS_EMPTY(val)==false)
			str += EscapeXML(val);

		str += _TS("-->\n");
		uf += str;
	}
	else if(node.GetXmlType()==XML_CDATA)
	{
		WriteIndent(uf, cnt, indent);
		TSTR str = _TS("<![CDATA[");
		TSTR val = node.GetValue();

		if(IS_EMPTY(val)==false)
			str += val;

		str += _TS("]]>\n");
		uf += str;
	}

	return true;
}

bool RawElement::WriteStartElement(TEXT_WRITER& uf, const TSTR& elementName)
{
	TSTR str = _TS("<");
	uf.Write(str+elementName);
	return true;
}

bool RawElement::WriteEndElement(TEXT_WRITER& uf, const TSTR& elementName)
{
	TSTR str = _TS("</");
	uf.Write(str+elementName+_TS(">"));
	return true;
}

bool RawElement::WriteStartElement(TSTR& uf, const TSTR& elementName)
{
	TSTR str = _TS("<");
	uf += (str+elementName);
	return true;
}

bool RawElement::WriteEndElement(TSTR& uf, const TSTR& elementName)
{
	TSTR str = _TS("</");
	uf += (str+elementName+_TS(">"));
	return true;
}

bool RawElement::Traverse(RawTreeNode& node, TEXT_WRITER& uf)
{
	if(node.GetXmlType()==XML_ELEMENT)
	{
		TSTR name = node.GetName();
		TSTR val = node.GetValue();

		if(IS_EMPTY(name)==false)
			WriteStartElement(uf, name);

		bool attrWritten = false;
		bool attrOnly = false;

		if(node.GetAttrCount()>0)
		{
			if(node.GetVec()->size()==0)
				attrOnly = true;

			attrWritten = true;

			size_t cnt = node.GetAttrCount();
			ATTR_MAP* attrs = node.GetAttrs();

			for(size_t i=0;i<cnt;++i)
			{
				TSTR str = _TS(" ");
				str += attrs->At(i).first + _TS("=\"");
				str += EscapeXML(attrs->At(i).second);

				str += _TS("\"");
				uf.Write(str);
			}
		}

		bool closed = false;
		if ((attrOnly||node.GetVec()->size()==0)&&IS_EMPTY(val))
		{
			uf.Write(_TS("/>"));
			attrWritten = true;
			closed = true;
		}
		else //if(node.GetVec()->size()>0)
		{
			uf.Write(_TS(">"));
		}

		size_t vecCount = node.GetVec()->size();
		for(size_t i=0;i<vecCount; ++i)
		{
			RawTreeNode* node1 = (*node.GetVec())[i];;
			Traverse(*node1, uf);
		}

		if(IS_EMPTY(val)==false)
		{
			//uf.Write(_TS(">"));

			TSTR str = EscapeXML(val);
			uf.Write(str);
		}

		if (false==closed)
		{
			if(IS_EMPTY(name)==false)
				WriteEndElement(uf, name);
		}
	}
	else if(node.GetXmlType()==XML_COMMENT)
	{
		TSTR str = _TS("<!--");

		TSTR val = node.GetValue();

		if(IS_EMPTY(val)==false)
			str += EscapeXML(val);

		str += _TS("-->");
		uf.Write(str);
	}
	else if(node.GetXmlType()==XML_CDATA)
	{
		TSTR str = _TS("<![CDATA[");
		TSTR val = node.GetValue();

		if(IS_EMPTY(val)==false)
			str += val;

		str += _TS("]]>");
		uf.Write(str);
	}

	return true;
}

bool RawElement::Traverse(RawTreeNode& node, TSTR& uf)
{
	if(node.GetXmlType()==XML_ELEMENT)
	{
		TSTR name = node.GetName();
		TSTR val = node.GetValue();

		if(IS_EMPTY(name)==false)
			WriteStartElement(uf, name);

		bool attrWritten = false;
		bool attrOnly = false;

		if(node.GetAttrCount()>0)
		{
			if(node.GetVec()->size()==0)
				attrOnly = true;

			attrWritten = true;

			size_t cnt = node.GetAttrCount();
			ATTR_MAP* attrs = node.GetAttrs();

			for(size_t i=0;i<cnt;++i)
			{
				TSTR str = _TS(" ");
				str += attrs->At(i).first + _TS("=\"");
				str += EscapeXML(attrs->At(i).second);

				str += _TS("\"");
				uf += str;
			}
		}

		bool closed = false;
		if ((attrOnly||node.GetVec()->size()==0)&&IS_EMPTY(val))
		{
			uf += _TS("/>");
			attrWritten = true;
			closed = true;
		}
		else //if(node.GetVec()->size()>0)
		{
			uf += _TS(">");
		}

		size_t vecCount = node.GetVec()->size();
		for(size_t i=0;i<vecCount; ++i)
		{
			RawTreeNode* node1 = (*node.GetVec())[i];;
			Traverse(*node1, uf);
		}

		if(IS_EMPTY(val)==false)
		{
			//uf.Write(_TS(">"));

			TSTR str = EscapeXML(val);
			uf += str;
		}

		if (false==closed)
		{
			if(IS_EMPTY(name)==false)
				WriteEndElement(uf, name);
		}
	}
	else if(node.GetXmlType()==XML_COMMENT)
	{
		TSTR str = _TS("<!--");

		TSTR val = node.GetValue();

		if(IS_EMPTY(val)==false)
			str += EscapeXML(val);

		str += _TS("-->");
		uf += str;
	}
	else if(node.GetXmlType()==XML_CDATA)
	{
		TSTR str = _TS("<![CDATA[");
		TSTR val = node.GetValue();

		if(IS_EMPTY(val)==false)
			str += val;

		str += _TS("]]>");
		uf += str;
	}

	return true;
}

TSTR RawElement::Replace( 
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

TSTR RawElement::EscapeXML( 
	const TSTR& fmtstr)
{
	TSTR fmtstr1 = Replace(fmtstr, _TS("&"), _TS("&amp;"));
	fmtstr1 = Replace(fmtstr1, _TS("\""), _TS("&quot;"));
	fmtstr1 = Replace(fmtstr1, _TS("\'"), _TS("&apos;"));
	fmtstr1 = Replace(fmtstr1, _TS("<"), _TS("&lt;"));
	fmtstr1 = Replace(fmtstr1, _TS(">"), _TS("&gt;"));

	return fmtstr1;
}

TSTR RawElement::UnescapeXML( 
	const TSTR& fmtstr)
{
	TSTR fmtstr1 = Replace(fmtstr, _TS("&amp;"), _TS("&"));
	fmtstr1 = Replace(fmtstr1, _TS("&quot;"), _TS("\""));
	fmtstr1 = Replace(fmtstr1, _TS("&apos;"), _TS("\'"));
	fmtstr1 = Replace(fmtstr1, _TS("&lt;"), _TS("<"));
	fmtstr1 = Replace(fmtstr1, _TS("&gt;"), _TS(">"));

	return fmtstr1;
}

bool RawElement::IsValidName(const TSTR& name)
{
	for(size_t i=0; i<GET_SIZE(name); ++i)
	{
		_ELCHAR ch = name[i];

		if(i==0)
		{
			if(ch>=_TS('0')&&ch<=_TS('9'))
				return false;
		}

		if(!(
			(ch>=_TS('a')&&ch<=_TS('z'))||
			(ch>=_TS('A')&&ch<=_TS('Z'))||
			(ch>=_TS('0')&&ch<=_TS('9'))||
			ch=='-'||ch=='_'||ch=='.'
			))
		{
			return false;
		}
	}

	return true;
}

RawElement* RawElement::FindElementRoot()
{
	RawElement* tmp = this;
	RawElement* found = NULL;

	while(true)
	{
		if(tmp->parent!=NULL)
			tmp = static_cast<RawElement*>(tmp->parent);
		else
		{
			found = tmp;
			break;
		}
	}

	return found;
}

bool RawElement::Open(std::map<TSTR, TSTR>& processingInstruction, const TSTR& file)
{
	TEXT_READER f;
	TSTR contents=_TS("");
#if defined ELMAX_USE_MFC_CSTRING || ELMAX_USE_CUSTOM_STRING
	bool res = f.Open(GET_CONST_PTR(file), FT_UTF8);
#else
	bool res = f.Open(file, FT_UTF8);
#endif
	if(res)
	{
#if defined ELMAX_USE_MFC_CSTRING || ELMAX_USE_CUSTOM_STRING
		STDSTR temp=_TS("");
		if(f.ReadAll(temp))
		{
			contents = temp.c_str();
			return ParseXMLString(processingInstruction, contents);
		}
#else
		if(f.ReadAll(contents))
			return ParseXMLString(processingInstruction, contents);
#endif
	}
	return false;
}

// /> : start element end
// </ : end element start


// /> : start element end
// </ : end element start

bool RawElement::ParseXMLString(std::map<TSTR, TSTR>& processingInstruction, const TSTR& src)
{
	size_t i = 0;
	size_t newline_cnt=0;
	while(IsProcessingInstructionStart(src, i))
	{
		i += ProcessingInstructionStartLength;
		TSTR prep;
		ReadProcessingInstructionValue(src, i, prep, processingInstruction, newline_cnt);
	}
	while(IsDocTypeStart(src, i))
	{
		i += DocTypeStartLength;
		TSTR dest;
		ReadDocType(src, i, dest);
	}

	std::stack<stNode> StackElement;
	TSTR name;
	TSTR val;
	TSTR text;
	_ELCHAR ch='\0';
	while(i<GET_SIZE(src))
	{
		text = _TS("");
		while(IsContent(src, i))
		{
			text += src[i];
			++i;
		}

		if(GET_SIZE(text)>0)
		{
			if(IsWhitespace(text,newline_cnt)==false)
			{
				if(StackElement.size()>0)
				{
					RawTreeNode* parent = StackElement.top().ptr;
					parent->SetValue(UnescapeXML(text));
				}
			}
		}

		if(i>=GET_SIZE(src))
			break;

		ch = src[i];
		if(IsCDataStart(src, i))
		{
			i += CDataStartLength;
			ReadCDataValue(src, i, val);
			if(StackElement.size()>0)
			{
				RawTreeNode* parent = StackElement.top().ptr;
				RawCData* cdata = new RawCData(val);
				parent->AddChild(cdata);
			}
			else // stack is empty
			{
				//RawCData* cdata = new RawCData(val);
				//GetVec()->Add(cdata);
			}
		}
		else if(IsCommentStart(src, i))
		{
			i += CommentStartLength;
			ReadCommentValue(src, i, val);
			if(StackElement.size()>0)
			{
				RawTreeNode* parent = StackElement.top().ptr;
				RawComment* comment = new RawComment(val);
				parent->AddChild(comment);
			}
			else // stack is empty
			{
				//RawComment* comment = new RawComment(val);
				//GetVec()->Add(comment);
			}
		}
		else if(src[i]==_TS('<')&&IsEndElementStart(src, i)==false) // is start element
		{
			// read element
			AfterElementName res = None;
			++i;
			if(ReadElementName(src, i, name, res, newline_cnt))
			{
				if(name==_TS(""))
				{
					throw std::runtime_error("empty name");
				}
				if(StackElement.size()>0)
				{
					RawTreeNode* parent = StackElement.top().ptr;
					RawElement* elem = new RawElement();
					elem->SetName(name);
					stNode node(elem, newline_cnt+1);
					StackElement.push(node);
					parent->AddChild(elem);
				}
				else // stack is empty
				{
					this->SetName(name);
					stNode node(this, newline_cnt+1);
					StackElement.push(node);
				}

				if(res==EncounterWhitespace)
				{
					while(i<GET_SIZE(src))
					{
						while(IsWhitespace(src, i, newline_cnt))
						{
							++i;
						}

						if(IsStartElementEnd(src, i))
						{
							i += 1;
							StackElement.pop();
							break;
						}

						if(src[i]==_TS('>'))
						{
							//++i;
							break;
						}

						ReadAttributeName(src, i, name, newline_cnt);
						
						while(IsWhitespace(src, i, newline_cnt)||src[i]==_TS('='))
							++i;

						ReadAttributeValue(src, i, val);

						if(name!=_TS(""))
						{
							RawTreeNode* parent = StackElement.top().ptr;
							parent->GetAttrs()->Add(name, val);
						}
					}
				}
				else if(res==ElementEnded)
				{
					StackElement.pop();
				}
			}
			else // parser error
			{
				PrintStack(i, newline_cnt, "Start tag error", StackElement);
			}
		}
		else // is end element
		{
			AfterElementName result;
			i += 2;
			if(ReadElementName(src, i, name, result, newline_cnt))
			{
				if(name==_TS(""))
				{
					PrintStack(i, newline_cnt, "The ending tag error", StackElement);
				}

				if(result==NodeEnded)
				{
					if(StackElement.top().ptr->GetName()!=name)
					{
						// print error of different start and end names
						TSTR error = _TS("Different start and end tag:");
#ifdef ELMAX_USE_UNICODE
						error+=_TS("Expect <");
						error+=GET_CONST_PTR(StackElement.top().ptr->GetName());
						error+=_TS("> but received </");
						error+=name + _TS(">");
#else
						error+=_TS("Expect <")+StackElement.top().ptr->GetName() + _TS("> but received </") + name + _TS(">");
#endif
						PrintStack(i, newline_cnt, StrConv::ConvToAString(error), StackElement);
						return false;
					}
					else
					{
						StackElement.pop();
					}
				}
			}
			else
			{
				// print all stack names and element without a end element
				PrintStack(i, newline_cnt, "The last element does not have a ending tag", StackElement);
			}

		}
		++i;
	}

	if(StackElement.size()>0)
	{
		PrintStack(i, newline_cnt, "The element does not have a ending tag", StackElement);
		return false;
	}

	return true;
}

void RawElement::PrintStack(size_t pos, size_t line, const std::string& error, std::stack<stNode>& StackElement)
{
	++line; // one based counting
	// print all the stack names
	std::vector<stNode> vecTemp;
	while(StackElement.size()>0)
	{
		stNode node = StackElement.top();
		vecTemp.push_back(node);
		StackElement.pop();
	}
	std::vector<stNode>::const_reverse_iterator it = vecTemp.rbegin();
	std::string err=error+":Parsing error near pos="+std::to_string(pos)+", line no.="+std::to_string(line)+":";

#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		for(;it!=vecTemp.rend();++it)
			err += "<" + StrConv::ConvToAString(it->ptr->GetName()) + " LineNum:"+std::to_string(it->line_num) +  ">";
	#else
		for(;it!=vecTemp.rend();++it)
			err += "<";
			err += GET_CONST_PTR(it->ptr->GetName());
			err += " LineNum:"+std::to_string(it->line_num);
			err	+= ">";
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		for(;it!=vecTemp.rend();++it)
			err += "<" + StrConv::ConvToAString(it->ptr->GetName()) + " LineNum:"+std::to_string(it->line_num) +  ">";
	#else
		for(;it!=vecTemp.rend();++it)
			err += "<" + it->ptr->GetName() + " LineNum:"+std::to_string(it->line_num) +  ">";
	#endif
#endif
	throw std::runtime_error(err);

}

TSTR RawElement::ToString()
{
	TSTR uf = _TS("");
	Traverse(*this, uf);
	return uf;
}

TSTR RawElement::ToPrettyString(const TSTR& indent)
{
	TSTR uf = _TS("");
	PrettyTraverse(*this, uf, 0, indent);
	return uf;
}

bool RawElement::IsContent(const TSTR& src, size_t index)
{
	if(index>=GET_SIZE(src))
		return false;

	_ELCHAR ch = src[index];

	return ch != _TS('<') && ch != _TS('>');
}

bool RawElement::IsWhitespace(const TSTR& src, size_t& newline_cnt)
{
	if(src==_TS(""))
		return true;

	bool whiteline = true;
	for(size_t i=0; i<GET_SIZE(src); ++i)
	{
		if(IsWhitespace(src[i], newline_cnt)==false)
		{
			whiteline = false;
		}
	}
	return whiteline;
}

bool RawElement::IsWhitespace(const TSTR& src, size_t index, size_t& newline_cnt)
{
	if(index>=GET_SIZE(src))
		return false;

	_ELCHAR ch = src[index];

	if(ch == _TS('\n'))
		++newline_cnt;

	return ch == _TS(' ') || ch == _TS('\n') || ch == _TS('\t') || ch == _TS('\r');
}

bool RawElement::IsWhitespace(_ELCHAR ch, size_t& newline_cnt)
{
	if(ch == _TS('\n'))
		++newline_cnt;

	return ch == _TS(' ') || ch == _TS('\n') || ch == _TS('\t') || ch == _TS('\r');
}

bool RawElement::IsStartElementEnd(const TSTR& src, size_t index)
{
	if(index + 1 < GET_SIZE(src))
	{
		// comparing "/>"
		return src[index] == _TS('/') && src[index+1] == _TS('>');
	}

	return false;
}

bool RawElement::IsEndElementStart(const TSTR& src, size_t index)
{
	if(index + 1 < GET_SIZE(src))
	{
		// comparing "</"
		return src[index] == _TS('<') && src[index+1] == _TS('/');
	}

	return false;
}

bool RawElement::IsProcessingInstructionStart(const TSTR& src, size_t index)
{
	if(index + 4 < GET_SIZE(src))
	{
		// comparing "<?xml"
		return src[index] == _TS('<') && src[index+1] == _TS('?') && src[index+2] == _TS('x')
			&& src[index+3] == _TS('m') && src[index+4] == _TS('l');
	}

	return false;
}

bool RawElement::IsProcessingInstructionEnd(const TSTR& src, size_t index)
{
	if(index + 1 < GET_SIZE(src))
	{
		// comparing "?>"
		return src[index] == _TS('?') && src[index+1] == _TS('>');
	}

	return false;
}

bool RawElement::IsDocTypeStart(const TSTR& src, size_t index)
{
	if(index + 8 < GET_SIZE(src))
	{
		// comparing "<!DOCTYPE"
		return src[index] == _TS('<') && src[index+1] == _TS('!') && src[index+2] == _TS('D')
			&& src[index+3] == _TS('O') && src[index+4] == _TS('C') && src[index+5] == _TS('T')
			&& src[index+6] == _TS('Y') && src[index+7] == _TS('P') && src[index+8] == _TS('E');
	}

	return false;
}

bool RawElement::IsDocTypeEnd(const TSTR& src, size_t index)
{
	if(index < GET_SIZE(src))
	{
		// comparing ">"
		return src[index] == _TS('>');
	}

	return false;
}

bool RawElement::IsCDataStart(const TSTR& src, size_t index)
{
	if(index + 8 < GET_SIZE(src))
	{
		// comparing "<![CDATA["
		return src[index] == _TS('<') && src[index+1] == _TS('!') && src[index+2] == _TS('[') &&
			src[index+3] == _TS('C') && src[index+4] == _TS('D') && src[index+5] == _TS('A') &&
			src[index+6] == _TS('T') && src[index+7] == _TS('A') && src[index+8] == _TS('[');
	}

	return false;
}

bool RawElement::IsCDataEnd(const TSTR& src, size_t index)
{
	if(index + 2 < GET_SIZE(src))
	{
		// comparing "]]>"
		return src[index] == _TS(']') && src[index+1] == _TS(']') && src[index+2] == _TS('>');
	}

	return false;
}

bool RawElement::IsCommentStart(const TSTR& src, size_t index)
{
	if(index + 3 < GET_SIZE(src))
	{
		// comparing "<!--"
		return src[index] == _TS('<') && src[index+1] == _TS('!') && src[index+2] == _TS('-') && src[index+3] == _TS('-');
	}

	return false;
}

bool RawElement::IsCommentEnd(const TSTR& src, size_t index)
{
	if(index + 2 < GET_SIZE(src))
	{
		// comparing "-->"
		return src[index] == _TS('-') && src[index+1] == _TS('-') && src[index+2] == _TS('>');
	}

	return false;
}

bool RawElement::ReadProcessingInstructionValue(const TSTR& src, size_t& index, TSTR& dest, std::map<TSTR, TSTR>& processingInstruction, size_t& newline_cnt)
{
	dest = _TS("");
	while(IsProcessingInstructionEnd(src, index)==false)
		dest += src[index++];

	index += ProcessingInstructionEndLength;

	TSTR name, val;
	for(size_t i=0;i<GET_SIZE(dest); ++i)
	{
		while(IsWhitespace(dest, i, newline_cnt))
		{
			++i;
		}

		ReadAttributeName(dest, i, name, newline_cnt);

		while(IsWhitespace(dest, i, newline_cnt)||dest[i]==_TS('='))
			++i;

		ReadAttributeValue(dest, i, val);

		if(name!=_TS("")&&val!=_TS(""))
		{
			processingInstruction[name] = val;
		}
	}
	
	return true;
}

bool RawElement::ReadDocType(const TSTR& src, size_t& index, TSTR& dest)
{
	dest = _TS("");
	while(IsDocTypeEnd(src, index)==false)
		dest += src[index++];

	index += DocTypeEndLength;

	return true;
}

bool RawElement::ReadElementName(const TSTR& src, size_t& index, TSTR& dest, AfterElementName& res, size_t& newline_cnt)
{
	dest = _TS("");
	res = None;
	while(src[index]!=_TS('>'))
	{
		if(IsWhitespace(src[index],newline_cnt))
		{
			res=EncounterWhitespace;
			return true;
		}
			
		if(IsStartElementEnd(src, index))
		{
			res=ElementEnded;
			index += 1;
			return true;
		}

		dest += src[index];

		++index;

		if(index>=GET_SIZE(src))
			return false;
	}

	if(src[index]==_TS('>'))
	{
		res=NodeEnded;
	}

	if(GET_SIZE(dest)==0)
		return false;
	
	return true;
}

// return false means this element has no text, what follows may be a start element or end element.
bool RawElement::ReadElementValue(const TSTR& src, size_t& index, TSTR& dest, size_t& newline_cnt)
{
	dest = _TS("");
	while(src[index]!=_TS('<'))
	{
		if(IsWhitespace(src[index],newline_cnt)==false)
			dest += src[index];

		++index;

		if(index>=GET_SIZE(src))
			return false;
	}

	--index;

	if(GET_SIZE(dest)>0)
	{
		dest = UnescapeXML(dest);
		return true;
	}

	return false;
}

bool RawElement::ReadAttributeName(const TSTR& src, size_t& index, TSTR& dest, size_t& newline_cnt)
{
	dest = _TS("");
	while(src[index]!=_TS('='))
	{
		if(IsWhitespace(src[index],newline_cnt)==false)
			dest += src[index];
		else
			break;

		++index;

		if(index>=GET_SIZE(src))
			return false;
	}

	return true;
}

bool RawElement::ReadAttributeValue(const TSTR& src, size_t& index, TSTR& dest)
{
	dest = _TS("");
	++index;
	if(src[index]==_TS('\"')&&src[index+1]==_TS('\"'))
	{
		++index;
		return true;
	}
	while(src[index]!=_TS('\"'))
	{
		dest += src[index];
		++index;

		if(index>=GET_SIZE(src))
			return false;
	}

	++index;

	dest = UnescapeXML(dest);

	return true;
}

bool RawElement::ReadCDataValue(const TSTR& src, size_t& index, TSTR& dest)
{
	dest = _TS("");
	while(IsCDataEnd(src, index)==false)
		dest += src[index++];

	index += (CDataEndLength-1);
	
	return true;
}

bool RawElement::ReadCommentValue(const TSTR& src, size_t& index, TSTR& dest)
{
	dest = _TS("");
	while(IsCommentEnd(src, index)==false)
		dest += src[index++];

	index += (CommentEndLength-1);

	dest = UnescapeXML(dest);

	return true;
}
