#include "stdafx.h"
#include "CppUnitTest.h"
#include "../PortableElmax/Elmax.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestElmax
{		
	TEST_CLASS(UnitTestSetterGetter)
	{
	public:
		
		TEST_METHOD(SetGetDateTime)
		{
			using namespace Elmax;

			Element root(_TS("aa"));

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
			root.Destroy();
		}
		TEST_METHOD(SetGetDate)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			Date dd(2010, 10, 1);
			Assert::IsTrue(elem.Exists());
			elem.SetDate(dd);
			Date ddcheck;
			Date dd3 = elem.GetDate(ddcheck);

			Assert::AreEqual(dd.GetYear(), dd3.GetYear());
			Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
			Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
			root.Destroy();
		}
		TEST_METHOD(SetGetBoolean)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			bool dd = true;
			Assert::IsTrue(elem.Exists());
			elem.SetBool(dd);

			bool dd2 = elem.GetBool(false);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetInt64)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			ELMAX_INT64 dd = 14000000000L;
			Assert::IsTrue(elem.Exists());
			elem.SetInt64(dd);

			ELMAX_INT64 dd2 = elem.GetInt64(10);

			Assert::IsTrue(dd == dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetInt)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			int dd = 2000000000;
			Assert::IsTrue(elem.Exists());
			elem.SetInt32(dd);

			int dd2 = elem.GetInt32(10);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetShort)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			short dd = 32000;
			Assert::IsTrue(elem.Exists());
			elem.SetInt16(dd);

			short dd2 = elem.GetInt16(10);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetChar)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			char dd = 'A';
			Assert::IsTrue(elem.Exists());
			elem.SetChar(dd);

			char dd2 = elem.GetChar('P');

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetUInt64)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned ELMAX_INT64 dd = 14000000000UL;
			Assert::IsTrue(elem.Exists());
			elem.SetUInt64(dd);

			unsigned ELMAX_INT64 dd2 = elem.GetUInt64(10);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetUInt)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned int dd = 4000000000;
			Assert::IsTrue(elem.Exists());
			elem.SetUInt32(dd);

			unsigned int dd2 = elem.GetUInt32(10);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetUShort)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned short dd = 65000;
			Assert::IsTrue(elem.Exists());
			elem.SetUInt16(dd);

			unsigned short dd2 = elem.GetUInt16(10);

			Assert::IsTrue(dd == dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetUChar)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			unsigned char dd = 255;
			Assert::IsTrue(elem.Exists());
			elem.SetUChar(dd);

			unsigned char dd2 = elem.GetUChar(12);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetWString)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			TSTR dd = _TS("ABCD");
			Assert::IsTrue(elem.Exists());
			elem.SetString(dd);

			TSTR dd2 = elem.GetString(_TS("A"));

			Assert::IsTrue(dd == dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetDouble)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			double dd = 123.0;
			Assert::IsTrue(elem.Exists());
			elem.SetDouble(dd);

			double dd2 = elem.GetDouble(10.0);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
		TEST_METHOD(SetGetFloat)
		{
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root.Create(_TS("bb")).Create(_TS("cc"));
			float dd = 123.0f;
			Assert::IsTrue(elem.Exists());
			elem.SetFloat(dd);

			float dd2 = elem.GetFloat(10.0f);

			Assert::AreEqual(dd, dd2);
			root.Destroy();
		}
	};
}