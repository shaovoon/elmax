#pragma once
#include "../Configuration/Configuration.h"
#include <map>
#include <stack>
#ifdef ELMAX_USE_BOOST_FUNC
#	include <boost/function.hpp>
#else
#	include <functional>
#endif
#include "Element.h"
#include "StringStack.h"

enum AfterElementName
{
	None,
	NodeEnded,
	ElementEnded,
	EncounterWhitespace
};

class Document
{
public:
	Document(void);
	~Document(void);

	bool Open(const TSTR& file);

	bool Open(std::map<TSTR, TSTR>& processingInstruction, const TSTR& file);

	bool ParseXMLString(std::map<TSTR, TSTR>& processingInstruction, const TSTR& src);

#ifdef ELMAX_USE_BOOST_FUNC
	void RegisterProcessingInstructionFunctor(boost::function<void(const TSTR&, const TSTR&)> f);
	void RegisterStartElementFunctor(const TSTR& elems, boost::function<void(SequelMax::Element&)> f);
	void RegisterEndElementFunctor(const TSTR& elems, boost::function<void(const TSTR&)> f);
	void RegisterCommentFunctor(const TSTR& elems, boost::function<void(const TSTR&)> f);
	void RegisterCDataFunctor(const TSTR& elems, boost::function<void(const TSTR&)> f);
#else
	void RegisterProcessingInstructionFunctor(std::function<void(const TSTR&, const TSTR&)> f);
	void RegisterStartElementFunctor(const TSTR& elems, std::function<void(SequelMax::Element&)> f);
	void RegisterEndElementFunctor(const TSTR& elems, std::function<void(const TSTR&)> f);
	void RegisterCommentFunctor(const TSTR& elems, std::function<void(const TSTR&)> f);
	void RegisterCDataFunctor(const TSTR& elems, std::function<void(const TSTR&)> f);
#endif

private:
	static bool IsContent(const TSTR& src, size_t index);
	static bool IsWhitespace(const TSTR& src, size_t& newline_cnt);
	static bool IsWhitespace(const TSTR& src, size_t index, size_t& newline_cnt);
	static bool IsWhitespace(_ELCHAR ch, size_t& newline_cnt);
	static bool IsStartElementEnd(const TSTR& src, size_t index);
	static bool IsEndElementStart(const TSTR& src, size_t index);
	static bool IsProcessingInstructionStart(const TSTR& src, size_t index);
	static bool IsProcessingInstructionEnd(const TSTR& src, size_t index);
	static bool IsDocTypeStart(const TSTR& src, size_t index);
	static bool IsDocTypeEnd(const TSTR& src, size_t index);
	static bool IsCDataStart(const TSTR& src, size_t index);
	static bool IsCDataEnd(const TSTR& src, size_t index);
	static bool IsCommentStart(const TSTR& src, size_t index);
	static bool IsCommentEnd(const TSTR& src, size_t index);

	static bool ReadProcessingInstructionValue(const TSTR& src, size_t& index, TSTR& dest, std::map<TSTR, TSTR>& processingInstruction, size_t& newline_cnt);
	static bool ReadDocType(const TSTR& src, size_t& index, TSTR& dest);
	static bool ReadElementName(const TSTR& src, size_t& index, TSTR& dest, AfterElementName& res, size_t& newline_cnt);
	static bool ReadElementValue(const TSTR& src, size_t& index, TSTR& dest, size_t& newline_cnt);
	static bool ReadAttributeName(const TSTR& src, size_t& index, TSTR& dest, size_t& newline_cnt);
	static bool ReadAttributeValue(const TSTR& src, size_t& index, TSTR& dest);

	static bool ReadCDataValue(const TSTR& src, size_t& index, TSTR& dest);
	static bool ReadCommentValue(const TSTR& src, size_t& index, TSTR& dest);

	static TSTR Replace(const TSTR& fmtstr, const TSTR& anchor, const TSTR& replace );
	//! Escape the XML string(eg, "&lt;&gt;" to "<>")
	static TSTR UnescapeXML(const TSTR& fmtstr);

	static void PrintStack(size_t pos, size_t line,const std::string& error, StringStack& StackElement, std::stack<size_t>& StackLineNum);

	static const size_t StartElementEndLength;
	static const size_t EndElementStartLength;
	static const size_t ProcessingInstructionStartLength;
	static const size_t ProcessingInstructionEndLength;
	static const size_t DocTypeStartLength;
	static const size_t DocTypeEndLength;
	static const size_t CDataStartLength;
	static const size_t CDataEndLength;
	static const size_t CommentStartLength;
	static const size_t CommentEndLength;

#ifdef ELMAX_USE_BOOST_FUNC
	boost::function<void(const TSTR&, const TSTR&)> PreprocessFunctor;
	std::map<TSTR, boost::function<void(SequelMax::Element&)> > map_StartElemFunctor;
	std::map<TSTR, boost::function<void(const TSTR&)> > map_EndElemFunctor;
	std::map<TSTR, boost::function<void(const TSTR&)> > map_CommentFunctor;
	std::map<TSTR, boost::function<void(const TSTR&)> > map_CDataFunctor;
#else
	std::function<void(const TSTR&, const TSTR&)> PreprocessFunctor;
	std::map<TSTR, std::function<void(SequelMax::Element&)> > map_StartElemFunctor;
	std::map<TSTR, std::function<void(const TSTR&)> > map_EndElemFunctor;
	std::map<TSTR, std::function<void(const TSTR&)> > map_CommentFunctor;
	std::map<TSTR, std::function<void(const TSTR&)> > map_CDataFunctor;
#endif

};

