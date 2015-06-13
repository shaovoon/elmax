// TestSequelMax.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include "../SequelMax/SequelMax.h"

#ifdef _MICROSOFT
TSTR GetFolderPath()
{
	return _TS("c:\\temp\\");
	//return _TS("..\\");
}
#else
TSTR GetFolderPath()
{
	return _TS("temp/");
}
#endif

struct Employee 
{
	int EmployeeID;
	int SupervisorID;
	TSTR Name;
	TSTR Gender;
	double Salary;
	TSTR Comment;
};

std::string conv_to_astring(const TSTR& text);

#ifdef ELMAX_USE_BOOST_FUNC
void ReadEmployee(SequelMax::Element& elem, std::vector<Employee>& vec);
void ReadName(const TSTR& text, std::vector<Employee>& vec);
void ReadGender(const TSTR& text, std::vector<Employee>& vec);
void ReadSalary(const TSTR& text, std::vector<Employee>& vec);
void ReadComment(const TSTR& text, std::vector<Employee>& vec);

void ReadEmployee(SequelMax::Element& elem, std::vector<Employee>& vec)
{
	Employee emp;
	emp.EmployeeID = elem.Attr(_TS("EmployeeID"));
	emp.SupervisorID = elem.Attr(_TS("SupervisorID"));
	vec.push_back(emp);
}
void ReadName(const TSTR& text, std::vector<Employee>& vec)
{
	vec.back().Name = text;
}
void ReadGender(const TSTR& text, std::vector<Employee>& vec)
{
	vec.back().Gender = text;
}
void ReadSalary(const TSTR& text, std::vector<Employee>& vec)
{
	#ifdef ELMAX_USE_UNICODE
		vec.back().Salary = boost::lexical_cast<int>(conv_to_astring(text));
	#else
		vec.back().Salary = boost::lexical_cast<int>(GET_CONST_PTR(text));
	#endif
}
void ReadComment(const TSTR& text, std::vector<Employee>& vec)
{
	vec.back().Comment = text;
}
bool ReadDoc(const TSTR& file, std::vector<Employee>& vec)
{
	using namespace SequelMax;
	Document doc;

	doc.RegisterStartElementFunctor(_TS("Employees|Employee"), boost::bind(ReadEmployee, _1, boost::ref(vec)));
	doc.RegisterEndElementFunctor(_TS("Employees|Employee|Name"), boost::bind(ReadName, _1, boost::ref(vec)));
	doc.RegisterEndElementFunctor(_TS("Employees|Employee|Gender"), boost::bind(ReadGender, _1, boost::ref(vec)));
	doc.RegisterEndElementFunctor(_TS("Employees|Employee|Salary"), boost::bind(ReadSalary, _1, boost::ref(vec)));
	doc.RegisterCommentFunctor(_TS("Employees|Employee"), boost::bind(ReadComment, _1, boost::ref(vec)));

	return doc.Open(file);
}

#else
bool ReadDoc(const TSTR& file, std::vector<Employee>& vec)
{
	using namespace SequelMax;
	Document doc;

	doc.RegisterStartElementFunctor(_TS("Employees|Employee"), [&vec](Element& elem)->void {
		Employee emp;
		emp.EmployeeID = elem.Attr(_TS("EmployeeID"));
		emp.SupervisorID = elem.Attr(_TS("SupervisorID"));
		vec.push_back(emp);
	});
	doc.RegisterEndElementFunctor(_TS("Employees|Employee|Name"), [&vec](const TSTR& text)->void {
		vec.back().Name = text;
	});
	doc.RegisterEndElementFunctor(_TS("Employees|Employee|Gender"), [&vec](const TSTR& text)->void {
		vec.back().Gender = text;
	});
	doc.RegisterEndElementFunctor(_TS("Employees|Employee|Salary"), [&vec](const TSTR& text)->void {
#ifdef ELMAX_USE_UNICODE
		vec.back().Salary = boost::lexical_cast<int>(conv_to_astring(text));
#else
		vec.back().Salary = boost::lexical_cast<int>(GET_CONST_PTR(text));
#endif
	});
	doc.RegisterCommentFunctor(_TS("Employees|Employee"), [&vec](const TSTR& text)->void {
		vec.back().Comment = text;
	});

	return doc.Open(file);
}
#endif
void DisplayDoc(const std::vector<Employee>& vec)
{
#ifdef ELMAX_USE_UNICODE
	for(size_t i=0; i<vec.size(); ++i)
	{
		std::wcout << L"Name: " << GET_CONST_PTR(vec[i].Name) << std::endl;
		std::wcout << L"EmployeeID: " << vec[i].EmployeeID << std::endl;
		std::wcout << L"SupervisorID: " << vec[i].SupervisorID << std::endl;
		std::wcout << L"Gender: " << GET_CONST_PTR(vec[i].Gender) << std::endl;
		std::wcout << L"Salary: " << vec[i].Salary << std::endl;

		if(IS_EMPTY(vec[i].Comment)==false)
			std::wcout << L"Comment: " << GET_CONST_PTR(vec[i].Comment) << std::endl;
		
		std::wcout << std::endl;
	}
#else
	for(size_t i=0; i<vec.size(); ++i)
	{
		std::cout << "Name: " << GET_CONST_PTR(vec[i].Name) << std::endl;
		std::cout << "EmployeeID: " << vec[i].EmployeeID << std::endl;
		std::cout << "SupervisorID: " << vec[i].SupervisorID << std::endl;
		std::cout << "Gender: " << GET_CONST_PTR(vec[i].Gender) << std::endl;
		std::cout << "Salary: " << vec[i].Salary << std::endl;

		if(IS_EMPTY(vec[i].Comment)==false)
			std::cout << "Comment: " << GET_CONST_PTR(vec[i].Comment) << std::endl;

		std::cout << std::endl;
	}
#endif
}
void PopulateData(std::vector<Employee>& vec)
{
	Employee emp1;
	emp1.EmployeeID = 1286;
	emp1.SupervisorID = 666;
	emp1.Name = _TS("Amanda Dion");
	emp1.Salary = 2200.0;
	emp1.Gender = _TS("Female");
	emp1.Comment = _TS("Hardworking employee!");

	Employee emp2;
	emp2.EmployeeID = 1287;
	emp2.SupervisorID = 666;
	emp2.Name = _TS("John Smith");
	emp2.Salary = 3200.0;
	emp2.Gender = _TS("Male");
	emp2.Comment = _TS("Hardly working employee!");

	Employee emp3;
	emp3.EmployeeID = 1288;
	emp3.SupervisorID = 666;
	emp3.Name = _TS("Sheldon Cohn");
	emp3.Salary = 5600.0;
	emp3.Gender = _TS("Male");

	vec.clear();
	vec.push_back(emp1);
	vec.push_back(emp2);
	vec.push_back(emp3);

}

bool WriteDoc(const TSTR& file, std::vector<Employee>& vec)
{
	using namespace SequelMax;
	XMLWriter w;
	if(w.Open(file, FT_UTF8, NEW, _TS("    ")))
	{
		w.WriteProcessingInstruction(_TS("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"));
		w.WriteStartElem(_TS("Employees"));
	
		for(size_t i=0; i<vec.size(); ++i)
		{
			w.WriteStartElem(_TS("Employee"));
				w.WriteAttr(_TS("EmployeeID"), vec[i].EmployeeID);
				w.WriteAttr(_TS("SupervisorID"), vec[i].SupervisorID);
				
				w.WriteElement(_TS("Name"), vec[i].Name);
				w.WriteElement(_TS("Salary"), vec[i].Salary);
				w.WriteElement(_TS("Gender"), vec[i].Gender);

				if(IS_EMPTY(vec[i].Comment)==false)
					w.WriteComment(vec[i].Comment);
			w.WriteEndElem();
		}
		w.WriteEndElem();
	}
	else
		return false;
	
	return true;
}

int main(int argc, char* argv[])
{
	std::vector<Employee> vec;
	PopulateData(vec);
	try
	{
		if(WriteDoc(GetFolderPath() + _TS("emp.xml"), vec)==false)
			std::cout << "Cannot write file!" << std::endl;

		std::vector<Employee> vecRead;
		if(ReadDoc(GetFolderPath() + _TS("emp.xml"), vecRead))
			DisplayDoc(vecRead);
		else
			std::cout << "Cannot read file!" << std::endl;
	}
	catch (boost::bad_lexical_cast& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

std::string conv_to_astring(const TSTR& text)
{
	std::string str = "";
	for(size_t i=0; i<GET_SIZE(text); ++i)
	{
		str += (char)(text[i]);
	}

	return str;
}



