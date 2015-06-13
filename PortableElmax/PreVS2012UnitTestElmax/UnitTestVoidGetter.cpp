#include "Assert.h"
#include "../PortableElmax/Elmax.h"

namespace UnitTestElmax
{
	TEST_CLASS(UnitTestVoidGetter)
	{
	public:
		
		TEST_METHOD(GetVoidDateTime)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			DateAndTime dd(2006, 7, 23, 9, 0, 23);
			Assert::IsTrue(elem.Exists());
			DateAndTime dd3 = elem[_TS("dd")].GetDateTime(dd);

			Assert::AreEqual(dd.GetYear(), dd3.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
			Assert::AreEqual(dd.GetHour(), dd3.GetHour());
			Assert::AreEqual(dd.GetMinute(), dd3.GetMinute());
			Assert::AreEqual(dd.GetSecond(), dd3.GetSecond());
			root.Destroy();
		}
		TEST_METHOD(GetVoidDate)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Date dd(2010, 10, 1);
			Assert::IsTrue(elem.Exists());
			Date dd3 = elem[_TS("dd")].GetDate(dd);

			Assert::AreEqual(dd.GetYear(), dd3.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
			root.Destroy();
		}
		TEST_METHOD(GetVoidBoolean)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			bool dd = false;
			Assert::IsTrue(elem.Exists());

			bool dd2 = elem[_TS("dd")].GetBool(false);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidInt64)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			ELMAX_INT64 dd = 14000000000L;
			Assert::IsTrue(elem.Exists());

			ELMAX_INT64 dd2 = elem[_TS("dd")].GetInt64(dd);

			Assert::IsTrue(dd == dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidInt)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			int dd = 2000000000;
			Assert::IsTrue(elem.Exists());

			int dd2 = elem[_TS("dd")].GetInt32(dd);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidShort)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			short dd = 32000;
			Assert::IsTrue(elem.Exists());

			short dd2 = elem[_TS("dd")].GetInt16(dd);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidChar)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			char dd = 'A';
			Assert::IsTrue(elem.Exists());

			char dd2 = elem[_TS("dd")].GetChar(dd);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidUInt64)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			unsigned ELMAX_INT64 dd = 14000000000UL;
			Assert::IsTrue(elem.Exists());

			unsigned ELMAX_INT64 dd2 = elem[_TS("dd")].GetUInt64(dd);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidUInt)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			unsigned int dd = 4000000000;
			Assert::IsTrue(elem.Exists());

			unsigned int dd2 = elem[_TS("dd")].GetUInt32(dd);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidUShort)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			unsigned short dd = 65000;
			Assert::IsTrue(elem.Exists());

			unsigned short dd2 = elem[_TS("dd")].GetUInt16(dd);

			Assert::IsTrue(dd == dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidUChar)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			unsigned char dd = 255;
			Assert::IsTrue(elem.Exists());

			unsigned char dd2 = elem[_TS("dd")].GetUChar(dd);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidWString)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			TSTR dd = _TS("ABCD");
			Assert::IsTrue(elem.Exists());

			TSTR dd2 = elem[_TS("dd")].GetString(dd);

			Assert::IsTrue(dd == dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidDouble)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			double dd = 123.0;
			Assert::IsTrue(elem.Exists());

			double dd2 = elem[_TS("dd")].GetDouble(dd);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidFloat)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			float dd = 123.0f;
			Assert::IsTrue(elem.Exists());

			float dd2 = elem[_TS("dd")].GetFloat(dd);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(GetVoidHex)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());

			unsigned int ans = elem[_TS("dd")].ReadHex(0xee);

			Assert::AreEqual((unsigned int)(0xee), ans);
			root.Destroy();
		}
		static void executeTests()
		{
			GetVoidDateTime();
			std::cout<<"GetVoidDateTime() runs fine!"<<std::endl;
			GetVoidDate();
			std::cout<<"GetVoidDate() runs fine!"<<std::endl;
			GetVoidBoolean();
			std::cout<<"GetVoidBoolean() runs fine!"<<std::endl;
			GetVoidInt64();
			std::cout<<"GetVoidInt64() runs fine!"<<std::endl;
			GetVoidInt();
			std::cout<<"GetVoidInt() runs fine!"<<std::endl;
			GetVoidShort();
			std::cout<<"GetVoidShort() runs fine!"<<std::endl;
			GetVoidChar();
			std::cout<<"GetVoidChar() runs fine!"<<std::endl;
			GetVoidUInt64();
			std::cout<<"GetVoidUInt64() runs fine!"<<std::endl;
			GetVoidUInt();
			std::cout<<"GetVoidUInt() runs fine!"<<std::endl;
			GetVoidUShort();
			std::cout<<"GetVoidUShort() runs fine!"<<std::endl;
			GetVoidUChar();
			std::cout<<"GetVoidUChar() runs fine!"<<std::endl;
			GetVoidWString();
			std::cout<<"GetVoidWString() runs fine!"<<std::endl;
			GetVoidDouble();
			std::cout<<"GetVoidDouble() runs fine!"<<std::endl;
			GetVoidFloat();
			std::cout<<"GetVoidFloat() runs fine!"<<std::endl;
			GetVoidHex();
			std::cout<<"GetVoidHex() runs fine!"<<std::endl;
		}
	};
}