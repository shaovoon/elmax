#pragma once

#include "../RawElement/RawComment.h"

namespace Elmax
{
//! Class to access XML comment
class Comment
{
friend class Element;
private:
	//! Constructor
	Comment(void);
	//! Non-default Constructor
	Comment(RawComment* ptrComment) : m_ptrComment(ptrComment) {};

public:
#if _HAS_CPP0X
	//! Copy Constructor
	Comment(Comment& other) : m_ptrComment(other.m_ptrComment) {};
#endif
	//! Destructor
	~Comment(void);

	//! Get the Comment data
	TSTR GetContent() const;
	//! Get the length of the Comment in _ELCHAR size
	size_t GetLength() const;
	//! Remove itself
	bool Remove();
	//! Update the Comment
	bool Update(const TSTR& comment);
	//! Is valid?
	bool IsValid();

private:
	//! Comment object
	RawComment* m_ptrComment;
};

} // ns Elmax