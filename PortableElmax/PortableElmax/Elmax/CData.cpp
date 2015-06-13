#include "CData.h"

using namespace Elmax;

CData::CData(void)
	: m_ptrCData(NULL) 
{
}

CData::~CData(void)
{
}

TSTR CData::GetContent() const
{
	if(!m_ptrCData)
		throw std::runtime_error("Invalid CData object");

	TSTR data = m_ptrCData->GetContent();
	return data;
}

size_t CData::GetLength() const
{
	if(!m_ptrCData)
		throw std::runtime_error("Invalid CData object");

	return m_ptrCData->GetLength();
}

bool CData::Remove()
{
	if(!m_ptrCData)
		throw std::runtime_error("Invalid CData object");

	m_ptrCData->Remove();

	return true;
}

bool CData::Update(const TSTR& data)
{
	if(!m_ptrCData)
		throw std::runtime_error("Invalid CData object");

	m_ptrCData->SetContent(data);

	return true;
}

bool CData::IsValid() 
{ 
	if(!m_ptrCData) 
		return false; 

	return true;
}
