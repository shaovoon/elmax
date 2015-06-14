#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

#include "../Configuration/Configuration.h"
#include "CData.h"
#include "Comment.h"
#include "Date.h"
#include "DateAndTime.h"
#include "../RawElement/RawElement.h"
#include "../../FileIO/Common/Enumeration.h"

namespace Elmax
{
	//! Contains information about xml element
	class Element
	{
	public:
		//! Constructor
		Element(void);
		//! Non-default Constructor
		Element(const TSTR& name);
		// to be used in inplace sort prediate to wrap the RawElement pointers in Element object for better processing
		Element(RawElement* pRawElement);

		//! Copy constructor
		Element(const Element& other);
		//! Assignment operator
		Element& operator=(const Element& other);

		//! Destructor
		virtual ~Element(void);

		class Iterator
		{
		public:
			Iterator(void) // create null object
				: _name(_TS("")), _parent(NULL), index(0), ptr(NULL) {}

			// copy constructor
			Iterator(const Iterator& other)
				: _name(other._name), _parent(other._parent), index(other.index), ptr(other.ptr) {}

			Iterator(const TSTR& name, RawTreeNode* parent)
				: _name(name), _parent(parent), index(0), ptr(NULL)
			{
				if (_parent != NULL)
				{
					NODE_COLLECTION* pColl = _parent->GetVec();
					size_t size = pColl->size();
					while (index < size)
					{
						if ((*pColl)[index]->GetXmlType() == XML_ELEMENT)
						{
							if ((*pColl)[index]->GetName() == _name || _name == _TS("*"))
							{
								ptr = (*pColl)[index];
								return;
							}
						}
						++index;
					}

					if (index >= size)
						ptr = NULL;
				}
				else
					ptr = NULL;
			};
			~Iterator(void) {};

			RawTreeNode* GetPtr() const
			{
				return ptr;
			}
			// copy constructor
			Iterator operator=(const Iterator& other)
			{
				_name = other._name;
				_parent = other._parent;
				index = other.index;
				ptr = other.ptr;
			}

			operator Element()
			{
				return Element((RawElement*) (ptr));
			}

			void operator ++()
			{
				if (_parent != NULL)
				{
					++index;
					NODE_COLLECTION* pColl = _parent->GetVec();
					size_t size = pColl->size();
					while (index < size)
					{
						if ((*pColl)[index]->GetXmlType() == XML_ELEMENT)
						{
							if ((*pColl)[index]->GetName() == _name || _name == _TS("*"))
							{
								ptr = (*pColl)[index];
								return;
							}
						}
						++index;
					}

					if (index >= size)
						ptr = NULL;
				}
				else
					ptr = NULL;
			}
			Element operator *()
			{
				if (ptr == NULL)
				{
					throw std::runtime_error("Null element iterator");
					return Element();
				}

				return Element((RawElement*) (ptr));
			}

			bool operator!=(const Element::Iterator& other) const
			{
				return this->GetPtr() != other.GetPtr();
			}

			bool operator==(const Element::Iterator& other) const
			{
				return this->GetPtr() == other.GetPtr();
			}

		private:
			TSTR _name;
			RawTreeNode* _parent;
			size_t index;
			RawTreeNode* ptr;
		}; // end of Iterator class


		//! Set the internal node object
		void SetNode(RawElement* pRawElement);
		//! Get the root name (to access the root)
		TSTR GetRootName();
		//! Get the element name
		TSTR GetName() { if (m_pRawElement) return m_pRawElement->GetName(); return _TS(""); }

		//! Returns true if the attribute with the name exists.
		bool Exists() const;
		//! Always create this child element with this optional namespaceUri
		Element Create(const TSTR& name, const TSTR& namespaceUri = _TS(""));
		//! Add this node as child node
		bool AddNode(Element& node);
		//! Delete this child node (node cannot be reused)
		bool RemoveNode(Element& node);
		//! Delete this node (node cannot be reused)
		bool Remove();

		//! Delete this child node (node cannot be reused)
		bool DetachNode(Element& node);
		//! Delete this node (node cannot be reused)
		bool Detach();

		bool PrettySave(const TSTR& filename, FILE_TYPE fileType, const TSTR& indent);
		bool Save(const TSTR& filename, FILE_TYPE fileType);

		bool PrettySave(std::map<TSTR, TSTR>& processingInstruction, const TSTR& filename, FILE_TYPE fileType, const TSTR& indent);
		bool Save(std::map<TSTR, TSTR>& processingInstruction, const TSTR& filename, FILE_TYPE fileType);

		bool ParseXMLString(const TSTR& src);
		bool ParseXMLString(std::map<TSTR, TSTR>& processingInstruction, const TSTR& src);

		TSTR ToString();
		TSTR ToPrettyString(const TSTR& indent);


		void Destroy();
		bool Open(const TSTR& filename);
		bool Open(std::map<TSTR, TSTR>& processingInstruction, const TSTR& filename);


		//! type of element vector
		typedef std::vector< Element > collection_t;
		//! Get the collection of sibling elements with the same name
		collection_t AsCollection();
		//! Get the collection of sibling elements with the same name which satisfy the boolean predicate
		//! Note: template functions has to be in the header file, not cpp file.
		template<typename Predicate>
		collection_t AsCollection(Predicate pred)
		{
			if (!m_pRawElement)
				throw std::runtime_error("Invalid Element");

			collection_t vec;
			RawElement* parent = static_cast<RawElement*>(m_pRawElement->GetParent());
			if (!parent)
				return vec;
			NODE_COLLECTION* nodevec = parent->GetVec();

			vec.clear();
			size_t len = nodevec->size();
			for (size_t i = 0; i < len; ++i)
			{
				if ((*nodevec)[i]->GetXmlType() == XML_ELEMENT)
				{
					TSTR name = (*nodevec)[i]->GetName();

					if (name == m_pRawElement->GetName())
					{
						Element ele(static_cast<RawElement*>((*nodevec)[i]));
						if (pred(ele))
							vec.push_back(ele);
					}
				}
			}

			return vec;
		}


		//! Get the collection of child elements with same name in vec
		collection_t GetChildren(const TSTR& name);

		ATTR_MAP_COLLECTION* GetAttributeCollection();

		//! Get the collection of child elements with same name in vec, which satisfy the boolean predicate
		//! Note: template functions has to be in the header file, not cpp file.
		template<typename Predicate>
		collection_t Filter(const TSTR& name, Predicate pred)
		{
			if (!m_pRawElement)
				throw std::runtime_error("Invalid Element");

			collection_t vec;
			NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

			vec.clear();
			size_t len = nodevec->size();
			for (size_t i = 0; i < len; ++i)
			{
				if ((*nodevec)[i]->GetXmlType() == XML_ELEMENT)
				{
					TSTR nodename = (*nodevec)[i]->GetName();

					if (nodename == name)
					{
						Element ele(static_cast<RawElement*>((*nodevec)[i]));
						if (pred(ele))
							vec.push_back(ele);
					}
				}
			}

			return vec;
		};

		template<typename Predicate>
		collection_t Sort(const TSTR& name, Predicate predSort) // Note: not an in-place sort!
		{
			if (!m_pRawElement)
				throw std::runtime_error("Invalid Element");

			collection_t vec;
			NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

			vec.clear();
			size_t len = nodevec->size();
			for (size_t i = 0; i < len; ++i)
			{
				if ((*nodevec)[i]->GetXmlType() == XML_ELEMENT)
				{
					TSTR nodename = (*nodevec)[i]->GetName();

					if (nodename == name)
					{
						Element ele(static_cast<RawElement*>((*nodevec)[i]));
						vec.push_back(ele);
					}
				}
			}

			std::sort(vec.begin(), vec.end(), predSort);
			return vec;
		};

		template<typename Predicate>
		void InplaceSort(Predicate predSort) // Note: not an in-place sort!
		{
			if (!m_pRawElement)
				throw std::runtime_error("Invalid Element");

			NODE_COLLECTION* nodevec = m_pRawElement->GetVec();

			std::sort(nodevec->begin(), nodevec->end(), predSort);
		};

		template<typename Predicate>
		size_t Count(const TSTR& name, Predicate pred) // for SQL Count function.
		{
			collection_t vec = Filter(name, pred);

			return vec.size();
		};

		typedef std::map< TSTR, size_t > available_child_t;
		//! Query number of children for each Element name
		available_child_t QueryChildrenNum();

		Iterator Begin(const TSTR& search) // "*" means get all
		{
			Iterator it(search, (RawTreeNode*) (m_pRawElement));
			return it;
		}
		Iterator End()
		{
			static Iterator ItEnd;
			return ItEnd;
		}

		// CData access methods
		//========================
		//! Add this CDataSection with data
		bool AddCData(const TSTR& data);
		//! Delete this CDataSection at this index
		bool DeleteCData(size_t index);
		//! Delete this CDataSection at this index
		bool DeleteAllCData();
		//! Get this CDataSection collection
		std::vector<CData> GetCDataCollection();

		// Comment access methods
		//==========================
		//! Add this Comment object with this comment string
		bool AddComment(const TSTR& comment);
		//! Delete this Comment at this index
		bool DeleteComment(size_t index);
		//! Delete this Comment at this index
		bool DeleteAllComments();
		//! Get this Comment collection
		std::vector<Comment> GetCommentCollection();

		Element operator[](const _ELCHAR* name) const;

		bool SetBool(bool val);
		bool SetChar(char val);
		bool SetInt16(short val);
		bool SetInt32(int val);
		bool SetInt64(ELMAX_INT64 val);
		bool SetUChar(unsigned char val);
		bool SetUInt16(unsigned short val);
		bool SetUInt32(unsigned int val);
		bool SetUInt64(unsigned ELMAX_INT64 val);
		bool SetFloat(float val);
		bool SetDouble(double val);
		bool SetString(const TSTR& val);
		bool SetDate(const Elmax::Date& val);
		bool SetDateTime(const Elmax::DateAndTime& val);
		bool SetHex(unsigned int val, bool bAddPrefix = false);

		bool GetBool(bool defaultVal) const;
		char GetChar(char defaultVal) const;
		short GetInt16(short defaultVal) const;
		int GetInt32(int defaultVal) const;
		ELMAX_INT64 GetInt64(ELMAX_INT64 defaultVal) const;
		unsigned char GetUChar(unsigned char defaultVal) const;
		unsigned short GetUInt16(unsigned short defaultVal) const;
		unsigned int GetUInt32(unsigned int defaultVal) const;
		unsigned ELMAX_INT64 GetUInt64(unsigned ELMAX_INT64 defaultVal) const;
		float GetFloat(float defaultVal) const;
		double GetDouble(double defaultVal) const;
		TSTR GetString(const TSTR& defaultVal = _TS("")) const;
		Elmax::Date GetDate(const Elmax::Date& defaultVal) const;
		Elmax::DateAndTime GetDateTime(const Elmax::DateAndTime& defaultVal) const;
		unsigned int ReadHex(unsigned int defaultVal) const;

		// attributes setters and getters
		//=================================
		bool SetAttrBool(const TSTR& name, bool val);
		bool SetAttrChar(const TSTR& name, char val);
		bool SetAttrInt16(const TSTR& name, short val);
		bool SetAttrInt32(const TSTR& name, int val);
		bool SetAttrInt64(const TSTR& name, ELMAX_INT64 val);
		bool SetAttrUChar(const TSTR& name, unsigned char val);
		bool SetAttrUInt16(const TSTR& name, unsigned short val);
		bool SetAttrUInt32(const TSTR& name, unsigned int val);
		bool SetAttrUInt64(const TSTR& name, unsigned ELMAX_INT64 val);
		bool SetAttrFloat(const TSTR& name, float val);
		bool SetAttrDouble(const TSTR& name, double val);
		bool SetAttrString(const TSTR& name, const TSTR& val);
		bool SetAttrDate(const TSTR& name, const Elmax::Date& val);
		bool SetAttrDateTime(const TSTR& name, const Elmax::DateAndTime& val);
		//! Set the unsigned 32bit integer into hexadecimal string value
		//!
		//! @param val is the source unsigned 32bit integer value to convert from
		//! @param val bAddPrefix indicates whether to add the "0x" prefix
		bool SetAttrHex(const TSTR& name, unsigned int val, bool bAddPrefix = false);


		bool GetAttrBool(const TSTR& name, bool defaultVal) const;
		char GetAttrChar(const TSTR& name, char defaultVal) const;
		short GetAttrInt16(const TSTR& name, short defaultVal) const;
		int GetAttrInt32(const TSTR& name, int defaultVal) const;
		ELMAX_INT64 GetAttrInt64(const TSTR& name, ELMAX_INT64 defaultVal) const;
		unsigned char GetAttrUChar(const TSTR& name, unsigned char defaultVal) const;
		unsigned short GetAttrUInt16(const TSTR& name, unsigned short defaultVal) const;
		unsigned int GetAttrUInt32(const TSTR& name, unsigned int defaultVal) const;
		unsigned ELMAX_INT64 GetAttrUInt64(const TSTR& name, unsigned ELMAX_INT64 defaultVal) const;
		float GetAttrFloat(const TSTR& name, float defaultVal) const;
		double GetAttrDouble(const TSTR& name, double defaultVal) const;
		TSTR GetAttrString(const TSTR& name, const TSTR& defaultVal) const;
		Elmax::Date GetAttrDate(const TSTR& name, const Elmax::Date& defaultVal) const;
		Elmax::DateAndTime GetAttrDateTime(const TSTR& name, const Elmax::DateAndTime& defaultVal) const;
		unsigned int ReadAttrHex(const TSTR& name, unsigned int defaultVal) const;


	private:
		//! Split the str(ing) with delimiter "|/\\" into vec
		//!
		//! @param bMultipleParent returns true if there are more than 1 item in vec
		static bool SplitString(const TSTR& str, std::vector<TSTR>& vec, bool& bMultipleParent);
		//! Get Element with this str name
		Element GetNodeAt(const TSTR& str) const;
		//! Split the src with delimiter ":" into wstrNamespace and wstrName
		static bool SplitNamespace(const TSTR& src, TSTR& wstrName, TSTR& wstrNamespace);
		//! Get the attribute value
		//!
		//! @param defaultVal is the default string value to use if src is invalid or empty
		//! @param val is the string value to be returned
		bool GetString(const TSTR& defaultVal, TSTR& val) const;
		void SetEncoding(std::map<TSTR, TSTR>& prep, FILE_TYPE fileType);

		bool GetAttrString(const TSTR& name, const TSTR& defaultVal, TSTR& val) const;
		bool GetAttributeAt(const TSTR& wstrName, TSTR& wstrValue, bool& bExists) const;

	protected:
		RawElement* m_pRawElement;

	public:
		static Element NullValue;

	};

	class RootElement : public Element
	{
	public:
		//! Constructor
		RootElement(void) {};
		//! Non-default Constructor
		RootElement(const TSTR& name) : Element(name) {}
		~RootElement(void) { Destroy(); }
	};

} // ns Elmax
