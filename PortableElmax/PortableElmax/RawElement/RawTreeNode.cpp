#include "RawTreeNode.h"

using namespace Elmax;

RawTreeNode::RawTreeNode(void)
	:pVec(NULL)
	,pAttrs(NULL)
	,Name(_TS(""))
	,Value(_TS(""))
	,xmltype(XML_NONE)
	,parent(NULL)
{
}

RawTreeNode::~RawTreeNode(void)
{
}

void RawTreeNode::Destroy()
{
	if(pVec!=NULL)
	{
		for(size_t i=0;i<pVec->size();++i)
			pVec->at(i)->Destroy();

		pVec->clear();

		delete pVec;
		pVec = NULL;
	}

	if(pAttrs != NULL)
	{
		delete pAttrs;
		pAttrs = NULL;
	}

	delete this;
}

void RawTreeNode::DetachAndDelete()
{
	if(parent&&parent->pVec)
	{
		// remove
		std::vector<RawTreeNode*>* vec = parent->pVec;
		std::vector<RawTreeNode*>::iterator it = vec->begin();

		for(; it != vec->end(); ++it)
		{
			if(this == *it)
			{
				vec->erase(it);
				break;
			}
		}

		Destroy();
	}
}

void RawTreeNode::Detach()
{
	if(parent&&parent->pVec)
	{
		// remove
		std::vector<RawTreeNode*>* vec = parent->pVec;
		std::vector<RawTreeNode*>::iterator it = vec->begin();

		for(; it != vec->end(); ++it)
		{
			if(this == *it)
			{
				vec->erase(it);
				break;
			}
		}

		SetParent(NULL);
	}
}

void RawTreeNode::AddChild(RawTreeNode* pChild)
{
	if(pVec==NULL)
		pVec = new NODE_COLLECTION();

	pChild->SetParent(this);
	pVec->push_back(pChild);
}

TSTR RawTreeNode::GetName()
{
	return Name;
}

TSTR RawTreeNode::GetValue()
{
	return Value;
}

void RawTreeNode::SetName(const TSTR& name)
{
	Name = name;
}

void RawTreeNode::SetValue(const TSTR& val)
{
	Value = val;
}

NODE_COLLECTION* RawTreeNode::GetVec()
{
	if(pVec==NULL)
		pVec = new NODE_COLLECTION();

	return pVec;
}

ATTR_MAP* RawTreeNode::GetAttrs()
{
	if(!pAttrs)
		pAttrs = new ATTR_MAP();

	return pAttrs;
}

size_t RawTreeNode::GetAttrCount()
{
	if(!pAttrs)
		return 0;

	return pAttrs->Count();
}

XMLTYPE RawTreeNode::GetXmlType()
{
	return xmltype;
}

void RawTreeNode::SetXmlType(XMLTYPE type)
{
	xmltype = type;
}

RawTreeNode* RawTreeNode::FindRoot()
{
	RawTreeNode* tmp = this;
	RawTreeNode* found = NULL;

	while(true)
	{
		if(tmp->parent!=NULL)
			tmp = tmp->parent;
		else
		{
			found = tmp;
			break;
		}
	}

	return found;
}

TSTR RawTreeNode::FindRootName()
{
	RawTreeNode* found = FindRoot();

	return found->GetName();
}

void RawTreeNode::Discard()
{
	this->Destroy();
}

RawTreeNode* RawTreeNode::GetParent()
{
	return parent;
}

void RawTreeNode::SetParent(RawTreeNode* p)
{
	parent = p;
}

