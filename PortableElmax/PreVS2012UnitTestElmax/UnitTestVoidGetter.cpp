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
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			DateAndTime dd(2006, 7, 23, 9, 0, 23);
			Assert::IsTrue(elem.Exists());
			DateAndTime dd3 = elem.GetDateTime(dd);

			Assert::AreEqual(dd.GetYear(), dd3.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
			Assert::AreEqual(dd.GetHour(), dd3.GetHour());
			Assert::AreEqual(dd.GetMinute(), dd3.GetMinute());
			Assert::AreEqual(dd.GetSecond(), dd3.GetSecond());
		}
		TEST_METHOD(GetVoidDate)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Date dd(2010, 10, 1);
			Assert::IsTrue(elem.Exists());
			Date dd3 = elem.GetDate(dd);

			Assert::AreEqual(dd.GetYear(), dd3.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
		}
		TEST_METHOD(GetVoidBoolean)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			bool dd = false;
			Assert::IsTrue(elem.Exists());

			bool dd2 = elem.GetBool(false);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(GetVoidInt64)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			ELMAX_INT64 dd = 14000000000L;
			Assert::IsTrue(elem.Exists());

			ELMAX_INT64 dd2 = elem.GetInt64(dd);

			Assert::IsTrue(dd == dd2);
		}
		TEST_METHOD(GetVoidInt)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			int dd = 2000000000;
			Assert::IsTrue(elem.Exists());

			int dd2 = elem.GetInt32(dd);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(GetVoidShort)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			short dd = 32000;
			Assert::IsTrue(elem.Exists());

			short dd2 = elem.GetInt16(dd);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(GetVoidChar)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			char dd = 'A';
			Assert::IsTrue(elem.Exists());

			char dd2 = elem.GetChar(dd);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(GetVoidUInt64)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned ELMAX_INT64 dd = 14000000000UL;
			Assert::IsTrue(elem.Exists());

			unsigned ELMAX_INT64 dd2 = elem.GetUInt64(dd);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(GetVoidUInt)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 4000000000;
			Assert::IsTrue(elem.Exists());

			unsigned int dd2 = elem.GetUInt32(dd);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(GetVoidUShort)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned short dd = 65000;
			Assert::IsTrue(elem.Exists());

			unsigned short dd2 = elem.GetUInt16(dd);

			Assert::IsTrue(dd == dd2);
		}
		TEST_METHOD(GetVoidUChar)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned char dd = 255;
			Assert::IsTrue(elem.Exists());

			unsigned char dd2 = elem.GetUChar(dd);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(GetVoidWString)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			TSTR dd = _TS("ABCD");
			Assert::IsTrue(elem.Exists());

			TSTR dd2 = elem.GetString(dd);

			Assert::IsTrue(dd == dd2);
		}
		TEST_METHOD(GetVoidDouble)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			double dd = 123.0;
			Assert::IsTrue(elem.Exists());

			double dd2 = elem.GetDouble(dd);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(GetVoidFloat)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			float dd = 123.0f;
			Assert::IsTrue(elem.Exists());

			float dd2 = elem.GetFloat(dd);

			Assert::AreEqual(dd, dd2);
		}
		TEST_METHOD(GetVoidHex)
		{
			Assert::FunctionName = __FUNCTION__;

			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());

			unsigned int ans = elem.ReadHex(0xee);

			Assert::AreEqual((unsigned int)(0xee), ans);
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