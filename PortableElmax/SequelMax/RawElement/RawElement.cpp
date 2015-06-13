#include "RawElement.h"
#include <vector>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "../Utils/StrConv.h"

using namespace SequelMax;

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


