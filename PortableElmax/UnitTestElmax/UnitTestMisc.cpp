#include "stdafx.h"
#include "CppUnitTest.h"
#include "../PortableElmax/Elmax.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestElmax
{
	TEST_CLASS(UnitTestMisc)
	{
	private:

		TSTR GetFolderPath()
		{
			return _TS("c:\\temp\\");
		}

	public:
		
		TEST_METHOD(TestDateAndTime)
		{
			using namespace Elmax;
			DateAndTime date(2007, 1, 1, 14, 23, 00);

			Assert::IsTrue(TSTR(_TS("2007-01-01 14:23:00")) == date.GetString());

			date.SetDateTime(2007, 12, 15, 2, 25, 59);

			Assert::IsTrue(TSTR(_TS("2007-12-15 02:25:59")) == date.GetString());

			date.SetString(_TS("2008-08-21 12:00:00"));
			Assert::AreEqual((short)(2008), date.GetYear());
			Assert::AreEqual((short)(8), date.GetMonth());
			Assert::AreEqual((short)(21), date.GetMonthDay());
			Assert::AreEqual((short)(12), date.GetHour());
			Assert::AreEqual((short)(0), date.GetMinute());
			Assert::AreEqual((short)(0), date.GetSecond());
		}
		TEST_METHOD(TestDate)
		{
			using namespace Elmax;
			Date date(2007, 1, 1);

			Assert::IsTrue(date.GetString() == TSTR(_TS("2007-01-01")));

			date.SetDate(2007, 12, 15);
			Assert::IsTrue(date.GetString() == TSTR(_TS("2007-12-15")));

			date.SetString(_TS("2008-08-21"));
			Assert::AreEqual(date.GetYear(), (short)(2008));
			Assert::AreEqual(date.GetMonth(), (short)(8));
			Assert::AreEqual(date.GetMonthDay(), (short)(21));
		}
		TEST_METHOD(QueryChildrenNum1)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("qq"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);
			Element elem4 = elembb.Create(_TS("qq"));
			elem4.SetInt32(44);
			Element elem5 = elembb.Create(_TS("cc"));
			elem5.SetInt32(55);

			Element::available_child_t acmap = root[_TS("bb")].QueryChildrenNum();

			Assert::AreEqual(acmap[_TS("cc")], (size_t)(3));
			Assert::AreEqual(acmap[_TS("qq")], (size_t)(2));

			TSTR file = GetFolderPath() + _TS("QueryChildrenNum1.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("QueryChildrenNum1Check.xml"), FT_UTF8);

			Element::available_child_t acmap2 = root2[_TS("bb")].QueryChildrenNum();

			Assert::AreEqual(acmap2[_TS("cc")], (size_t)(3));
			Assert::AreEqual(acmap2[_TS("qq")], (size_t)(2));
		}
		TEST_METHOD(QueryChildrenNum2)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("qq"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);
			Element elem4 = elembb.Create(_TS("qq"));
			elem4.SetInt32(44);
			Element elem5 = elembb.Create(_TS("cc"));
			elem5.SetInt32(55);

			Element::available_child_t acmap = root[_TS("bb")].QueryChildrenNum();

			Assert::AreEqual(acmap[_TS("cc")], (size_t)(3));
			Assert::AreEqual(acmap[_TS("qq")], (size_t)(2));

			TSTR file = GetFolderPath() + _TS("QueryChildrenNum2.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("QueryChildrenNum2Check.xml"), FT_UTF8);

			Element::available_child_t acmap2 = root2[_TS("bb")].QueryChildrenNum();

			Assert::AreEqual(acmap2[_TS("cc")], (size_t)(3));
			Assert::AreEqual(acmap2[_TS("qq")], (size_t)(2));
		}
		TEST_METHOD(AsCollection1)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);

			Element::collection_t vec = root[_TS("bb")][_TS("cc")].AsCollection();

			Assert::AreNotEqual(vec.size(), (size_t)0U);
			for(size_t i=0;i<vec.size(); ++i)
			{
				Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
			}

			TSTR file = GetFolderPath() + _TS("AsCollection1.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AsCollection1Check.xml"), FT_UTF8);

			Element::collection_t vec2 = root2[_TS("bb")][_TS("cc")].AsCollection();

			Assert::AreNotEqual(vec2.size(), (size_t)0U);
			for(size_t i=0;i<vec2.size(); ++i)
			{
				Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
			}
		}
		TEST_METHOD(AsCollection2)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);

			Element::collection_t vec = root[_TS("bb")][_TS("cc")].AsCollection();

			Assert::AreNotEqual(vec.size(), (size_t)0U);
			for(size_t i=0;i<vec.size(); ++i)
			{
				Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
			}

			TSTR file = GetFolderPath() + _TS("AsCollection2.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AsCollection2Check.xml"), FT_UTF8);

			Element::collection_t vec2 = root2[_TS("bb")][_TS("cc")].AsCollection();

			Assert::AreNotEqual(vec2.size(), (size_t)0U);
			for(size_t i=0;i<vec2.size(); ++i)
			{
				Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
			}
		}
		TEST_METHOD(AsCollectionPred)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);

			Pred pred;
			Element::collection_t vec = root[_TS("bb")][_TS("cc")].AsCollection(pred);

			Assert::AreEqual(vec.size(), (size_t)2U);
			for(size_t i=0;i<vec.size(); ++i)
			{
				Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
			}

			TSTR file = GetFolderPath() + _TS("AsCollectionPred.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AsCollectionPredCheck.xml"), FT_UTF8);

			Element::collection_t vec2 = root2[_TS("bb")][_TS("cc")].AsCollection(pred);

			Assert::AreEqual(vec2.size(), (size_t)2U);
			for(size_t i=0;i<vec2.size(); ++i)
			{
				Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
			}
		}
		TEST_METHOD(GetChildren1)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);

			Element::collection_t vec = root[_TS("bb")].GetChildren(_TS("cc"));

			Assert::AreNotEqual(vec.size(), (size_t)0U);
			for(size_t i=0;i<vec.size(); ++i)
			{
				Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
			}

			TSTR file = GetFolderPath() + _TS("GetChildren1.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("GetChildren1Check.xml"), FT_UTF8);

			Element::collection_t vec2 = root2[_TS("bb")].GetChildren(_TS("cc"));

			Assert::AreNotEqual(vec2.size(), (size_t)0U);
			for(size_t i=0;i<vec2.size(); ++i)
			{
				Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
			}
		}
		TEST_METHOD(GetChildren2)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);

			Element::collection_t vec = root[_TS("bb")].GetChildren(_TS("cc"));

			Assert::AreNotEqual(vec.size(), (size_t)0U);
			for(size_t i=0;i<vec.size(); ++i)
			{
				Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
			}

			TSTR file = GetFolderPath() + _TS("GetChildren2.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("GetChildren2Check.xml"), FT_UTF8);

			Element::collection_t vec2 = root2[_TS("bb")].GetChildren(_TS("cc"));

			Assert::AreNotEqual(vec2.size(), (size_t)0U);
			for(size_t i=0;i<vec2.size(); ++i)
			{
				Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
			}
		}
		TEST_METHOD(GetChildrenPred)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);

			Pred pred;
			Element::collection_t vec = root[_TS("bb")].Filter(_TS("cc"),  pred);

			Assert::AreEqual(vec.size(), (size_t)2U);
			for(size_t i=0;i<vec.size(); ++i)
			{
				Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
			}

			TSTR file = GetFolderPath() + _TS("GetChildrenPred.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("GetChildrenPredCheck.xml"), FT_UTF8);

			Element::collection_t vec2 = root2[_TS("bb")].Filter(_TS("cc"),  pred);

			Assert::AreEqual(vec2.size(), (size_t)2U);
			for(size_t i=0;i<vec2.size(); ++i)
			{
				Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
			}
		}
		TEST_METHOD(CountPred)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);

			Pred pred;
			unsigned int cnt = root[_TS("bb")].Count(_TS("cc"),  pred);

			Assert::AreEqual((unsigned int)(2), cnt);
		}
		TEST_METHOD(DetachAndAddNode)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			int dd = 2000000000;
			elem.SetInt32(dd);
			int dd2 = elem.GetInt32(10);
			Assert::AreEqual(dd, dd2);

			Element elemDelete = elem.Create(_TS("dd"));
			elemDelete.SetInt32(dd);
			Assert::IsTrue(elemDelete.Exists());
			elem.DetachNode(elemDelete);

			dd2 = elem[_TS("dd")].GetInt32(10);
			Assert::AreEqual(10, dd2);

			elem.AddNode(elemDelete);

			dd2 = elem[_TS("dd")].GetInt32(10);
			Assert::AreEqual(dd, dd2);

			elem.DetachNode(elemDelete);
			elemDelete.Destroy();

			TSTR file = GetFolderPath() + _TS("DetachAndAddNode.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("DetachAndAddNodeCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			dd2 = elem2[_TS("dd")].GetInt32(10);
			Assert::AreEqual(10, dd2);
		}
		TEST_METHOD(RemoveNode)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			int dd = 2000000000;
			elem.SetInt32(dd);
			int dd2 = elem.GetInt32(10);
			Assert::AreEqual(dd, dd2);

			elem.Remove();
			dd2 = elem.GetInt32(10);
			Assert::AreEqual(10, dd2);

			TSTR file = GetFolderPath() + _TS("RemoveNode.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("RemoveNodeCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];

			dd2 = elem2.GetInt32(10);
			Assert::AreEqual(10, dd2);
		}
		
		TEST_METHOD(TestDelimiter)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			ELMAX_INT64 dd = 14000000000L;
			Assert::IsTrue(elem.Exists());
			elem.SetInt64(dd);

			TSTR file = GetFolderPath() + _TS("TestDelimiter1.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("TestDelimiter1Check.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			ELMAX_INT64 dd2 = elem2.GetInt64(10);

			Assert::IsTrue(dd == dd2);
		}
		TEST_METHOD(EmptyAsCollection)
		{
			using namespace Elmax;
			RootElement root(_TS("cc"));

			Element elem1 = root.Create(_TS("aa"));
			elem1.SetInt32(11);

			bool bExceptionThrown = false;
			try
			{
				Element::collection_t vec = root[_TS("aa")][_TS("bb")].AsCollection();

				Assert::AreEqual((size_t)(0), vec.size());
			}
			catch (std::exception e)
			{
				bExceptionThrown = true;
			}
			Assert::IsTrue(bExceptionThrown);

			TSTR file = GetFolderPath() + _TS("EmptyAsCollection.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("EmptyAsCollectionCheck.xml"), FT_UTF8);

			bExceptionThrown = false;
			try
			{
				Element::collection_t vec2 = root2[_TS("bb")].AsCollection();

				Assert::AreEqual((size_t)(0), vec2.size());
			}
			catch (std::exception e)
			{
				bExceptionThrown = true;
			}
		}
		TEST_METHOD(EmptyGetChildren)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem1 = root.Create(_TS("bb"));
			elem1.SetInt32(11);

			Element::collection_t vec = root[_TS("bb")].GetChildren(_TS("cc"));

			Assert::AreEqual((size_t)(0), vec.size());

			TSTR file = GetFolderPath() + _TS("EmptyGetChildren.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("EmptyGetChildrenCheck.xml"), FT_UTF8);

			Element::collection_t vec2 = root2[_TS("bb")].GetChildren(_TS("cc"));

			Assert::AreEqual((size_t)(0), vec2.size());
		}
		TEST_METHOD(EmptyQueryChildrenNum)
		{
			using namespace Elmax;
			RootElement root(_TS("cc"));

			root.Create(_TS("aa"));

			Element::available_child_t acmap = root[_TS("aa")].QueryChildrenNum();

			Assert::AreEqual((size_t)(0), acmap.size());

			TSTR file = GetFolderPath() + _TS("EmptyQueryChildrenNum.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("EmptyQueryChildrenNumCheck.xml"), FT_UTF8);

			Element::available_child_t acmap2 = root2[_TS("aa")].QueryChildrenNum();

			Assert::AreEqual((size_t)(0), acmap2.size());
		}
		TEST_METHOD(InvalidElementGetChildren)
		{
			using namespace Elmax;
			RootElement root(_TS("cc"));

			Element elem1 = root.Create(_TS("aa"));
			elem1.SetInt32(11);

			bool bExceptionThrown = false;
			try
			{
				Element::collection_t vec = root[_TS("aa")][_TS("bb")].GetChildren(_TS("cc"));

				Assert::AreEqual((size_t)(0), vec.size());
			}
			catch (std::exception e)
			{
				bExceptionThrown = true;
			}
			Assert::IsTrue(bExceptionThrown);

			TSTR file = GetFolderPath() + _TS("InvalidElementGetChildren.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("InvalidElementGetChildrenCheck.xml"), FT_UTF8);

			bExceptionThrown = false;
			try
			{
				Element::collection_t vec2 = root2[_TS("bb")].GetChildren(_TS("cc"));

				Assert::AreEqual((size_t)(0), vec2.size());
			}
			catch (std::exception e)
			{
				bExceptionThrown = true;
			}
			Assert::IsTrue(bExceptionThrown);
		}
		TEST_METHOD(InvalidElementQueryChildrenNum)
		{
			using namespace Elmax;
			RootElement root(_TS("cc"));

			root.Create(_TS("aa"));

			bool bExceptionThrown = false;
			try
			{
				Element::available_child_t acmap = root[_TS("aa|bb")].QueryChildrenNum();

				Assert::AreEqual((size_t)(0), acmap.size());
			}
			catch (std::exception e)
			{
				bExceptionThrown = true;
			}
			Assert::IsTrue(bExceptionThrown);

			TSTR file = GetFolderPath() + _TS("InvalidElementQueryChildrenNum.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("InvalidElementQueryChildrenNumCheck.xml"), FT_UTF8);

			bExceptionThrown = false;
			try
			{
				Element::available_child_t acmap2 = root2[_TS("aa|bb")].QueryChildrenNum();

				Assert::AreEqual((size_t)(0), acmap2.size());
			}
			catch (std::exception e)
			{
				bExceptionThrown = true;
			}
			Assert::IsTrue(bExceptionThrown);
		}
		TEST_METHOD(Sort)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetDouble(22.0);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetDouble(33.0);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetDouble(11.0);

			SortElementPred pred;
			Element::collection_t list = root[_TS("bb")].Sort(_TS("cc"), pred);
			Assert::AreEqual(list[0].GetDouble(0), 11.0);
			Assert::AreEqual(list[1].GetDouble(0), 22.0);
			Assert::AreEqual(list[2].GetDouble(0), 33.0);
		}

		TEST_METHOD(Iterator1)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);
			Element elem4 = elembb.Create(_TS("dd"));
			elem4.SetInt32(44);
			root[_TS("bb")].AddComment(_TS("Hello world"));

			Element elemBB = root[_TS("bb")];
			Element::Iterator it = elemBB.Begin(_TS("cc"));

			size_t sum = 0;
			size_t i=0;
			for(;it!=elemBB.End(); ++it, ++i)
			{
				Assert::AreEqual((*it).GetInt32(10), (int)(11*(i+1)));
				sum += (*it).GetInt32(10);
			}
			Assert::AreEqual((size_t)(66), sum);

			TSTR file = GetFolderPath() + _TS("Iterator1.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("Iterator1Check.xml"), FT_UTF8);

			Element elemBB2 = root2[_TS("bb")];
			Element::Iterator it2 = elemBB2.Begin(_TS("cc"));

			sum = 0;
			i=0;
			for(;it2!=elemBB2.End(); ++it2, ++i)
			{
				Assert::AreEqual((*it2).GetInt32(10), (int)(11*(i+1)));
				sum += (*it2).GetInt32(10);
			}
			Assert::AreEqual((size_t)(66), sum);
		}

		TEST_METHOD(Iterator2)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);
			Element elem4 = elembb.Create(_TS("dd"));
			elem4.SetInt32(44);
			root[_TS("bb")].AddComment(_TS("Hello world"));

			Element elemBB = root[_TS("bb")];
			Element::Iterator it = elemBB.Begin(_TS("*"));

			size_t sum = 0;
			size_t i=0;
			for(;it!=elemBB.End(); ++it, ++i)
			{
				Assert::AreEqual((*it).GetInt32(10), (int)(11*(i+1)));
				sum += (*it).GetInt32(10);
			}
			Assert::AreEqual((size_t)(110), sum);

			TSTR file = GetFolderPath() + _TS("Iterator2.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("Iterator2Check.xml"), FT_UTF8);

			Element elemBB2 = root2[_TS("bb")];
			Element::Iterator it2 = elemBB2.Begin(_TS("*"));

			sum = 0;
			i=0;
			for(;it2!=elemBB2.End(); ++it2, ++i)
			{
				Assert::AreEqual((*it2).GetInt32(10), (int)(11*(i+1)));
				sum += (*it2).GetInt32(10);
			}
			Assert::AreEqual((size_t)(110), sum);
		}
		TEST_METHOD(SaveToString)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);
			Element elem4 = elembb.Create(_TS("dd"));
			elem4.SetInt32(44);
			root[_TS("bb")].AddComment(_TS("Hello world"));

			Element elemBB = root[_TS("bb")];
			Element::Iterator it = elemBB.Begin(_TS("*"));

			size_t sum = 0;
			size_t i=0;
			for(;it!=elemBB.End(); ++it, ++i)
			{
				Assert::AreEqual((*it).GetInt32(10), (int)(11*(i+1)));
				sum += (*it).GetInt32(10);
			}
			Assert::AreEqual((size_t)(110), sum);

			TSTR saved = root.ToString();

			RootElement root2;
			root2.ParseXMLString(saved);
			TSTR saved2 = root2.ToString();
			Assert::IsTrue(saved == saved2);

			Element elemBB2 = root2[_TS("bb")];
			Element::Iterator it2 = elemBB2.Begin(_TS("*"));

			sum = 0;
			i=0;
			for(;it2!=elemBB2.End(); ++it2, ++i)
			{
				Assert::AreEqual((*it2).GetInt32(10), (int)(11*(i+1)));
				sum += (*it2).GetInt32(10);
			}
			Assert::AreEqual((size_t)(110), sum);
		}

		TEST_METHOD(SaveToPrettyString)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elembb = root.Create(_TS("bb"));

			Element elem1 = elembb.Create(_TS("cc"));
			elem1.SetInt32(11);
			Element elem2 = elembb.Create(_TS("cc"));
			elem2.SetInt32(22);
			Element elem3 = elembb.Create(_TS("cc"));
			elem3.SetInt32(33);
			Element elem4 = elembb.Create(_TS("dd"));
			elem4.SetInt32(44);
			root[_TS("bb")].AddComment(_TS("Hello world"));

			Element elemBB = root[_TS("bb")];
			Element::Iterator it = elemBB.Begin(_TS("*"));

			size_t sum = 0;
			size_t i=0;
			for(;it!=elemBB.End(); ++it, ++i)
			{
				Assert::AreEqual((*it).GetInt32(10), (int)(11*(i+1)));
				sum += (*it).GetInt32(10);
			}
			Assert::AreEqual((size_t)(110), sum);

			TSTR saved = root.ToPrettyString(_TS("  "));

			RootElement root2;
			root2.ParseXMLString(saved);
			TSTR saved2 = root2.ToPrettyString(_TS("  "));
			Assert::IsTrue(saved == saved2);

			Element elemBB2 = root2[_TS("bb")];
			Element::Iterator it2 = elemBB2.Begin(_TS("*"));

			sum = 0;
			i=0;
			for(;it2!=elemBB2.End(); ++it2, ++i)
			{
				Assert::AreEqual((*it2).GetInt32(10), (int)(11*(i+1)));
				sum += (*it2).GetInt32(10);
			}
			Assert::AreEqual((size_t)(110), sum);
		}
	};
}