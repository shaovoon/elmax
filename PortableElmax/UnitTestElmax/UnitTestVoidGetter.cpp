#include "stdafx.h"
#include "CppUnitTest.h"
#include "../PortableElmax/Elmax.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestElmax
{
	TEST_CLASS(UnitTestVoidGetter)
	{
	public:
		
		TEST_METHOD(GetVoidDateTime)
		{
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
			using namespace Elmax;
			RootElement root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Assert::IsTrue(elem.Exists());

			unsigned int ans = elem.ReadHex(0xee);

			Assert::AreEqual((unsigned int)(0xee), ans);
			
		}
	};
}