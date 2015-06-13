// PreVS2012UnitTestElmax.cpp : Defines the entry point for the console application.
//

#include "UnitTestAttribute.cpp"
#include "UnitTestCommentAndCData.cpp"
#include "UnitTestMisc.cpp"
#include "UnitTestSaveAndRead.cpp"
#include "UnitTestSetterGetter.cpp"
#include "UnitTestVoidGetter.cpp"
#include <boost/lexical_cast.hpp>

using namespace UnitTestElmax;

int main(int argc, char* argv[])
{
	try
	{
		UnitTestAttribute::executeTests();
		UnitTestCommentAndCData::executeTests();
		UnitTestMisc::executeTests();
		UnitTestSaveAndRead::executeTests();
		UnitTestSetterGetter::executeTests();
		UnitTestVoidGetter::executeTests();
		std::cout<<"All unit tests passed"<<std::endl;
	}
	catch (boost::bad_lexical_cast& e)
	{
		std::cout<<"Exception error: "<<e.what()<< std::endl;
	}
	catch (std::runtime_error& e)
	{
		std::cout<<"Runtime error: "<<e.what()<< std::endl;
	}
	catch (std::logic_error& e)
	{
		std::cout<<"Logic error: "<<e.what()<< std::endl;
	}
	catch (std::exception& e)
	{
		std::cout<<"Exception error: "<<e.what()<< std::endl;
	}

#if defined _DEBUG && defined _MICROSOFT
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}

