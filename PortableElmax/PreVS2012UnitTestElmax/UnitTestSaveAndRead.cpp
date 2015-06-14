#include "Assert.h"
#include "../PortableElmax/Elmax.h"

namespace UnitTestElmax
{
	TEST_CLASS(UnitTestSaveAndRead)
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
		
		TEST_METHOD(SaveReadRootName)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			TSTR rootName = _TS("aa");
			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			bool dd = true;
			Assert::IsTrue(elem.Exists());
			elem.SetBool(dd);

			Assert::IsTrue(rootName == elem.GetRootName());

			TSTR file = GetFolderPath() + _TS("SaveReadRootName.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadRootNameCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			bool dd2 = elem2.GetBool(false);

			Assert::AreEqual(dd, dd2);

			Assert::IsTrue(rootName == elem2.GetRootName());
		}
		TEST_METHOD(SaveReadDateTime)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			DateAndTime dd(2006, 7, 23, 9, 0, 23);
			Assert::IsTrue(elem.Exists());
			elem.SetDateTime(dd);
			DateAndTime ddcheck;
			DateAndTime dd3 = elem.GetDateTime(ddcheck);

			Assert::AreEqual(dd.GetYear(), dd3.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
			Assert::AreEqual(dd.GetHour(), dd3.GetHour());
			Assert::AreEqual(dd.GetMinute(), dd3.GetMinute());
			Assert::AreEqual(dd.GetSecond(), dd3.GetSecond());

			TSTR file = GetFolderPath() + _TS("SaveReadDateTime.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadDateTimeCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			DateAndTime dd2 = elem2.GetDateTime(ddcheck);

			Assert::AreEqual(dd.GetYear(), dd2.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
			Assert::AreEqual(dd.GetHour(), dd2.GetHour());
			Assert::AreEqual(dd.GetMinute(), dd2.GetMinute());
			Assert::AreEqual(dd.GetSecond(), dd2.GetSecond());
		}
		TEST_METHOD(SaveReadDate)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Date dd(2010, 10, 1);
			Assert::IsTrue(elem.Exists());
			elem.SetDate(dd);
			Date ddcheck;
			Date dd3 = elem.GetDate(ddcheck);

			Assert::AreEqual(dd.GetYear(), dd3.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());

			TSTR file = GetFolderPath() + _TS("SaveReadDate.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadDateCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			Date dd2 = elem2.GetDate(ddcheck);

			Assert::AreEqual(dd.GetYear(), dd2.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
		}
		TEST_METHOD(SaveReadBoolean)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			bool dd = true;
			Assert::IsTrue(elem.Exists());
			elem.SetBool(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadBoolean.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadBooleanCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			bool dd2 = elem2.GetBool(false);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadProcessingInstruction)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			bool dd = true;
			Assert::IsTrue(elem.Exists());
			elem.SetBool(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadProcessingInstruction.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			std::map<TSTR, TSTR> prep;;
			root2.Open(prep, file);
			//root2.Save(GetFolderPath() + _TS("SaveReadProcessingInstructionCheck.xml"), FT_UTF8);

			Assert::IsTrue(prep[_TS("version")] == TSTR(_TS("1.0")));
			Assert::IsTrue(prep[_TS("encoding")] == TSTR(_TS("UTF-8")));
			
			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			bool dd2 = elem2.GetBool(false);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadInt64)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			ELMAX_INT64 dd = 14000000000L;
			Assert::IsTrue(elem.Exists());
			elem.SetInt64(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadInt64.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadInt64Check.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			ELMAX_INT64 dd2 = elem2.GetInt64(10);

			Assert::IsTrue(dd == dd2);
		}
		TEST_METHOD(SaveReadInt)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			int dd = 2000000000;
			Assert::IsTrue(elem.Exists());
			elem.SetInt32(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadIntSaveReadInt.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadIntCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			int dd2 = elem2.GetInt32(10);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadShort)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			short dd = 32000;
			Assert::IsTrue(elem.Exists());
			elem.SetInt16(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadShort.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadShortCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			short dd2 = elem2.GetInt16(10);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadChar)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			char dd = 'A';
			Assert::IsTrue(elem.Exists());
			elem.SetChar(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadChar.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadCharCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			char dd2 = elem2.GetChar('P');

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadUInt64)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned ELMAX_INT64 dd = 14000000000UL;
			Assert::IsTrue(elem.Exists());
			elem.SetUInt64(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadUInt64.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadUInt64Check.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned ELMAX_INT64 dd2 = elem2.GetUInt64(10);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadUInt)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 4000000000;
			Assert::IsTrue(elem.Exists());
			elem.SetUInt32(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadUInt.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadUIntCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned int dd2 = elem2.GetUInt32(10);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadUShort)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned short dd = 65000;
			Assert::IsTrue(elem.Exists());
			elem.SetUInt16(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadUShort.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadUShortCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned short dd2 = elem2.GetUInt16(10);

			Assert::IsTrue(dd == dd2);
		}
		TEST_METHOD(SaveReadUChar)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned char dd = 255;
			Assert::IsTrue(elem.Exists());
			elem.SetUChar(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadUChar.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadUCharCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned char dd2 = elem2.GetUChar(12);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadString)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			TSTR dd = _TS("ABCD");
			Assert::IsTrue(elem.Exists());
			elem.SetString(dd);

			TSTR dd3 = elem.GetString(_TS("A"));

			Assert::IsTrue(dd == dd3);

			TSTR file = GetFolderPath() + _TS("SaveReadString.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadStringCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			TSTR dd2 = elem2.GetString(_TS("A"));

			Assert::IsTrue(dd == dd2);
		}
		TEST_METHOD(SaveReadEscapeString)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			TSTR dd = _TS("<ABCD>");
			Assert::IsTrue(elem.Exists());
			elem.SetString(dd);

			TSTR dd3 = elem.GetString(_TS("A"));

			Assert::IsTrue(dd == dd3);

			TSTR file = GetFolderPath() + _TS("SaveReadEscapeString.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadStringCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			TSTR dd2 = elem2.GetString(_TS("A"));

			Assert::IsTrue(dd == dd2);
		}
		TEST_METHOD(SaveReadDouble)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			double dd = 123.0;
			Assert::IsTrue(elem.Exists());
			elem.SetDouble(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadDouble.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadDoubleCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			double dd2 = elem2.GetDouble(10.0);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadFloat)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			float dd = 123.0f;
			Assert::IsTrue(elem.Exists());
			elem.SetFloat(dd);

			TSTR file = GetFolderPath() + _TS("SaveReadFloat.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadFloatCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			float dd2 = elem2.GetFloat(10.0f);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadHex)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 0xACAC;
			Assert::IsTrue(elem.Exists());
			elem.SetHex(dd);

			unsigned int ans = elem.ReadHex(0xee);

			Assert::AreEqual(dd, ans);

			TSTR file = GetFolderPath() + _TS("SaveReadHex.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadHexCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned int dd2 = elem2.ReadHex(0xee);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadHexWithPrefix)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 0xACAC;
			Assert::IsTrue(elem.Exists());
			elem.SetHex(dd, true);

			unsigned int ans = elem.ReadHex(0xee);
			Assert::AreEqual(dd, ans);

			TSTR strAns = elem.GetString(_TS("0xee"));

			Assert::IsTrue(TSTR(_TS("0xACAC")) == strAns);

			TSTR file = GetFolderPath() + _TS("SaveReadHexWithPrefix.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadHexWithPrefixCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned int dd2 = elem2.ReadHex(0xee);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(SaveReadHexWithLowerCase)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 0xACAC;
			Assert::IsTrue(elem.Exists());
			elem.SetString(_TS("acac"));

			unsigned int ans = elem.ReadHex(0xee);

			Assert::AreEqual(dd, ans);

			TSTR file = GetFolderPath() + _TS("SaveReadHexWithLowerCase.xml");
			root.Save(file, FT_UTF8);

			RootElement root2;
			root2.Open(file);
			//root2.Save(GetFolderPath() + _TS("SaveReadHexWithLowerCaseCheck.xml"), FT_UTF8);

			Element elem2 = root2[_TS("bb")][_TS("cc")];
			Assert::IsTrue(elem2.Exists());

			unsigned int dd2 = elem2.ReadHex(0xee);

			Assert::AreEqual(dd, dd2);
		}
		static void executeTests()
		{
			SaveReadRootName();
			std::cout<<"SaveReadRootName() runs fine!"<<std::endl;
			SaveReadDateTime();
			std::cout<<"SaveReadDateTime() runs fine!"<<std::endl;
			SaveReadDate();
			std::cout<<"SaveReadDate() runs fine!"<<std::endl;
			SaveReadBoolean();
			std::cout<<"SaveReadBoolean() runs fine!"<<std::endl;
			SaveReadProcessingInstruction();
			std::cout<<"SaveReadProcessingInstruction() runs fine!"<<std::endl;
			SaveReadInt64();
			std::cout<<"SaveReadInt64() runs fine!"<<std::endl;
			SaveReadInt();
			std::cout<<"SaveReadInt() runs fine!"<<std::endl;
			SaveReadShort();
			std::cout<<"SaveReadShort() runs fine!"<<std::endl;
			SaveReadChar();
			std::cout<<"SaveReadChar() runs fine!"<<std::endl;
			SaveReadUInt64();
			std::cout<<"SaveReadUInt64() runs fine!"<<std::endl;
			SaveReadUInt();
			std::cout<<"SaveReadUInt() runs fine!"<<std::endl;
			SaveReadUShort();
			std::cout<<"SaveReadUShort() runs fine!"<<std::endl;
			SaveReadUChar();
			std::cout<<"SaveReadUChar() runs fine!"<<std::endl;
			SaveReadString();
			std::cout<<"SaveReadString() runs fine!"<<std::endl;
			SaveReadEscapeString();
			std::cout<<"SaveReadEscapeString() runs fine!"<<std::endl;
			SaveReadDouble();
			std::cout<<"SaveReadDouble() runs fine!"<<std::endl;
			SaveReadFloat();
			std::cout<<"SaveReadFloat() runs fine!"<<std::endl;
			SaveReadHex();
			std::cout<<"SaveReadHex() runs fine!"<<std::endl;
			SaveReadHexWithPrefix();
			std::cout<<"SaveReadHexWithPrefix() runs fine!"<<std::endl;
			SaveReadHexWithLowerCase();
			std::cout<<"SaveReadHexWithLowerCase() runs fine!"<<std::endl;
		}

	};
}