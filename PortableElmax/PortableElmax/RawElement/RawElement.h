#pragma once
#include "../Configuration/Configuration.h"
#include "../../FileIO/Common/Enumeration.h"
#include "RawTreeNode.h"
#include <map>
#include <stack>

namespace Elmax
{

enum AfterElementName
{
	None,
	NodeEnded,
	ElementEnded,
	EncounterWhitespace
};

struct stNode
{
	stNode() : ptr(NULL), line_num(0) {}
	stNode(RawTreeNode* p, size_t n) : ptr(p), line_num(n) {}
	RawTreeNode* ptr;
	size_t line_num;
};

class RawElement : public RawTreeNode
{
public:
	~RawElement(void);

	RawElement operator[](const _ELCHAR* name);

	bool Exists() { return GetName() != _TS(""); }

	//! Copy constructor
	RawElement(const RawElement& other);
	//! Assignment operator
	RawElement& operator=(const RawElement& other);

	// Constructors
	RawElement();
	RawElement(const TSTR& name);
	RawElement(const TSTR& name, const TSTR& sValue);
	RawElement Add(RawTreeNode* node1);

	RawElement* FindElementRoot();

	//! Save XML to file
	//!
	//! @param file is file path
	//! @param xmlVersion is the xml version for the processing instruction, eg, _TS("1.0")
	//! @param utf8 specifies it should be saved in utf-8 or utf-16
	//! @param indent is indentation string used, eg _TS("\t")
	bool Save(std::map<TSTR, TSTR>& processingInstruction, const TSTR& file, FILE_TYPE fileType);
	//! Save with the indentation and newlines
	//!
	//! @param file is file path
	//! @param xmlVersion is the xml version for the processing instruction, eg, _TS("1.0")
	//! @param utf8 specifies it should be saved in utf-8 or utf-16
	//! @param indent is indentation string used, eg _TS("\t")
	bool PrettySave(std::map<TSTR, TSTR>& processingInstruction, const TSTR& file, FILE_TYPE fileType, const TSTR& indent = _TS("    "));

	bool Append(RawTreeNode* child);

	bool Open(std::map<TSTR, TSTR>& processingInstruction, const TSTR& file);

	bool ParseXMLString(std::map<TSTR, TSTR>& processingInstruction, const TSTR& src);

	TSTR ToString();
	TSTR ToPrettyString(const TSTR& indent);

	static bool IsValidName(const TSTR& name);

	static void FormatProcessingInstruction(const std::map<TSTR, TSTR>& processingInstruction, TSTR& dest);


private:

	//! Find the child with this chained names (eg, _TS("MyElement|MyChild"))
	RawElement Find(const TSTR& names);
	//! Find the 1st child with this name
	RawElement FindFirstChild(const TSTR& name);

	//! Write indentation to unicode file
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param indent is indentation string used, eg _TS("\t")
	static bool WriteIndent(TEXT_WRITER& uf, size_t cnt, const TSTR& indent);

	//! Write start element (eg, <element>) to unicode file
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param elementName is the element name
	//! @param indent is indentation string used, eg _TS("\t")
	static bool WriteStartElement(TEXT_WRITER& uf, size_t cnt, const TSTR& elementName, const TSTR& indent);

	//! Write end element (eg, </element>) to unicode file
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param elementName is the element name
	//! @param indent is indentation string used, eg _TS("\t")
	static bool WriteEndElement(TEXT_WRITER& uf, size_t cnt, const TSTR& elementName, const TSTR& indent);
	//! Write indentation to unicode file
	//!
	//! @param uf is the destination string that is written
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param indent is indentation string used, eg _TS("\t")
	static bool WriteIndent(TSTR& uf, size_t cnt, const TSTR& indent);

	//! Write start element (eg, <element>) to unicode file
	//!
	//! @param uf is the destination string that is written
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param elementName is the element name
	//! @param indent is indentation string used, eg _TS("\t")
	static bool WriteStartElement(TSTR& uf, size_t cnt, const TSTR& elementName, const TSTR& indent);

	//! Write end element (eg, </element>) to unicode file
	//!
	//! @param uf is the destination string that is written
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param elementName is the element name
	//! @param indent is indentation string used, eg _TS("\t")
	static bool WriteEndElement(TSTR& uf, size_t cnt, const TSTR& elementName, const TSTR& indent);

	//! Traverse the tree recursively and write them to file prettily.
	//!
	//! @param node is the xml tree node
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param indent is indentation string used, eg _TS("\t")
	static bool PrettyTraverse(RawTreeNode& node, TEXT_WRITER& uf, size_t cnt, const TSTR& indent);

	//! Traverse the tree recursively and write them to file prettily.
	//!
	//! @param uf is the destination string that is written
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param cnt is the number of indentation should be written
	//! @param indent is indentation string used, eg _TS("\t")
	static bool PrettyTraverse(RawTreeNode& node, TSTR& uf, size_t cnt, const TSTR& indent);

	//! Write start element (eg, <element>) to unicode file without indentation.
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param elementName is the element name
	static bool WriteStartElement(TEXT_WRITER& uf, const TSTR& elementName);

	//! Write end element (eg, </element>) to unicode file without indentation.
	//!
	//! @param uf is the opened unicode file
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param elementName is the element name
	static bool WriteEndElement(TEXT_WRITER& uf, const TSTR& elementName);
	//! Write start element (eg, <element>) to unicode file without indentation.
	//!
	//! @param uf is the destination string that is written
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param elementName is the element name
	static bool WriteStartElement(TSTR& uf, const TSTR& elementName);

	//! Write end element (eg, </element>) to unicode file without indentation.
	//!
	//! @param uf is the destination string that is written
	//! @param utf8 specifies it should be written in utf-8 or utf-16
	//! @param elementName is the element name
	static bool WriteEndElement(TSTR& uf, const TSTR& elementName);

	//! Traverse the tree recursively and write them to file without indentation.
	//!
	//! @param node is the xml tree node
	//! @param uf is the opened unicode file
	static bool Traverse(RawTreeNode& node, TEXT_WRITER& uf);
	//! Traverse the tree recursively and write them to file without indentation.
	//!
	//! @param node is the xml tree node
	//! @param uf is the destination string that is written
	static bool Traverse(RawTreeNode& node, TSTR& uf);

	//! Replace all the anchor string instance found in the fmtstr string with another string
	static TSTR Replace( 
		const TSTR& fmtstr, 
		const TSTR& anchor,
		const TSTR& replace );

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

	//! Escape the XML string(eg, "<>" to "&lt;&gt;")
	static TSTR EscapeXML(const TSTR& fmtstr);

	//! Escape the XML string(eg, "&lt;&gt;" to "<>")
	static TSTR UnescapeXML(const TSTR& fmtstr);

	static void PrintStack(size_t pos, size_t line,const std::string& error, std::stack<stNode>& StackElement);


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

};

} // ns Elmax

