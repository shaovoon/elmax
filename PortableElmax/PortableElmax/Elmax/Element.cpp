#include "Element.h"
#include "../Utils/BoolHexUtil.h"
#include "../Utils/StrConv.h"
#include <cassert>
#include <boost/lexical_cast.hpp>

using namespace Elmax;

Element Element::NullValue;


Element::Element(void)
	: m_strNonExistingParent(_TS(""))
	, m_bDeleted(false)
	, m_bValid(true)
	, m_pRawElement(NULL)
{
}

Element::Element(const TSTR& name)
	: m_strNonExistingParent(_TS(""))
	, m_bDeleted(false)
	, m_strName(name)
	, m_bValid(true)
{
	m_pRawElement = new RawElement(name);
}

// Non-default constructor
Element::Element(RawElement* pRawElement)
{
	if(pRawElement!=NULL)
		m_strName = pRawElement->GetName();
	else
		m_strName = _TS("");
	m_strNonExistingParent = _TS("");
	m_bDeleted=false;

	m_bValid = (pRawElement!=NULL);
	m_pRawElement = pRawElement;
}


// Non-default constructor
Element::Element(
	RawElement* pRawElement,
	const TSTR& nonExistingParent, 
	const TSTR& name, 
	bool bValid)
: m_strNonExistingParent(nonExistingParent)
, m_bDeleted(false)
, m_strName(name)
, m_bValid(bValid)
, m_pRawElement(pRawElement)
{
}

// Copy constructor
Element::Element(const Element& other)
: m_strNonExistingParent(other.m_strNonExistingParent)
, m_bDeleted(other.m_bDeleted)
, m_strName(other.m_strName)
, m_bValid(other.m_bValid)
, m_pRawElement(other.m_pRawElement)
{

}

// Assignment operator
Element& Element::operator=(const Element& other)
{
	m_strNonExistingParent = other.m_strNonExistingParent;
	m_bDeleted = other.m_bDeleted;
	m_strName = other.m_strName;
	m_bValid = other.m_bValid;
	m_pRawElement = other.m_pRawElement;

	return *this;
}

Element::~Element(void)
{
}

TSTR Element::GetRootName()
{
	if(m_pRawElement)
		return m_pRawElement->FindRootName();

	return _TS("");
}

void Element::SetNode(RawElement* ptrElement)
{
	m_pRawElement = ptrElement;
}

void Element::ResolveNullNode(const TSTR& str)
{
	if(m_pRawElement)
		return;

	bool multipleParent = false;
	std::vector<TSTR> vec;
	TSTR temp = str;
	TSTR nonExistingParent = _TS("");
	if(false==IS_EMPTY(m_strNonExistingParent))
	{
		temp = m_strNonExistingParent;
		temp += _TS("|");
		temp += m_strName;
	}
	else
	{
		temp = m_strName;
	}
	SplitString(temp, vec, multipleParent);

	if(multipleParent)
	{
		RawTreeNode* pSrc = m_pRawElement->FindRoot();
				
		for(size_t i=0; i<vec.size(); ++i)
		{
			// Get the collection from this node
			// If successful, assign the found node to this element
			// and find the next element.
			NODE_COLLECTION* nodevec = pSrc->GetVec();
			for(size_t j=0; j<nodevec->size(); ++j)
			{
				RawTreeNode* pNode = nodevec->at(j);
				if(pNode && pNode->GetXmlType()==XML_ELEMENT)
				{
					if(vec.at(i)==pNode->GetName())
					{
						pSrc = pNode;

						if(!m_pRawElement&&vec.at(vec.size()-1)==pNode->GetName())
						{
							m_pRawElement = static_cast<RawElement*>(pNode);
							return;
						}
					}
				}
			}
		}
	}
	else // if(bMultipleParent==false)
	{
		RawTreeNode* pSrc = m_pRawElement->FindRoot();
		NODE_COLLECTION* nodevec = pSrc->GetVec();
		for(size_t j=0; j<nodevec->size(); ++j)
		{
			RawTreeNode* pNode = nodevec->at(j);
			if(pNode)
			{
				if(!m_pRawElement)
				{
					if(str==pNode->GetName())
					{
						pSrc = pNode;
						if(!m_pRawElement&&m_strName==pNode->GetName())
						{
							m_pRawElement = static_cast<RawElement*>(pNode);
							return;
						}
					}
				}
			}
		}
	}
}

void Element::ResolveNode(const TSTR& str)
{
	bool bRoot = false;

	bool multipleParent = false;
	std::vector<TSTR> vec;
	TSTR temp = str;
	TSTR nonExistingParent = _TS("");
	if(false==IS_EMPTY(m_strNonExistingParent))
	{
		temp = m_strNonExistingParent;
		temp += _TS("|");
		temp += m_strName;
	}
	else
	{
		temp = m_strName;
	}
	SplitString(temp, vec, multipleParent);
	if(multipleParent)
	{
		m_strNonExistingParent = _TS("");
		for(size_t i=0; i<vec.size()-1; ++i)
		{
			m_strNonExistingParent += vec.at(i);
			if(i!=vec.size()-2)
				m_strNonExistingParent += _TS("|");
		}
		if(vec.size()>0)
			m_strName = vec.at(vec.size()-1);
	}

	return;
	if(multipleParent)
	{
		RawTreeNode* pSrc = m_pRawElement->FindRoot();

		size_t i=0;
		if(bRoot&&vec.size()>0&&vec.at(0)==pSrc->GetName())
			i = 1;

		bool bFound = false;
		for(; i<vec.size(); ++i)
		{
			// Get the collection from this node
			// If successful, assign the found node to this element
			// and find the next element.
			NODE_COLLECTION* nodevec = pSrc->GetVec();
			size_t len = nodevec->size();
			for(size_t j=0; j<len; ++j)
			{
				RawTreeNode* pNode = (*nodevec)[j];
				if(vec.at(i)==pNode->GetName())
				{
					pSrc = pNode;
				}
			}
			if(bFound==false)
				break;
		}
		if(bFound)
		{
			if(pSrc)
				m_pRawElement = static_cast<RawElement*>(pSrc);
		}
	}
	else // if(bMultipleParent==false)
	{
		RawTreeNode* pSrc = m_pRawElement->FindRoot();
		if(!pSrc)
			return;
		if(bRoot&&vec.size()>0&&vec.at(0)==pSrc->GetName())
			return;

		NODE_COLLECTION* nodevec = pSrc->GetVec();
		size_t len = nodevec->size();
		for(size_t j=0; j<len; ++j)
		{
			RawTreeNode* pNode = (*nodevec)[j];
			if(!m_pRawElement)
			{
				if(str==pNode->GetName())
				{
					pSrc = pNode;
					if(m_strName==pNode->GetName())
					{
						m_pRawElement = static_cast<RawElement*>(pNode);
					}
				}
			}
		}
	}
}

Element Element::GetNodeAt(const TSTR& str)
{
	ResolveNullNode(str);
	bool bMultipleParent = false;
	std::vector<TSTR> vec;
	TSTR temp = str;
	TSTR wstrNonExistingParent = _TS("");
	if(false==IS_EMPTY(m_strNonExistingParent))
	{
		temp = m_strNonExistingParent;
		temp += _TS("|");
		if(IS_EMPTY(m_strName)==false)
		{
			temp += m_strName;
			temp += _TS("|");
		}
		temp += str;
	}
	else
	{
		if(m_pRawElement&&m_strName==m_pRawElement->GetName())
		{
			temp = str;
		}
		else
		{
			if(IS_EMPTY(m_strName)==false)
			{
				temp = m_strName;
				temp += _TS("|");
				temp += str;
			}
			else
				temp = str;
		}
	}
	SplitString(temp, vec, bMultipleParent);

	if(m_pRawElement)
	{
		if(IS_EMPTY(m_strNonExistingParent))
		{
			if(bMultipleParent)
			{
				RawTreeNode* pSrc = m_pRawElement;
				bool found = false;
				size_t i=0;
				//if(m_strName==m_pRawElement->GetName())
				//	i = 1;
				size_t nFound = i;
				for(; i<vec.size(); ++i)
				{
					// Get the collection from this node
					// If successful, assign the found node to this element
					// and find the next element.
					NODE_COLLECTION* nodevec = pSrc->GetVec();
					size_t len = nodevec->size();
					for(size_t j=0; j<len; ++j)
					{
						RawTreeNode* pNode = (*nodevec)[j];
						if(vec.at(i)==pNode->GetName())
						{
							pSrc = pNode;
							found = true;
							++nFound;
							break;
						}
					}
					if(false==found)
					{
						for(;i<vec.size()-1;++i)
						{
							if(IS_EMPTY(wstrNonExistingParent)==false)
								wstrNonExistingParent += _TS("|");

							wstrNonExistingParent += vec.at(i);
						}

						if(vec.empty()==false)
							temp = vec.at(vec.size()-1);

						return Element(static_cast<RawElement*>(pSrc), wstrNonExistingParent, temp, false);
					}
				}
				if(found)
				{
					for(;i<vec.size()-1;++i)
					{
						if(IS_EMPTY(wstrNonExistingParent)==false)
							wstrNonExistingParent += _TS("|");

						wstrNonExistingParent += vec.at(i);
					}

					if(vec.empty()==false)
						temp = vec.at(vec.size()-1);

					bool bValid = false;
					if(nFound==i)
						bValid = true;

					return Element(static_cast<RawElement*>(pSrc), wstrNonExistingParent, temp, bValid);
				}
			}
			else // if(bMultipleParent==false)
			{
				//if(str==m_pRawElement->GetName())
				//	return Element(m_pRawElement, wstrNonExistingParent, str, true);

				RawTreeNode* pSrc = m_pRawElement;
				NODE_COLLECTION* nodevec = pSrc->GetVec();
				size_t len = nodevec->size();
				bool found = false;
				for(size_t j=0; j<len; ++j)
				{
					RawTreeNode* pNode = (*nodevec)[j];

					if(str==pNode->GetName())
					{
						pSrc = pNode;
						found = true;
						break;
					}
				}
				if(false==found)
				{
					if(false==IS_EMPTY(m_strNonExistingParent))
					{
						wstrNonExistingParent = m_strNonExistingParent;
						wstrNonExistingParent += _TS("|");
						wstrNonExistingParent += m_strName;
					}
					else
						wstrNonExistingParent = _TS("");

					return Element(static_cast<RawElement*>(pSrc), wstrNonExistingParent, str, false);
				}
				else // if(found)
				{
					return Element(static_cast<RawElement*>(pSrc), wstrNonExistingParent, str, true);
				}
			}
		}
		else // if(false == m_strNonExistingParent.empty())
		{
			for(size_t i=0;i<vec.size()-1;++i)
			{
				if(IS_EMPTY(wstrNonExistingParent)==false)
					wstrNonExistingParent += _TS("|");

				wstrNonExistingParent += vec.at(i);
			}

			return Element(NULL, wstrNonExistingParent, str, false);
		}
	}
	else
	{
		throw std::runtime_error("No valid xml document and node in this element!");
	}

	return Element();
}

bool Element::SplitString(const TSTR& str, std::vector<TSTR>& vec, bool& bMultipleParent)
{
	vec.clear();
	bMultipleParent = false;

	TSTR temp = str;
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	int size = temp.FindOneOf(_TS("|"));
	if(size!=-1)
	{
		bMultipleParent = true;
	}
	#ifndef ELMAX_DISABLE_FORWARD_BACKWARD_SEPARATOR
		size = temp.FindOneOf(_TS("\\"));
		if(size!=-1)
		{
			bMultipleParent = true;
		}
		size = temp.FindOneOf(_TS("/"));
		if(size!=-1)
		{
			bMultipleParent = true;
		}
	#endif
#else
	size_t size = temp.find_first_of(_TS('|'));
	if(size!=STDSTR::npos)
	{
		bMultipleParent = true;
	}
	#ifndef ELMAX_DISABLE_FORWARD_BACKWARD_SEPARATOR
		size = temp.find_first_of(_TS('\\'));
		if(size!=STDSTR::npos)
		{
			bMultipleParent = true;
		}
		size = temp.find_first_of(_TS('/'));
		if(size!=STDSTR::npos)
		{
			bMultipleParent = true;
		}
	#endif
#endif
	if(bMultipleParent)
	{
#ifdef ELMAX_DISABLE_FORWARD_BACKWARD_SEPARATOR
		_ELCHAR seps[]   = _TS("|");
#else
		_ELCHAR seps[]   = _TS("|/\\");
#endif
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
		token = STRTOK_R(p, seps, &next_token);
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

	if(vec.empty()&&IS_EMPTY(str)==false)
		vec.push_back(str);

	return true;
}

bool Element::SplitNamespace(const TSTR& src, TSTR& wstrName, TSTR& wstrNamespace)
{
	wstrName = src;
	wstrNamespace = _TS("");
	bool bNamespace = false;
	using namespace std;
	TSTR temp = src;
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	int size = temp.FindOneOf(_TS(":"));
	if(size!=-1)
	{
		bNamespace = true;
	}
	else
	{
		wstrName = src;
		return false;
	}
#else
	size_t size = temp.find_first_of(_TS(':'));
	if(size!=STDSTR::npos)
	{
		bNamespace = true;
	}
	else
	{
		wstrName = src;
		return false;
	}
#endif
	if(bNamespace)
	{
		bool bFirstToken = true;
		_ELCHAR seps[]   = _TS(":");
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
			if(bFirstToken)
			{
				wstrNamespace = token;
				bFirstToken = false;
			}
			else
				wstrName = token;
			
			// Get next token
#ifdef _MICROSOFT
			token = STRTOK_S( NULL, seps, &next_token );
#else
	#ifdef _WIN32
			token = STRTOK( NULL, seps);
	#else
			token = STRTOK_R( NULL, seps, &next_token );
	#endif
#endif
		}
		//delete [] p;
	}

	return true;
}

bool Element::Exists() const
{
	if(!m_pRawElement)
		return false;
	else if(false==m_bValid)
		return false;
	else if(GET_SIZE(m_strNonExistingParent)>0)
		return false;

	return true;
}

Element Element::Create(const TSTR& namespaceUri)
{
	ResolveNode(m_strName);
	if(m_pRawElement)
	{
		if(IS_EMPTY(m_strNonExistingParent) && m_strName==m_pRawElement->GetName() && m_bValid)
			return *this;
	}

	using namespace std;
	bool bMultipleParent = false;
	vector<TSTR> vec;
	TSTR wstrNonExistingParent = m_strNonExistingParent;
	wstrNonExistingParent += _TS("|");

	wstrNonExistingParent += m_strName;
	if(wstrNonExistingParent==_TS("|"))
		wstrNonExistingParent=_TS("");

	SplitString(wstrNonExistingParent, vec, bMultipleParent);

	TSTR namespaceUriTemp = _TS("");
	if(false==IS_EMPTY(wstrNonExistingParent))
	{
		if(m_pRawElement)
		{
			for(size_t i=0; i<vec.size(); ++i)
			{
				if(i==vec.size()-1)
					namespaceUriTemp = namespaceUri;

				RawElement* pNew = new RawElement(vec.at(i));
				m_pRawElement->Add(pNew);

				m_pRawElement = pNew;
				m_bValid = true;
			}
			m_bDeleted = false;
			m_strNonExistingParent = _TS("");
		}
		else if(!m_pRawElement)
		{
			for(size_t i=0; i<vec.size(); ++i)
			{
				if(i==vec.size()-1)
					namespaceUriTemp = namespaceUri;
				if(!m_pRawElement)
				{
					m_pRawElement = new RawElement(vec.at(i));

					m_bValid = true;
				}
				else
				{
					RawElement* pNew = new RawElement(vec.at(i));

					if(pNew&&m_pRawElement)
					{
						m_pRawElement->Add(pNew);
						m_pRawElement = pNew;
						m_bValid = true;
					}
				}

			}
			m_bDeleted = false;
			m_strNonExistingParent = _TS("");
		}
		else
			throw std::runtime_error("No valid xml document and node in this element!");
	}
	else // if(wstrNonExistingParent.empty())
	{
		if(m_pRawElement)
		{
			if(m_strName==m_pRawElement->GetName())
				return *this;
			else
			{
				RawElement* pNew = new RawElement(m_strName);

				m_pRawElement->Add(pNew);
				m_pRawElement = pNew;
				m_bValid = true;
				m_bDeleted = false;
				m_strNonExistingParent = _TS("");
			}
		}
		else if(!m_pRawElement)
		{
			m_pRawElement = new RawElement(m_strName);

			m_bValid = true;
		}
		else
		{
			RawElement* pNew = new RawElement(m_strName);

			if(pNew&&m_pRawElement)
			{
				m_pRawElement->Add(pNew);
				m_pRawElement = pNew;

				m_bValid = true;
			}

			m_bDeleted = false;
			m_strNonExistingParent = _TS("");
		}
	}

	return *this;
}

Element Element::CreateNew(const TSTR& namespaceUri)
{
	ResolveNode(m_strName);
	if(false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid)
	{
		return Create(namespaceUri);
	}
	else // if(m_strNonExistingParent.empty())
	{
		if(m_pRawElement)
		{
			RawElement* pNew = new RawElement(m_pRawElement->GetName());

			RawElement* parent = static_cast<RawElement*>(m_pRawElement->GetParent());
			if(parent)
			{
				//RawElement* root = m_pRawElement->FindElementRoot();
				//if (parent != root || (parent == root && !root))
				//{
					parent->Add(pNew);
					m_pRawElement = pNew;

					m_bDeleted = false;
					m_bValid = true;

					return *this;
				//}

				//return Element();
			}
			else
				throw std::runtime_error("No valid parent found!");
		}
		else if(!m_pRawElement)
		{
			m_pRawElement = new RawElement(m_strName);
			m_bValid = true;

			m_bDeleted = false;
			return *this;
		}
		else
			throw std::runtime_error("No valid xml document and node in this element!");
	}

	// will not come here
	throw std::runtime_error("No valid xml document and node in this element!");
	return Element();
}

bool Element::AddNode(Element& node)
{
	if(false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid)
	{
		throw std::runtime_error("Invalid element");
	}

	if(m_pRawElement)
	{
		if(node.m_pRawElement)
		{
			m_pRawElement->Add(node.m_pRawElement);
			node.m_bDeleted = false;
			return true;
		}
		else
			return false;
	}

	throw std::runtime_error("No valid xml document and node in this element!");

	return false;
}

bool Element::RemoveNode(Element& node)
{
	if(false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid||node.m_bDeleted)
	{
		throw std::runtime_error("Invalid element");
	}

	if(m_pRawElement)
	{
		if(node.m_pRawElement)
		{
			node.m_pRawElement->DetachAndDelete();
			node.m_bDeleted = true;
			return true;
		}
		else
			throw std::runtime_error("Invalid child node!");
	}

	throw std::runtime_error("No valid xml document and node in this element!");

	return false;
}

bool Element::Remove()
{
	if(false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid||m_bDeleted)
	{
		throw std::runtime_error("Invalid element");
	}

	if(m_pRawElement)
	{
		RawTreeNode* parent = m_pRawElement->GetParent();
		if(parent)
		{
			this->m_pRawElement->DetachAndDelete();

			this->m_bDeleted = true;
			return true;
		}
		else
			throw std::runtime_error("No valid parent!");
	}
	
	throw std::runtime_error("No valid xml document and node in this element!");
	return false;
}

bool Element::DetachNode(Element& node)
{
	if(false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid||node.m_bDeleted)
	{
		throw std::runtime_error("Invalid element");
	}

	if(m_pRawElement)
	{
		if(node.m_pRawElement)
		{
			node.m_pRawElement->Detach();
			return true;
		}
		else
			throw std::runtime_error("Invalid child node!");
	}

	throw std::runtime_error("No valid xml document and node in this element!");

	return false;
}

bool Element::Detach()
{
	if(false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid||m_bDeleted)
	{
		throw std::runtime_error("Invalid element");
	}

	if(m_pRawElement)
	{
		RawTreeNode* parent = m_pRawElement->GetParent();
		if(parent)
		{
			this->m_pRawElement->Detach();

			return true;
		}
		else
			throw std::runtime_error("No valid parent!");
	}

	throw std::runtime_error("No valid xml document and node in this element!");
	return false;
}

Element::collection_t Element::AsCollection()
{
	if(!m_pRawElement || false == IS_EMPTY(m_strNonExistingParent) || false == m_bValid)
		throw std::runtime_error("Invalid Element");

	collection_t vec;
	ResolveNullNode(m_strName);
	RawTreeNode* parent = m_pRawElement->GetParent();
	if(!parent)
		return vec;

	NODE_COLLECTION* nodevec = parent->GetVec();

	vec.clear();
	size_t len = nodevec->size();
	for(size_t i=0; i<len; ++i)
	{
		if((*nodevec)[i]->GetXmlType()==XML_ELEMENT)
		{
			TSTR name = (*nodevec)[i]->GetName();

			if(name==m_pRawElement->GetName())
			{
				Element ele(static_cast<RawElement*>((*nodevec)[i]), _TS(""), m_strName, true);
				vec.push_back(ele);
			}
		}
	}

	return vec;
}

Element::collection_t Element::GetChildren(const TSTR& name)
{
	if(!m_pRawElement || false == IS_EMPTY(m_strNonExistingParent) || false == m_bValid)
		throw std::runtime_error("Invalid Element");

	collection_t vec;
	ResolveNullNode(m_strName);
	NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

	vec.clear();
	size_t len = nodevec->size();
	for(size_t i=0; i<len; ++i)
	{
		if((*nodevec)[i]->GetXmlType()==XML_ELEMENT)
		{
			TSTR nodename = (*nodevec)[i]->GetName();

			if(nodename==name)
			{
				Element ele(static_cast<RawElement*>((*nodevec)[i]), _TS(""), name, true);
				vec.push_back(ele);
			}
		}
	}

	return vec;
}

ATTR_MAP_COLLECTION* Element::GetAttributeCollection()
{
	if(!m_pRawElement || false == IS_EMPTY(m_strNonExistingParent) || false == m_bValid)
		throw std::runtime_error("Invalid Element");

	return m_pRawElement->GetAttrs()->GetInternalMap();
}

Element::available_child_t Element::QueryChildrenNum()
{
	if(!m_pRawElement || false == IS_EMPTY(m_strNonExistingParent) || false == m_bValid)
		throw std::runtime_error("Invalid Element");

	Element::available_child_t children;
	NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

	size_t len = nodevec->size();

	children.clear();
	for(size_t i=0; i<len; ++i)
	{
		if((*nodevec)[i]->GetXmlType()==XML_ELEMENT)
		{
			TSTR nodename = (*nodevec)[i]->GetName();

			Element::available_child_t::iterator it = children.find(nodename);

			if(it!=children.end())
			{
				size_t n = it->second;
				++n;
				it->second = n;
			}
			else
				children.insert(std::make_pair(nodename,size_t(1)));
		}
	}

	return children;
}

Element Element::operator[](const _ELCHAR* name)
{
	return GetNodeAt(name);
}

bool Element::SetBool(bool val)
{
	TSTR strDest;
	if( BoolHexUtil::SetBool(strDest, val) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Element::SetChar(char val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif

	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetInt16(short val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetInt32(int val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetInt64(ELMAX_INT64 val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUChar(unsigned char val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUInt16(unsigned short val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUInt32(unsigned int val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetUInt64(unsigned ELMAX_INT64 val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetFloat(float val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetDouble(double val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = temp.c_str();
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		std::string temp = boost::lexical_cast<std::string>(val);
		TSTR strDest = StrConv::ConvToWString(temp);
	#else
		std::string strDest = boost::lexical_cast<std::string>(val);
	#endif
#endif
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetString(const TSTR& val)
{
	if(false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid)
	{
		*this = CreateNew();
	}

	if(m_pRawElement)
	{
		m_pRawElement->SetValue(val);
	}
	else
		return false;

	return true;
}

bool Element::SetDate(const Elmax::Date& val)
{
	TSTR strDest = val.GetString();
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetDateTime(const Elmax::DateAndTime& val)
{
	TSTR strDest = val.GetString();
	if(SetString(strDest))
		return true;

	return false;
}

bool Element::SetHex(unsigned int val, bool bAddPrefix)
{
	TSTR strDest;
	if( BoolHexUtil::SetHex(strDest, val, bAddPrefix) )
	{
		if(SetString(strDest))
			return true;
	}

	return false;
}

bool Element::GetString(const TSTR& defaultVal, TSTR& val) const
{
	if(false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid)
		return false;

	if(m_pRawElement)
	{
		val = m_pRawElement->GetValue();
		if(IS_EMPTY(val))
			val = defaultVal;
	}
	else 
		val = defaultVal;
	
	return true;
}

bool Element::GetBool(bool defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	bool val = defaultVal;
	BoolHexUtil::GetBool(src, defaultVal, val);

	return val;
}

char Element::GetChar(char defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	char val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<char>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<char>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<char>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<char>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

short Element::GetInt16(short defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	short val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<short>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<short>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<short>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<short>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

int Element::GetInt32(int defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	int val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<int>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<int>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<int>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<int>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

ELMAX_INT64 Element::GetInt64(ELMAX_INT64 defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	ELMAX_INT64 val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<ELMAX_INT64>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<ELMAX_INT64>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<ELMAX_INT64>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<ELMAX_INT64>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned char Element::GetUChar(unsigned char defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned char val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned char>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned char>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned char>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned char>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned short Element::GetUInt16(unsigned short defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned short val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned short>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned short>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned short>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned short>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned int Element::GetUInt32(unsigned int defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned int val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned int>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned int>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned int>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned int>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned ELMAX_INT64 Element::GetUInt64(unsigned ELMAX_INT64 defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned ELMAX_INT64 val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned ELMAX_INT64>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned ELMAX_INT64>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned ELMAX_INT64>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<unsigned ELMAX_INT64>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

float Element::GetFloat(float defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	float val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<float>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<float>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<float>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<float>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

double Element::GetDouble(double defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	double val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<double>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<double>(GET_CONST_PTR(src));
	#endif
#else
	#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<double>(StrConv::ConvToAString(src));
	#else
		val = boost::lexical_cast<double>(src);
	#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

TSTR Element::GetString(const TSTR& defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	TSTR val = defaultVal;

	if(IS_EMPTY(src)==false)
		val = src;

	return val;
}

Elmax::Date Element::GetDate(const Elmax::Date& defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	Elmax::Date val;
	try
	{
		val.SetString(src);
	}
	catch (...)
	{
		return defaultVal;
	}
	return val;
}

Elmax::DateAndTime Element::GetDateTime(const Elmax::DateAndTime& defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	Elmax::DateAndTime val;
	try
	{
		val.SetString(src);
	}
	catch (...)
	{
		return defaultVal;
	}
	return val;
}

unsigned int Element::ReadHex(unsigned int defaultVal) const
{
	TSTR src;
	if(false==GetString(_TS(""), src))
		return defaultVal;

	unsigned int val = defaultVal;
	BoolHexUtil::ReadHex(src, defaultVal, val);
	return val;
}

bool Element::AddCData(const TSTR& data)
{
	if(!m_pRawElement||false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid)
	{
		throw std::runtime_error("Invalid Element");
	}
	else // if(m_strNonExistingParent.empty())
	{
		if(m_pRawElement)
		{
			RawCData* cdata = new RawCData(data);
			cdata->SetParent(m_pRawElement);
			m_pRawElement->GetVec()->push_back(cdata);

			return true;
		}
	}

	return false;
}

bool Element::DeleteAllCData()
{
	std::vector<CData> vec = GetCDataCollection();

	if(vec.size()==0)
		return false;

	for(size_t i=0; i<vec.size(); ++i)
		vec.at(i).Remove();

	return true;
}

std::vector<CData> Element::GetCDataCollection()
{
	std::vector<CData> vec;
	if(!m_pRawElement||false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid)
		throw std::runtime_error("Invalid Element");

	NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

	vec.clear();
	size_t len = nodevec->size();
	for(size_t j=0; j<len; ++j)
	{
		RawTreeNode* pNode = (*nodevec)[j];
		if(pNode->GetXmlType()==XML_CDATA)
		{
			vec.push_back(CData(static_cast<RawCData*>(pNode)));
		}
	}

	return vec;
}

bool Element::AddComment(const TSTR& comment)
{
	if(!m_pRawElement||false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid)
	{
		throw std::runtime_error("Invalid Element");
	}
	else // if(m_strNonExistingParent.empty())
	{
		if(m_pRawElement)
		{
			RawComment* pComment = new RawComment(comment);
			pComment->SetParent(m_pRawElement);
			m_pRawElement->GetVec()->push_back(pComment);

			return true;
		}
	}

	return false;
}

bool Element::DeleteAllComments()
{
	std::vector<Comment> vec = GetCommentCollection();

	if(vec.size()==0)
		return false;

	for(size_t i=0; i<vec.size(); ++i)
		vec.at(i).Remove();

	return true;
}

std::vector<Comment> Element::GetCommentCollection()
{
	std::vector<Comment> vec;
	if(!m_pRawElement||false==IS_EMPTY(m_strNonExistingParent)||false==m_bValid)
		throw std::runtime_error("Invalid Element");

	if(m_pRawElement)
	{
		NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

		vec.clear();
		size_t len = nodevec->size();
		for(size_t j=0; j<len; ++j)
		{
			RawTreeNode* pNode = (*nodevec)[j];
			if(pNode->GetXmlType()==XML_COMMENT)
			{
				vec.push_back(Comment(static_cast<RawComment*>(pNode)));
			}
		}
	}

	return vec;
}


bool Element::PrettySave(const TSTR& filename, FILE_TYPE fileType, const TSTR& indent)
{
	std::map<TSTR, TSTR> prep;
	prep[_TS("version")] = _TS("1.0");
	SetEncoding(prep, fileType);

	return PrettySave(prep, filename, fileType, indent);
}

bool Element::Save(const TSTR& filename, FILE_TYPE fileType)
{
	std::map<TSTR, TSTR> prep;
	prep[_TS("version")] = _TS("1.0");
	SetEncoding(prep, fileType);

	return Save(prep, filename, fileType);
}

void Element::SetEncoding(std::map<TSTR, TSTR>& prep, FILE_TYPE fileType)
{
	if(fileType==FT_UTF8)
		prep[_TS("encoding")] = _TS("UTF-8");
	else if(fileType==FT_UNICODE)
		prep[_TS("encoding")] = _TS("UTF-16");
	else if(fileType==FT_BEUNICODE)
		prep[_TS("encoding")] = _TS("UTF-16");
	else if(fileType==FT_ASCII)
		prep[_TS("encoding")] = _TS("ASCII");
}

bool Element::PrettySave(std::map<TSTR, TSTR>& processingInstruction, const TSTR& filename, FILE_TYPE fileType, const TSTR& indent)
{
	if(!m_pRawElement)
		return false;

	return m_pRawElement->PrettySave(processingInstruction, filename, fileType, indent);
}

bool Element::Save(std::map<TSTR, TSTR>& processingInstruction, const TSTR& filename, FILE_TYPE fileType)
{
	if(!m_pRawElement)
		return false;

	return m_pRawElement->Save(processingInstruction, filename, fileType);
}

bool Element::ParseXMLString(const TSTR& src)
{
	std::map<TSTR, TSTR> processingInstruction;
	return ParseXMLString(processingInstruction, src);
}

bool Element::ParseXMLString(std::map<TSTR, TSTR>& processingInstruction, const TSTR& src)
{
	if(!m_pRawElement)
	{
		m_pRawElement = new RawElement(); // memory leak if earlier object is not released.
	}

	return m_pRawElement->ParseXMLString(processingInstruction, src);
}

TSTR Element::ToString()
{
	if(!m_pRawElement)
		return _TS("");

	return m_pRawElement->ToString();
}

TSTR Element::ToPrettyString(const TSTR& indent)
{
	if(!m_pRawElement)
		return _TS("");

	return m_pRawElement->ToPrettyString(indent);
}

bool Element::Open(const TSTR& filename)
{
	std::map<TSTR, TSTR> processingInstruction;
	return Open(processingInstruction, filename);
}

bool Element::Open(std::map<TSTR, TSTR>& processingInstruction, const TSTR& filename)
{
	if(!m_pRawElement)
	{
		m_pRawElement = new RawElement(); // memory leak if earlier object is not released.
	}

	return m_pRawElement->Open(processingInstruction, filename);
}

void Element::Destroy()
{
	if(m_pRawElement)
	{
		m_pRawElement->Destroy();
		m_pRawElement = NULL;

		m_strNonExistingParent = _TS("");
		m_bDeleted = true;
		m_strName = _TS("");
		m_bValid = false;
	}
}

// attributes setters and getters
//=================================
bool Element::SetAttrBool(const TSTR& name, bool val)
{
	TSTR strDest;
	if( BoolHexUtil::SetBool(strDest, val) )
	{
		if(SetAttrString(name, strDest))
			return true;
	}

	return false;
}

bool Element::SetAttrChar(const TSTR& name, char val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrInt16(const TSTR& name, short val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrInt32(const TSTR& name, int val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrInt64(const TSTR& name, ELMAX_INT64 val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrUChar(const TSTR& name, unsigned char val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrUInt16(const TSTR& name, unsigned short val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrUInt32(const TSTR& name, unsigned int val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrUInt64(const TSTR& name, unsigned ELMAX_INT64 val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrFloat(const TSTR& name, float val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrDouble(const TSTR& name, double val)
{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = temp.c_str();
#endif
#else
#ifdef ELMAX_USE_UNICODE
	std::string temp = boost::lexical_cast<std::string>(val);
	TSTR strDest = StrConv::ConvToWString(temp);
#else
	std::string strDest = boost::lexical_cast<std::string>(val);
#endif
#endif
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrString(const TSTR& name, const TSTR& val)
{
	if(!m_pRawElement)
		throw std::runtime_error("Invalid element");

	m_pRawElement->GetAttrs()->SetOrAdd(name, val);

	return true;
}

bool Element::SetAttrDate(const TSTR& name, const Elmax::Date& val)
{
	TSTR strDest = val.GetString();
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrDateTime(const TSTR& name, const Elmax::DateAndTime& val)
{
	TSTR strDest = val.GetString();
	if(SetAttrString(name, strDest))
		return true;

	return false;
}

bool Element::SetAttrHex(const TSTR& name, unsigned int val, bool bAddPrefix)
{
	TSTR strDest;
	if( BoolHexUtil::SetHex(strDest, val, bAddPrefix) )
	{
		if(SetAttrString(name, strDest))
			return true;
	}

	return false;
}

bool Element::GetAttrString(const TSTR& name, const TSTR& defaultVal, TSTR& val) const
{
	if(!m_pRawElement)
		throw std::runtime_error("Invalid element!");

	TSTR strValue;
	bool bExists = false;
	GetAttributeAt(name, strValue, bExists);
	if(false==bExists||IS_EMPTY(strValue))
	{
		val = defaultVal;
		return false;
	}

	val = strValue;

	return true;
}

bool Element::GetAttrBool(const TSTR& name, bool defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	bool val = defaultVal;
	BoolHexUtil::GetBool(src, defaultVal, val);
	return val;
}

char Element::GetAttrChar(const TSTR& name, char defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	char val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<char>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<char>(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<char>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<char>(src);
#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

short Element::GetAttrInt16(const TSTR& name, short defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	short val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<short>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<short>(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<short>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<short>(src);
#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

int Element::GetAttrInt32(const TSTR& name, int defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	int val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<int>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<int>(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<int>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<int>(src);
#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

ELMAX_INT64 Element::GetAttrInt64(const TSTR& name, ELMAX_INT64 defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	ELMAX_INT64 val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<ELMAX_INT64>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<ELMAX_INT64>(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<ELMAX_INT64>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<ELMAX_INT64>(src);
#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned char Element::GetAttrUChar(const TSTR& name, unsigned char defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned char val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned char>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<unsigned char>(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned char>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<unsigned char>(src);
#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned short Element::GetAttrUInt16(const TSTR& name, unsigned short defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned short val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned short>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<unsigned short>(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned short>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<unsigned short>(src);
#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned int Element::GetAttrUInt32(const TSTR& name, unsigned int defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned int val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned int>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<unsigned int>(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned int>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<unsigned int>(src);
#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

unsigned ELMAX_INT64 Element::GetAttrUInt64(const TSTR& name, unsigned ELMAX_INT64 defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned ELMAX_INT64 val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned ELMAX_INT64>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<unsigned ELMAX_INT64>(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<unsigned ELMAX_INT64>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<unsigned ELMAX_INT64>(src);
#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

float Element::GetAttrFloat(const TSTR& name, float defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	float val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<float>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<float>(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<float>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<float>(src);
#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

double Element::GetAttrDouble(const TSTR& name, double defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	double val = defaultVal;
	try
	{
#if defined ELMAX_USE_MFC_CSTRING || defined ELMAX_USE_CUSTOM_STRING
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<double>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<double>(GET_CONST_PTR(src));
#endif
#else
#ifdef ELMAX_USE_UNICODE
		val = boost::lexical_cast<double>(StrConv::ConvToAString(src));
#else
		val = boost::lexical_cast<double>(src);
#endif
#endif
	}
	catch (boost::bad_lexical_cast &)
	{
		val = defaultVal;
	}
	return val;
}

TSTR Element::GetAttrString(const TSTR& name, const TSTR& defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	TSTR val = defaultVal;
	if(IS_EMPTY(src)==false)
		val = src;

	return val;
}

Elmax::Date Element::GetAttrDate(const TSTR& name, const Elmax::Date& defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	Elmax::Date val;
	try
	{
		val.SetString(src);
	}
	catch (...)
	{
		return defaultVal;
	}
	return val;
}

Elmax::DateAndTime Element::GetAttrDateTime(const TSTR& name, const Elmax::DateAndTime& defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	Elmax::DateAndTime val;
	try
	{
		val.SetString(src);
	}
	catch (...)
	{
		return defaultVal;
	}
	return val;
}

unsigned int Element::ReadAttrHex(const TSTR& name, unsigned int defaultVal) const
{
	TSTR src;
	if(false==GetAttrString(name, _TS(""), src))
		return defaultVal;

	unsigned int val = defaultVal;
	BoolHexUtil::ReadHex(src, defaultVal, val);
	return val;
}

bool Element::GetAttributeAt(const TSTR& name, TSTR& val, bool& bExists) const
{
	bExists = false;
	if(m_pRawElement)
	{
		ATTR_MAP* attrmap = m_pRawElement->GetAttrs();

		if(attrmap)
		{
			for(size_t i=0; i<attrmap->Count(); ++i)
			{
				std::pair<TSTR, TSTR> pair = attrmap->At(i);
				if(pair.first==name)
				{
					val = pair.second;
					bExists = true;

					return true;
				}
			}
		}
	}

	return false;
}
