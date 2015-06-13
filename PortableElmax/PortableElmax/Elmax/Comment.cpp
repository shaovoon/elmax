#include "Comment.h"


using namespace Elmax;

Comment::Comment(void)
: m_ptrComment(NULL) 
{
}

Comment::~Comment(void)
{
}

TSTR Comment::GetContent() const
{
	if(!m_ptrComment)
		throw std::runtime_error("Invalid comment object");

	TSTR comment = m_ptrComment->GetContent();

	return comment;
}

size_t Comment::GetLength() const
{
	if(!m_ptrComment)
		throw std::runtime_error("Invalid comment object");

	return m_ptrComment->GetLength();
}

bool Comment::Remove()
{
	if(!m_ptrComment)
		throw std::runtime_error("Invalid comment object");

	m_ptrComment->Remove();

	return true;
}

bool Comment::Update(const TSTR& data)
{
	if(!m_ptrComment)
		throw std::runtime_error("Invalid comment");

	m_ptrComment->SetContent(data);
	return true;
}

bool Comment::IsValid() 
{ 
	if(!m_ptrComment) 
		return false; 
	
	return true;
}
