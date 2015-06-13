#include "Document.h"
#include "../RawElement/RawElement.h"
#include <boost/lexical_cast.hpp>
#include "../Utils/StrConv.h"

const size_t Document::StartElementEndLength = 2;
const size_t Document::EndElementStartLength = 2;
const size_t Document::ProcessingInstructionStartLength = 5;
const size_t Document::ProcessingInstructionEndLength = 2;
const size_t Document::DocTypeStartLength = 9;
const size_t Document::DocTypeEndLength = 1;
const size_t Document::CDataStartLength = 9;
const size_t Document::CDataEndLength = 3;
const size_t Document::CommentStartLength = 4;
const size_t Document::CommentEndLength = 3;

Document::Document(void)
{
}


Document::~Document(void)
{
}

bool Document::Open(const TSTR& file)
{
	std::map<TSTR, TSTR> processingInstruction;
	return Open(processingInstruction, file);
}

bool Document::Open(std::map<TSTR, TSTR>& processingInstruction, const TSTR& file)
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

bool Document::ParseXMLString(std::map<TSTR, TSTR>& processingInstruction, const TSTR& src)
{
	size_t i = 0;
	size_t newline_cnt=0;
	while(IsProcessingInstructionStart(src, i))
	{
		i += ProcessingInstructionStartLength;
		TSTR prep;
		if(ReadProcessingInstructionValue(src, i, prep, processingInstruction, newline_cnt))
		{
			if(PreprocessFunctor)
			{
				std::map<TSTR, TSTR>::const_iterator it = processingInstruction.begin();
				for(; it!=processingInstruction.end(); ++it)
					PreprocessFunctor(it->first, it->second);
			}
		}
	}
	while(IsDocTypeStart(src, i))
	{
		i += DocTypeStartLength;
		TSTR dest;
		ReadDocType(src, i, dest);
	}

	StringStack StackElement;
	std::stack<size_t> StackLineNum;
	TSTR name;
	TSTR val;
	TSTR text;
	while(i<GET_SIZE(src))
	{
		text = _TS("");
		while(IsContent(src, i))
		{
			text += src[i];
			++i;
		}

		if(i>=GET_SIZE(src))
			break;

		if(IsCDataStart(src, i))
		{
			i += CDataStartLength;
			ReadCDataValue(src, i, val);
			if(StackElement.size()>0)
			{
#ifdef ELMAX_USE_BOOST_FUNC
				std::map<TSTR, boost::function<void(const TSTR&)> >::iterator it = map_CDataFunctor.find(StackElement.to_str());
#else
				std::map<TSTR, std::function<void(const TSTR&)> >::iterator it = map_CDataFunctor.find(StackElement.to_str());
#endif
				if(it!=map_CDataFunctor.end())
					it->second(val);
			}
		}
		else if(IsCommentStart(src, i))
		{
			i += CommentStartLength;
			ReadCommentValue(src, i, val);
			if(StackElement.size()>0)
			{
#ifdef ELMAX_USE_BOOST_FUNC
				std::map<TSTR, boost::function<void(const TSTR&)> >::iterator it = map_CommentFunctor.find(StackElement.to_str());
#else
				std::map<TSTR, std::function<void(const TSTR&)> >::iterator it = map_CommentFunctor.find(StackElement.to_str());
#endif
				if(it!=map_CommentFunctor.end())
					it->second(val);
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
				StackElement.push(name);
				StackLineNum.push(newline_cnt+1);

				SequelMax::RawElement* pRawElement = new SequelMax::RawElement(name);
				if(res==EncounterWhitespace)
				{
					bool isStartElementEnd = false;
					while(i<GET_SIZE(src))
					{
						while(IsWhitespace(src, i, newline_cnt))
						{
							++i;
						}

						isStartElementEnd = IsStartElementEnd(src, i);
						if (isStartElementEnd)
						{
							i += 1;
#ifdef ELMAX_USE_BOOST_FUNC
							std::map<TSTR, boost::function<void(SequelMax::Element&)> >::iterator it = map_StartElemFunctor.find(StackElement.to_str());
#else
							std::map<TSTR, std::function<void(SequelMax::Element&)> >::iterator it = map_StartElemFunctor.find(StackElement.to_str());
#endif
							if(it!=map_StartElemFunctor.end())
							{
								SequelMax::Element elem(pRawElement);
								it->second(elem);
							}
							else
							{
								pRawElement->Destroy();
								delete pRawElement;
								pRawElement = NULL;
							}
#ifdef ELMAX_USE_BOOST_FUNC
							std::map<TSTR, boost::function<void(const TSTR&)> >::iterator itEnd = map_EndElemFunctor.find(StackElement.to_str());
#else
							std::map<TSTR, std::function<void(const TSTR&)> >::iterator itEnd = map_EndElemFunctor.find(StackElement.to_str());
#endif
							if(itEnd!=map_EndElemFunctor.end())
								itEnd->second(_TS(""));


							StackElement.pop();
							StackLineNum.pop();
							goto breakout;
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
							pRawElement->GetAttrs()->Add(name, val);
						}
					}
#ifdef ELMAX_USE_BOOST_FUNC
					std::map<TSTR, boost::function<void(SequelMax::Element&)> >::iterator it = map_StartElemFunctor.find(StackElement.to_str());
#else
					std::map<TSTR, std::function<void(SequelMax::Element&)> >::iterator it = map_StartElemFunctor.find(StackElement.to_str());
#endif
					if(it!=map_StartElemFunctor.end())
					{
						SequelMax::Element elem(pRawElement);
						it->second(elem);
					}
					else
					{
						if (!isStartElementEnd)
						{
							pRawElement->Destroy();
							delete pRawElement;
							pRawElement = NULL;
						}
					}

				}
				else if(res==ElementEnded)
				{
#ifdef ELMAX_USE_BOOST_FUNC
					std::map<TSTR, boost::function<void(SequelMax::Element&)> >::iterator it = map_StartElemFunctor.find(StackElement.to_str());
#else
					std::map<TSTR, std::function<void(SequelMax::Element&)> >::iterator it = map_StartElemFunctor.find(StackElement.to_str());
#endif
					if(it!=map_StartElemFunctor.end())
					{
						SequelMax::Element elem(pRawElement);
						it->second(elem);
					}
					else
					{
						pRawElement->Destroy();
						delete pRawElement;
						pRawElement = NULL;
					}
#ifdef ELMAX_USE_BOOST_FUNC
					std::map<TSTR, boost::function<void(const TSTR&)> >::iterator itEnd = map_EndElemFunctor.find(StackElement.to_str());
#else
					std::map<TSTR, std::function<void(const TSTR&)> >::iterator itEnd = map_EndElemFunctor.find(StackElement.to_str());
#endif
					if(itEnd!=map_EndElemFunctor.end())
						itEnd->second(_TS(""));

					StackElement.pop();
					StackLineNum.pop();
				}
				else // NodeEnded
				{
#ifdef ELMAX_USE_BOOST_FUNC
					std::map<TSTR, boost::function<void(SequelMax::Element&)> >::iterator it = map_StartElemFunctor.find(StackElement.to_str());
#else
					std::map<TSTR, std::function<void(SequelMax::Element&)> >::iterator it = map_StartElemFunctor.find(StackElement.to_str());
#endif
					if(it!=map_StartElemFunctor.end())
					{
						SequelMax::Element elem(pRawElement);
						it->second(elem);
					}
					else
					{
						pRawElement->Destroy();
						delete pRawElement;
						pRawElement = NULL;
					}
				}
			}
			else // parser error
			{
				PrintStack(i, newline_cnt, "Start tag error", StackElement, StackLineNum);
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
					PrintStack(i, newline_cnt, "The ending tag error", StackElement, StackLineNum);
				}

				if(result==NodeEnded)
				{
					if(StackElement.top()!=name)
					{
						// print error of different start and end names
						TSTR error = _TS("Different start and end tag:");
#ifdef ELMAX_USE_UNICODE
						error+=_TS("Expect <");
						error+=GET_CONST_PTR(StackElement.top());
						error+=_TS("> but received </");
						error+=name + _TS(">");
#else
						error+=_TS("Expect <")+StackElement.top() + _TS("> but received </") + name + _TS(">");
#endif
						PrintStack(i, newline_cnt, StrConv::ConvToAString(error), StackElement, StackLineNum);
						return false;
					}
					else
					{
#ifdef ELMAX_USE_BOOST_FUNC
						std::map<TSTR, boost::function<void(const TSTR&)> >::iterator it = map_EndElemFunctor.find(StackElement.to_str());
#else
						std::map<TSTR, std::function<void(const TSTR&)> >::iterator it = map_EndElemFunctor.find(StackElement.to_str());
#endif
						if(it!=map_EndElemFunctor.end())
						{
							size_t newline_cnt=0;
							if(IsWhitespace(text, newline_cnt))
								it->second(_TS(""));
							else
								it->second(UnescapeXML(text));
						}

						StackElement.pop();
						StackLineNum.pop();
					}
				}
			}
			else
			{
				// print all stack names and element without a end element
				PrintStack(i, newline_cnt, "The last element does not have a ending tag", StackElement, StackLineNum);
			}

		}
breakout:
		++i;
	}

	if(StackElement.size()>0)
	{
		PrintStack(i, newline_cnt, "The element does not have a ending tag", StackElement, StackLineNum);
		return false;
	}

	return true;
}

void Document::PrintStack(size_t pos, size_t line, const std::string& error, StringStack& StackElement, std::stack<size_t>& StackLineNum)
{
	++line; // one based counting
	// print all the stack names
	std::vector<TSTR> vecTemp;
	std::vector<size_t> vecLineNum;
	while(StackElement.size()>0)
	{
		TSTR name = StackElement.top();
		vecTemp.push_back(name);
		StackElement.pop();
		size_t line = StackLineNum.top();
		vecLineNum.push_back(line);
		StackLineNum.pop();
	}
	std::vector<TSTR>::const_reverse_iterator it = vecTemp.rbegin();
	std::vector<size_t>::const_reverse_iterator itLine = vecLineNum.rbegin();
	std::string err=error+":Parsing error near pos="+boost::lexical_cast<std::string>(pos)+", line no.="+boost::lexical_cast<std::string>(line)+":";

#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	for(;it!=vecTemp.rend();++it, ++itLine)
		err += "<" + StrConv::ConvToAString(*it) + " LineNum:"+boost::lexical_cast<std::string>(*itLine) +  ">";
#else
	for(;it!=vecTemp.rend();++it, ++itLine)
	{
		err += "<";
		err += GET_CONST_PTR(*it);
		err += " LineNum:"+boost::lexical_cast<std::string>(*itLine);
		err += ">";
	}
#endif
#else
#ifdef ELMAX_USE_UNICODE
	for(;it!=vecTemp.rend();++it, ++itLine)
		err += "<" + StrConv::ConvToAString(*it) + " LineNum:"+boost::lexical_cast<std::string>(*itLine) +  ">";
#else
	for(;it!=vecTemp.rend();++it, ++itLine)
		err += "<" + *it + " LineNum:"+boost::lexical_cast<std::string>(*itLine) +  ">";
#endif
#endif
	throw std::runtime_error(err);

}

TSTR Document::Replace( 
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

TSTR Document::UnescapeXML( 
	const TSTR& fmtstr)
{
	TSTR fmtstr1 = Replace(fmtstr, _TS("&amp;"), _TS("&"));
	fmtstr1 = Replace(fmtstr1, _TS("&quot;"), _TS("\""));
	fmtstr1 = Replace(fmtstr1, _TS("&apos;"), _TS("\'"));
	fmtstr1 = Replace(fmtstr1, _TS("&lt;"), _TS("<"));
	fmtstr1 = Replace(fmtstr1, _TS("&gt;"), _TS(">"));

	return fmtstr1;
}

#ifdef ELMAX_USE_BOOST_FUNC
void Document::RegisterProcessingInstructionFunctor(boost::function<void(const TSTR&, const TSTR&)> f)
#else
void Document::RegisterProcessingInstructionFunctor(std::function<void(const TSTR&, const TSTR&)> f)
#endif
{
	PreprocessFunctor = f;
}

#ifdef ELMAX_USE_BOOST_FUNC
void Document::RegisterStartElementFunctor(const TSTR& elems, boost::function<void(SequelMax::Element&)> f)
#else
void Document::RegisterStartElementFunctor(const TSTR& elems, std::function<void(SequelMax::Element&)> f)
#endif
{
	map_StartElemFunctor[elems] = f;
}

#ifdef ELMAX_USE_BOOST_FUNC
void Document::RegisterEndElementFunctor(const TSTR& elems, boost::function<void(const TSTR&)> f)
#else
void Document::RegisterEndElementFunctor(const TSTR& elems, std::function<void(const TSTR&)> f)
#endif
{
	map_EndElemFunctor[elems] = f;
}

#ifdef ELMAX_USE_BOOST_FUNC
void Document::RegisterCommentFunctor(const TSTR& elems, boost::function<void(const TSTR&)> f)
#else
void Document::RegisterCommentFunctor(const TSTR& elems, std::function<void(const TSTR&)> f)
#endif
{
	map_CommentFunctor[elems] = f;
}

#ifdef ELMAX_USE_BOOST_FUNC
void Document::RegisterCDataFunctor(const TSTR& elems, boost::function<void(const TSTR&)> f)
#else
void Document::RegisterCDataFunctor(const TSTR& elems, std::function<void(const TSTR&)> f)
#endif
{
	map_CDataFunctor[elems] = f;
}


bool Document::IsContent(const TSTR& src, size_t index)
{
	if(index>=GET_SIZE(src))
		return false;

	_ELCHAR ch = src[index];

	return ch != _TS('<') && ch != _TS('>');
}

bool Document::IsWhitespace(const TSTR& src, size_t& newline_cnt)
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

bool Document::IsWhitespace(const TSTR& src, size_t index, size_t& newline_cnt)
{
	if(index>=GET_SIZE(src))
		return false;

	_ELCHAR ch = src[index];

	if(ch == _TS('\n'))
		++newline_cnt;

	return ch == _TS(' ') || ch == _TS('\n') || ch == _TS('\t') || ch == _TS('\r');
}

bool Document::IsWhitespace(_ELCHAR ch, size_t& newline_cnt)
{
	if(ch == _TS('\n'))
		++newline_cnt;

	return ch == _TS(' ') || ch == _TS('\n') || ch == _TS('\t') || ch == _TS('\r');
}

bool Document::IsStartElementEnd(const TSTR& src, size_t index)
{
	if(index + 1 < GET_SIZE(src))
	{
		// comparing "/>"
		return src[index] == _TS('/') && src[index+1] == _TS('>');
	}

	return false;
}

bool Document::IsEndElementStart(const TSTR& src, size_t index)
{
	if(index + 1 < GET_SIZE(src))
	{
		// comparing "</"
		return src[index] == _TS('<') && src[index+1] == _TS('/');
	}

	return false;
}

bool Document::IsProcessingInstructionStart(const TSTR& src, size_t index)
{
	if(index + 4 < GET_SIZE(src))
	{
		// comparing "<?xml"
		return src[index] == _TS('<') && src[index+1] == _TS('?') && src[index+2] == _TS('x')
			&& src[index+3] == _TS('m') && src[index+4] == _TS('l');
	}

	return false;
}

bool Document::IsProcessingInstructionEnd(const TSTR& src, size_t index)
{
	if(index + 1 < GET_SIZE(src))
	{
		// comparing "?>"
		return src[index] == _TS('?') && src[index+1] == _TS('>');
	}

	return false;
}

bool Document::IsDocTypeStart(const TSTR& src, size_t index)
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

bool Document::IsDocTypeEnd(const TSTR& src, size_t index)
{
	if(index < GET_SIZE(src))
	{
		// comparing ">"
		return src[index] == _TS('>');
	}

	return false;
}

bool Document::IsCDataStart(const TSTR& src, size_t index)
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

bool Document::IsCDataEnd(const TSTR& src, size_t index)
{
	if(index + 2 < GET_SIZE(src))
	{
		// comparing "]]>"
		return src[index] == _TS(']') && src[index+1] == _TS(']') && src[index+2] == _TS('>');
	}

	return false;
}

bool Document::IsCommentStart(const TSTR& src, size_t index)
{
	if(index + 3 < GET_SIZE(src))
	{
		// comparing "<!--"
		return src[index] == _TS('<') && src[index+1] == _TS('!') && src[index+2] == _TS('-') && src[index+3] == _TS('-');
	}

	return false;
}

bool Document::IsCommentEnd(const TSTR& src, size_t index)
{
	if(index + 2 < GET_SIZE(src))
	{
		// comparing "-->"
		return src[index] == _TS('-') && src[index+1] == _TS('-') && src[index+2] == _TS('>');
	}

	return false;
}

bool Document::ReadProcessingInstructionValue(const TSTR& src, size_t& index, TSTR& dest, std::map<TSTR, TSTR>& processingInstruction, size_t& newline_cnt)
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

bool Document::ReadDocType(const TSTR& src, size_t& index, TSTR& dest)
{
	dest = _TS("");
	while(IsDocTypeEnd(src, index)==false)
		dest += src[index++];

	index += DocTypeEndLength;

	return true;
}

bool Document::ReadElementName(const TSTR& src, size_t& index, TSTR& dest, AfterElementName& res, size_t& newline_cnt)
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
bool Document::ReadElementValue(const TSTR& src, size_t& index, TSTR& dest, size_t& newline_cnt)
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

bool Document::ReadAttributeName(const TSTR& src, size_t& index, TSTR& dest, size_t& newline_cnt)
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

bool Document::ReadAttributeValue(const TSTR& src, size_t& index, TSTR& dest)
{
	dest = _TS("");
	++index;
	if((src[index]==_TS('\"')&&src[index+1]==_TS('\"'))||(src[index]==_TS('\'')&&src[index+1]==_TS('\'')))
	{
		++index;
		return true;
	}
	while(src[index]!=_TS('\"')&&src[index]!=_TS('\''))
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

bool Document::ReadCDataValue(const TSTR& src, size_t& index, TSTR& dest)
{
	dest = _TS("");
	while(IsCDataEnd(src, index)==false)
		dest += src[index++];

	index += (CDataEndLength-1);

	return true;
}

bool Document::ReadCommentValue(const TSTR& src, size_t& index, TSTR& dest)
{
	dest = _TS("");
	while(IsCommentEnd(src, index)==false)
		dest += src[index++];

	index += (CommentEndLength-1);

	dest = UnescapeXML(dest);

	return true;
}
