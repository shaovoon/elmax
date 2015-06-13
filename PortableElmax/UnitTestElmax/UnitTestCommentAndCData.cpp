#include "stdafx.h"
#include "CppUnitTest.h"
#include "../PortableElmax/Elmax.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestElmax
{
	TEST_CLASS(UnitTestCommentAndCData)
	{
	private:

		TSTR GetFolderPath()
		{
			return _TS("c:\\temp\\");
		}

	public:
		
		TEST_METHOD(SaveReadComment)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			elem.AddComment(strComment);

			Comment comment = elem.GetCommentCollection().at(0);

			Assert::IsTrue(strComment == comment.GetContent());

			TSTR file = GetFolderPath() + _TS("SaveReadComment.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadCommentCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			Comment comment2 = elem2.GetCommentCollection().at(0);

			Assert::IsTrue(strComment == comment2.GetContent());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(SaveReadCData)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData);

			CData cdata = elem.GetCDataCollection().at(0);

			Assert::IsTrue(strCData == cdata.GetContent());

			TSTR file = GetFolderPath() + _TS("SaveReadCData.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadCDataCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			CData cdata2 = elem2.GetCDataCollection().at(0);

			Assert::IsTrue(strCData == cdata2.GetContent());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(SaveReadCommentCollection)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			elem.AddComment(strComment);
			TSTR strComment2 = _TS("Can I see you?");
			elem.AddComment(strComment2);

			std::vector<Comment> vec = elem.GetCommentCollection();

			Assert::IsTrue(strComment == vec.at(0).GetContent());

			Assert::IsTrue(strComment2 == vec.at(1).GetContent());

			TSTR file = GetFolderPath() + _TS("SaveReadCommentCollection.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadCommentCollectionCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<Comment> vec2 = elem2.GetCommentCollection();

			Assert::IsTrue(strComment == vec2.at(0).GetContent());

			Assert::IsTrue(strComment2 == vec2.at(1).GetContent());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(SaveReadCDataCollection)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData);
			TSTR strCData2 = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData2);

			std::vector<CData> vec = elem.GetCDataCollection();

			Assert::IsTrue(strCData == vec.at(0).GetContent());

			Assert::IsTrue(strCData2 == vec.at(1).GetContent());

			TSTR file = GetFolderPath() + _TS("SaveReadCDataCollection.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadCDataCollectionCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<CData> vec2 = elem.GetCDataCollection();

			Assert::IsTrue(strCData == vec2.at(0).GetContent());

			Assert::IsTrue(strCData2 == vec2.at(1).GetContent());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(DeleteComment)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			elem.AddComment(strComment);

			Comment comment = elem.GetCommentCollection().at(0);

			Assert::IsTrue(strComment == comment.GetContent());

			Assert::IsTrue(comment.Remove());

			std::vector<Comment> vec = elem.GetCommentCollection();

			Assert::IsTrue(vec.empty());

			TSTR file = GetFolderPath() + _TS("DeleteComment.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("DeleteCommentCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<Comment> vec2 = elem2.GetCommentCollection();

			Assert::IsTrue(vec2.empty());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(DeleteAllComment)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			elem.AddComment(strComment);

			Comment comment = elem.GetCommentCollection().at(0);

			Assert::IsTrue(strComment == comment.GetContent());

			Assert::IsTrue(elem.DeleteAllComments());

			std::vector<Comment> vec = elem.GetCommentCollection();

			Assert::IsTrue(vec.empty());

			TSTR file = GetFolderPath() + _TS("DeleteAllComment.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("DeleteAllCommentCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<Comment> vec2 = elem2.GetCommentCollection();

			Assert::IsTrue(vec2.empty());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(DeleteCData)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData);

			CData cdata = elem.GetCDataCollection().at(0);

			Assert::IsTrue(strCData == cdata.GetContent());

			Assert::IsTrue(cdata.Remove());

			std::vector<CData> vec = elem.GetCDataCollection();

			Assert::IsTrue(vec.empty());

			TSTR file = GetFolderPath() + _TS("DeleteCData.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("DeleteCDataCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<CData> vec2 = elem2.GetCDataCollection();

			Assert::IsTrue(vec2.empty());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(DeleteAllCData)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData);

			CData cdata = elem.GetCDataCollection().at(0);

			Assert::IsTrue(strCData == cdata.GetContent());

			Assert::IsTrue(elem.DeleteAllCData());

			std::vector<CData> vec = elem.GetCDataCollection();

			Assert::IsTrue(vec.empty());

			TSTR file = GetFolderPath() + _TS("DeleteAllCData.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("DeleteAllCDataCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<CData> vec2 = elem2.GetCDataCollection();

			Assert::IsTrue(vec2.empty());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(UpdateComment)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			elem.AddComment(strComment);

			Comment comment = elem.GetCommentCollection().at(0);

			Assert::IsTrue(strComment == comment.GetContent());

			TSTR strUpdate = _TS("Cannot see anything!");
			Assert::IsTrue(comment.Update(strUpdate));

			TSTR file = GetFolderPath() + _TS("UpdateComment.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("UpdateCommentCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			Comment comment2 = elem2.GetCommentCollection().at(0);

			Assert::IsTrue(strUpdate == comment2.GetContent());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(UpdateCData)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			elem.AddCData(strCData);

			CData cdata = elem.GetCDataCollection().at(0);

			Assert::IsTrue(strCData == cdata.GetContent());

			TSTR strUpdate = _TS("<data>Where is my world?</data>");
			Assert::IsTrue(cdata.Update(strUpdate));

			TSTR file = GetFolderPath() + _TS("UpdateCData.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("UpdateCDataCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			CData cdata2 = elem2.GetCDataCollection().at(0);

			Assert::IsTrue(strUpdate == cdata2.GetContent());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(SaveReadEmptyCommentCollection)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());

			std::vector<Comment> vec = elem.GetCommentCollection();

			Assert::AreEqual((size_t)(0), vec.size());

			TSTR file = GetFolderPath() + _TS("SaveReadEmptyCommentCollection.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadEmptyCommentCollectionCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<Comment> vec2 = elem2.GetCommentCollection();

			Assert::AreEqual((size_t)(0), vec2.size());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(SaveReadEmptyCDataCollection)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());

			std::vector<CData> vec = elem.GetCDataCollection();

			Assert::AreEqual((size_t)(0), vec.size());

			TSTR file = GetFolderPath() + _TS("SaveReadEmptyCDataCollection.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadEmptyCDataCollectionCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			std::vector<CData> vec2 = elem.GetCDataCollection();

			Assert::AreEqual((size_t)(0), vec2.size());
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(InvalidElementCData)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strCData = _TS("<data>Where is my data?</data>");
			bool bExceptThrown = false;
			try
			{
				Assert::AreEqual(false, elem[_TS("dd")].AddCData(strCData));
			}
			catch (std::exception e)
			{
				bExceptThrown = true;
			}
			Assert::IsTrue(bExceptThrown);
			bExceptThrown = false;

			try
			{
				std::vector<CData> vec = elem[_TS("dd")].GetCDataCollection();

				Assert::AreEqual((size_t)(0), vec.size());
			}
			catch (std::exception e)
			{
				bExceptThrown = true;
			}
			Assert::IsTrue(bExceptThrown);
			bExceptThrown = false;

			try
			{
				Assert::AreEqual(false, elem[_TS("dd")].DeleteAllCData());
			}
			catch (std::exception e)
			{
				bExceptThrown = true;
			}
			Assert::IsTrue(bExceptThrown);

			TSTR file = GetFolderPath() + _TS("InvalidElementCData.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("InvalidElementCDataCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());
			bExceptThrown = false;
			try
			{
				std::vector<CData> vec2 = elem2[_TS("dd")].GetCDataCollection();
				Assert::AreEqual((size_t)(0), vec2.size());
			}
			catch (std::exception e)
			{
				bExceptThrown = true;
			}
			Assert::IsTrue(bExceptThrown);

			bExceptThrown = false;

			try
			{
				Assert::AreEqual(false, elem2[_TS("dd")].DeleteAllCData());
			}
			catch (std::exception e)
			{
				bExceptThrown = true;
			}
			Assert::IsTrue(bExceptThrown);
			root.Destroy();
			root2.Destroy();
		}
		TEST_METHOD(InvalidElementComment)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());
			TSTR strComment = _TS("Can you see me?");
			bool bExceptThrown = false;
			try
			{
				Assert::AreEqual(false, elem[_TS("dd")].AddComment(strComment));
			}
			catch (std::exception e)
			{
				bExceptThrown = true;
			}
			Assert::IsTrue(bExceptThrown);
			bExceptThrown = false;

			try
			{
				std::vector<Comment> vec = elem[_TS("dd")].GetCommentCollection();

				Assert::AreEqual((size_t)(0), vec.size());
			}
			catch (std::exception e)
			{
				bExceptThrown = true;
			}
			Assert::IsTrue(bExceptThrown);
			bExceptThrown = false;

			try
			{
				Assert::AreEqual(false, elem[_TS("dd")].DeleteAllComments());
			}
			catch (std::exception e)
			{
				bExceptThrown = true;
			}
			Assert::IsTrue(bExceptThrown);

			TSTR file = GetFolderPath() + _TS("InvalidElementComment.xml");
			root.Save(file, FT_UTF8);

			Element root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("InvalidElementCommentCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("aa")][_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			bExceptThrown = false;
			try
			{
				std::vector<Comment> vec2 = elem2[_TS("dd")].GetCommentCollection();
				Assert::AreEqual((size_t)(0), vec2.size());
			}
			catch (std::exception e)
			{
				bExceptThrown = true;
			}
			Assert::IsTrue(bExceptThrown);

			bExceptThrown = false;

			try
			{
				Assert::AreEqual(false, elem2[_TS("dd")].DeleteAllComments());
			}
			catch (std::exception e)
			{
				bExceptThrown = true;
			}
			Assert::IsTrue(bExceptThrown);
			root.Destroy();
			root2.Destroy();
		}
	};
}