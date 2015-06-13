#include "RawNode.h"

using namespace Elmax;

RawNode::RawNode(void)
: ptr(NULL)
{
	
}


RawNode::~RawNode(void)
{
}

void RawNode::Discard()
{
	if(ptr!=NULL)
		ptr->Destroy();

	ptr=NULL;
}

void RawNode::Init() 
{
	if(!ptr)
		ptr = new RawTreeNode();
}

ATTR_MAP* RawNode::GetAttrs()
{
	if(ptr)
	{
		return ptr->GetAttrs();
	}
	
	return NULL;
}

RawTreeNode* RawNode::FindRoot()
{
	if(ptr)
	{
		RawTreeNode* tmp = ptr;
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

	return NULL;
}

TSTR RawNode::FindRootName()
{
	RawTreeNode* found = RawNode::FindRoot();

	return found->GetName();
}




