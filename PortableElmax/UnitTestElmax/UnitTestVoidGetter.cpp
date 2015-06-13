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
			using namespace Elmax;
			Element root(_TS("aa"));

			Element elem = root[_TS("bb")][_TS("cc")].CreateNew();
			Assert::IsTrue(elem.Exists());

			unsigned int ans = elem[_TS("dd")].ReadHex(0xee);

			Assert::AreEqual((unsigned int)(0xee), ans);
			root.Destroy();
		}
	};
}