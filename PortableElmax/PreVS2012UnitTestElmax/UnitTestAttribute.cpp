#include "Assert.h"
#include "../PortableElmax/Elmax.h"

namespace UnitTestElmax
{
	TEST_CLASS(UnitTestAttribute)
	{
	private:
		
#ifdef _MICROSOFT
		static TSTR GetFolderPath()
		{
			return _TS("c:\\temp\\");
		}
#else
		static TSTR GetFolderPath()
		{
			return _TS("temp/");
		}
#endif

	public:
		
		TEST_METHOD(AttributeBoolean)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			bool dd = true;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrBool(_TS("Attr"), dd);
			bool dd3 = elem.GetAttrBool(_TS("Attr"), false);

			Assert::AreEqual(dd, dd3);

			TSTR file = GetFolderPath() + _TS("AttributeBoolean.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeBooleanCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			bool dd2 = elem2.GetAttrBool(_TS("Attr"), false);

			Assert::AreEqual(dd, dd2);

			
			
		}
		TEST_METHOD(AttributeDateTime)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			DateAndTime dd(2006, 7, 23, 9, 0, 23);
			Assert::IsTrue(elem.Exists());
			elem.SetAttrDateTime(_TS("Attr"), dd);
			DateAndTime ddcheck;
			DateAndTime dd3 = elem.GetAttrDateTime(_TS("Attr"), ddcheck);

			Assert::AreEqual(dd.GetYear(), dd3.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
			Assert::AreEqual(dd.GetHour(), dd3.GetHour());
			Assert::AreEqual(dd.GetMinute(), dd3.GetMinute());
			Assert::AreEqual(dd.GetSecond(), dd3.GetSecond());

			TSTR file = GetFolderPath() + _TS("AttributeDateTime.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeDateTimeCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			DateAndTime dd2 = elem2.GetAttrDateTime(_TS("Attr"), ddcheck);

			Assert::AreEqual(dd.GetYear(), dd2.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
			Assert::AreEqual(dd.GetHour(), dd2.GetHour());
			Assert::AreEqual(dd.GetMinute(), dd2.GetMinute());
			Assert::AreEqual(dd.GetSecond(), dd2.GetSecond());
			
			
		}
		TEST_METHOD(AttributeDate)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Date dd(2010, 10, 1);
			Assert::IsTrue(elem.Exists());
			elem.SetAttrDate(_TS("Attr"), dd);
			Date ddcheck;
			Date dd3 = elem.GetAttrDate(_TS("Attr"), ddcheck);

			Assert::AreEqual(dd.GetYear(), dd3.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());

			TSTR file = GetFolderPath() + _TS("AttributeDate.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeDateCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			Date dd2 = elem2.GetAttrDate(_TS("Attr"), ddcheck);

			Assert::AreEqual(dd.GetYear(), dd2.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
			
			
		}
		TEST_METHOD(AttributeInt64)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			ELMAX_INT64 dd = 14000000000L;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrInt64(_TS("Attr"), dd);
			ELMAX_INT64 dd3 = elem.GetAttrInt64(_TS("Attr"), 10);

			Assert::IsTrue(dd == dd3);

			TSTR file = GetFolderPath() + _TS("AttributeInt64.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeInt64Check.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			ELMAX_INT64 dd2 = elem2.GetAttrInt64(_TS("Attr"), 10);

			Assert::IsTrue(dd == dd2);
			
			
		}
		TEST_METHOD(AttributeInt)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			int dd = 2000000000;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrInt32(_TS("Attr"), dd);
			int dd3 = elem.GetAttrInt32(_TS("Attr"), 10);

			Assert::AreEqual(dd, dd3);

			TSTR file = GetFolderPath() + _TS("AttributeInt.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeIntCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			int dd2 = elem2.GetAttrInt32(_TS("Attr"), 10);

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeShort)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			short dd = 32000;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrInt16(_TS("Attr"), dd);
			short dd3 = elem.GetAttrInt16(_TS("Attr"), 10);

			Assert::AreEqual(dd, dd3);

			TSTR file = GetFolderPath() + _TS("AttributeShort.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeShortCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			short dd2 = elem2.GetAttrInt16(_TS("Attr"), 10);

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeChar)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			char dd = 'A';
			Assert::IsTrue(elem.Exists());
			elem.SetAttrChar(_TS("Attr"), dd);
			char dd3 = elem.GetAttrChar(_TS("Attr"), 'P');

			Assert::AreEqual(dd, dd3);

			TSTR file = GetFolderPath() + _TS("AttributeChar.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeCharCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			char dd2 = elem2.GetAttrChar(_TS("Attr"), 'P');

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeUInt64)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned ELMAX_INT64 dd = 14000000000UL;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrUInt64(_TS("Attr"), dd);
			unsigned ELMAX_INT64 dd3 = elem.GetAttrUInt64(_TS("Attr"), 10);

			Assert::AreEqual(dd, dd3);

			TSTR file = GetFolderPath() + _TS("AttributeUInt64.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeUInt64Check.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned ELMAX_INT64 dd2 = elem2.GetAttrUInt64(_TS("Attr"), 10);

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeUInt)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 4000000000;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrUInt32(_TS("Attr"), dd);
			unsigned int dd3 = elem.GetAttrUInt32(_TS("Attr"), 10);

			Assert::AreEqual(dd, dd3);

			TSTR file = GetFolderPath() + _TS("AttributeUInt.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeUIntCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned int dd2 = elem2.GetAttrUInt32(_TS("Attr"), 10);

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeUShort)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned short dd = 65000;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrUInt16(_TS("Attr"), dd);
			unsigned short dd3 = elem.GetAttrUInt16(_TS("Attr"), 10);

			Assert::IsTrue(dd == dd3);

			TSTR file = GetFolderPath() + _TS("AttributeUShort.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeUShortCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned short dd2 = elem2.GetAttrUInt16(_TS("Attr"), 10);

			Assert::IsTrue(dd == dd2);
			
			
		}
		TEST_METHOD(AttributeUChar)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned char dd = 255;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrUChar(_TS("Attr"), dd);
			unsigned char dd3 = elem.GetAttrUChar(_TS("Attr"), 12);

			Assert::AreEqual(dd, dd3);

			TSTR file = GetFolderPath() + _TS("AttributeUChar.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeUCharCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned char dd2 = elem2.GetAttrUChar(_TS("Attr"), 12);

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeWString)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			TSTR dd = _TS("ABCD");
			Assert::IsTrue(elem.Exists());
			elem.SetAttrString(_TS("Attr"), dd);
			TSTR dd3 = elem.GetAttrString(_TS("Attr"), _TS("A"));

			Assert::IsTrue(dd == dd3);

			TSTR file = GetFolderPath() + _TS("AttributeWString.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeWStringCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			TSTR dd2 = elem2.GetAttrString(_TS("Attr"), _TS("A"));

			Assert::IsTrue(dd == dd2);
			
			
		}
		TEST_METHOD(AttributeDouble)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			double dd = 123.0;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrDouble(_TS("Attr"), dd);
			double dd3 = elem.GetAttrDouble(_TS("Attr"), 10.0);

			Assert::AreEqual(dd, dd3);

			TSTR file = GetFolderPath() + _TS("AttributeDouble.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeDoubleCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			double dd2 = elem2.GetAttrDouble(_TS("Attr"), 10.0);

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeFloat)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			float dd = 123.0f;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrFloat(_TS("Attr"), dd);
			float dd3 = elem.GetAttrFloat(_TS("Attr"), 10.0f);

			Assert::AreEqual(dd, dd3);

			TSTR file = GetFolderPath() + _TS("AttributeFloat.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeFloatCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			float dd2 = elem2.GetAttrFloat(_TS("Attr"), 10.0f);

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeHex)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 0xACAC;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrHex(_TS("dd"), dd);

			unsigned int ans = elem.ReadAttrHex(_TS("dd"), 0xee);

			Assert::AreEqual(dd, ans);

			TSTR file = GetFolderPath() + _TS("AttributeHex.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeHexCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned int dd2 = elem2.ReadAttrHex(_TS("dd"), 0xee);

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeHexWithPrefix)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 0xACAC;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrHex(_TS("dd"), dd, true);

			unsigned int ans = elem.ReadAttrHex(_TS("dd"), 0xee);
			Assert::AreEqual(dd, ans);

			TSTR strAns = elem.GetAttrString(_TS("dd"), _TS("0xee"));

			Assert::IsTrue(TSTR(_TS("0xACAC")) == strAns);

			TSTR file = GetFolderPath() + _TS("AttributeHexWithPrefix.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeHexWithPrefixCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned int dd2 = elem2.ReadAttrHex(_TS("dd"), 0xee);

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeHexWithLowerCase)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 0xACAC;
			Assert::IsTrue(elem.Exists());
			elem.SetAttrString(_TS("dd"), _TS("acac"));

			unsigned int ans = elem.ReadAttrHex(_TS("dd"), 0xee);

			Assert::AreEqual(dd, ans);

			TSTR file = GetFolderPath() + _TS("AttributeHexWithLowerCase.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeHexWithLowerCaseCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned int dd2 = elem2.ReadAttrHex(_TS("dd"), 0xee);

			Assert::AreEqual(dd, dd2);
			
			
		}
		TEST_METHOD(AttributeNonExistantString)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			TSTR dd = _TS("A");
			Assert::IsTrue(elem.Exists());
			TSTR dd3 = elem.GetAttrString(_TS("Attr"), _TS("A"));

			Assert::IsTrue(dd == dd3);

			TSTR file = GetFolderPath() + _TS("AttributeNonExistantString.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeNonExistantStringCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			TSTR dd2 = elem2.GetAttrString(_TS("Attr"), _TS("A"));

			Assert::IsTrue(dd == dd2);
			
			
		}
		TEST_METHOD(AttributeNonExistantInt32)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			TSTR dd = _TS("ABCD");
			Assert::IsTrue(elem.Exists());
			int dd3 = elem.GetAttrInt32(_TS("Attr"), 123);

			Assert::AreEqual(123, dd3);

			TSTR file = GetFolderPath() + _TS("AttributeNonExistantInt32.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeNonExistantInt32Check.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			int dd2 = elem2.GetAttrInt32(_TS("Attr"), 123);

			Assert::AreEqual(123, dd2);
			
			
		}
		TEST_METHOD(AttributeEmpty)
		{
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());
			elem.SetAttrString(_TS("Attr"), _TS(""));
			TSTR dd = elem.GetAttrString(_TS("Attr"), _TS(""));

			Assert::AreEqual(dd, TSTR(_TS("")));

			TSTR file = GetFolderPath() + _TS("AttributeEmpty.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("AttributeEmptyCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			TSTR dd2 = elem2.GetAttrString(_TS("Attr"), _TS(""));

			Assert::AreEqual(dd2, TSTR(_TS("")));

			
			
		}

		static void executeTests()
		{
			AttributeBoolean();
			std::cout<<"AttributeBoolean() runs fine!"<<std::endl;
			AttributeDateTime();
			std::cout<<"AttributeDateTime() runs fine!"<<std::endl;
			AttributeDate();
			std::cout<<"AttributeDate() runs fine!"<<std::endl;
			AttributeInt64();
			std::cout<<"AttributeInt64() runs fine!"<<std::endl;
			AttributeInt();
			std::cout<<"AttributeInt() runs fine!"<<std::endl;
			AttributeShort();
			std::cout<<"AttributeShort() runs fine!"<<std::endl;
			AttributeChar();
			std::cout<<"AttributeChar() runs fine!"<<std::endl;
			AttributeUInt64();
			std::cout<<"AttributeUInt64() runs fine!"<<std::endl;
			AttributeUInt();
			std::cout<<"AttributeUInt() runs fine!"<<std::endl;
			AttributeUShort();
			std::cout<<"AttributeUShort() runs fine!"<<std::endl;
			AttributeUChar();
			std::cout<<"AttributeUChar() runs fine!"<<std::endl;
			AttributeWString();
			std::cout<<"AttributeWString() runs fine!"<<std::endl;
			AttributeDouble();
			std::cout<<"AttributeDouble() runs fine!"<<std::endl;
			AttributeFloat();
			std::cout<<"AttributeFloat() runs fine!"<<std::endl;
			AttributeHex();
			std::cout<<"AttributeHex() runs fine!"<<std::endl;
			AttributeHexWithPrefix();
			std::cout<<"AttributeHexWithPrefix() runs fine!"<<std::endl;
			AttributeHexWithLowerCase();
			std::cout<<"AttributeHexWithLowerCase() runs fine!"<<std::endl;
			AttributeNonExistantString();
			std::cout<<"AttributeNonExistantString() runs fine!"<<std::endl;
			AttributeNonExistantInt32();
			std::cout<<"AttributeNonExistantInt32() runs fine!"<<std::endl;
			AttributeEmpty();
			std::cout<<"AttributeEmpty() runs fine!"<<std::endl;
		}
	};
}