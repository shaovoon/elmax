#include "Assert.h"
#include "../PortableElmax/Elmax.h"

namespace UnitTestElmax
{		
	TEST_CLASS(UnitTestSetterGetter)
	{
	public:
		
		TEST_METHOD(SetGetDateTime)
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
			
		}
		TEST_METHOD(SetGetDate)
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
			
		}
		TEST_METHOD(SetGetBoolean)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			bool dd = true;
			Assert::IsTrue(elem.Exists());
			elem.SetBool(dd);

			bool dd2 = elem.GetBool(false);

			Assert::AreEqual(dd, dd2);
			
		}
		TEST_METHOD(SetGetInt64)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			ELMAX_INT64 dd = 14000000000L;
			Assert::IsTrue(elem.Exists());
			elem.SetInt64(dd);

			ELMAX_INT64 dd2 = elem.GetInt64(10);

			Assert::IsTrue(dd == dd2);
			
		}
		TEST_METHOD(SetGetInt)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			int dd = 2000000000;
			Assert::IsTrue(elem.Exists());
			elem.SetInt32(dd);

			int dd2 = elem.GetInt32(10);

			Assert::AreEqual(dd, dd2);
			
		}
		TEST_METHOD(SetGetShort)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			short dd = 32000;
			Assert::IsTrue(elem.Exists());
			elem.SetInt16(dd);

			short dd2 = elem.GetInt16(10);

			Assert::AreEqual(dd, dd2);
			
		}
		TEST_METHOD(SetGetChar)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			char dd = 'A';
			Assert::IsTrue(elem.Exists());
			elem.SetChar(dd);

			char dd2 = elem.GetChar('P');

			Assert::AreEqual(dd, dd2);
			
		}
		TEST_METHOD(SetGetUInt64)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned ELMAX_INT64 dd = 14000000000UL;
			Assert::IsTrue(elem.Exists());
			elem.SetUInt64(dd);

			unsigned ELMAX_INT64 dd2 = elem.GetUInt64(10);

			Assert::AreEqual(dd, dd2);
			
		}
		TEST_METHOD(SetGetUInt)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 4000000000;
			Assert::IsTrue(elem.Exists());
			elem.SetUInt32(dd);

			unsigned int dd2 = elem.GetUInt32(10);

			Assert::AreEqual(dd, dd2);
			
		}
		TEST_METHOD(SetGetUShort)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned short dd = 65000;
			Assert::IsTrue(elem.Exists());
			elem.SetUInt16(dd);

			unsigned short dd2 = elem.GetUInt16(10);

			Assert::IsTrue(dd == dd2);
			
		}
		TEST_METHOD(SetGetUChar)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned char dd = 255;
			Assert::IsTrue(elem.Exists());
			elem.SetUChar(dd);

			unsigned char dd2 = elem.GetUChar(12);

			Assert::AreEqual(dd, dd2);
			
		}
		TEST_METHOD(SetGetWString)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			TSTR dd = _TS("ABCD");
			Assert::IsTrue(elem.Exists());
			elem.SetString(dd);

			TSTR dd2 = elem.GetString(_TS("A"));

			Assert::IsTrue(dd == dd2);
			
		}
		TEST_METHOD(SetGetDouble)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			double dd = 123.0;
			Assert::IsTrue(elem.Exists());
			elem.SetDouble(dd);

			double dd2 = elem.GetDouble(10.0);

			Assert::AreEqual(dd, dd2);
			
		}
		TEST_METHOD(SetGetFloat)
		{
			Assert::FunctionName = __FUNCTION__;
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			float dd = 123.0f;
			Assert::IsTrue(elem.Exists());
			elem.SetFloat(dd);

			float dd2 = elem.GetFloat(10.0f);

			Assert::AreEqual(dd, dd2);
			
		}

		static void executeTests()
		{
			SetGetDateTime();
			std::cout<<"SetGetDateTime() runs fine!"<<std::endl;
			SetGetDate();
			std::cout<<"SetGetDate() runs fine!"<<std::endl;
			SetGetBoolean();
			std::cout<<"SetGetBoolean() runs fine!"<<std::endl;
			SetGetInt64();
			std::cout<<"SetGetInt64() runs fine!"<<std::endl;
			SetGetInt();
			std::cout<<"SetGetInt() runs fine!"<<std::endl;
			SetGetShort();
			std::cout<<"SetGetShort() runs fine!"<<std::endl;
			SetGetChar();
			std::cout<<"SetGetChar() runs fine!"<<std::endl;
			SetGetUInt64();
			std::cout<<"SetGetUInt64() runs fine!"<<std::endl;
			SetGetUInt();
			std::cout<<"SetGetUInt() runs fine!"<<std::endl;
			SetGetUShort();
			std::cout<<"SetGetUShort() runs fine!"<<std::endl;
			SetGetUChar();
			std::cout<<"SetGetUChar() runs fine!"<<std::endl;
			SetGetWString();
			std::cout<<"SetGetWString() runs fine!"<<std::endl;
			SetGetDouble();
			std::cout<<"SetGetDouble() runs fine!"<<std::endl;
			SetGetFloat();
			std::cout<<"SetGetFloat() runs fine!"<<std::endl;
		}

	};
}