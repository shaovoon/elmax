// TestSequelMax.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include "../SequelMax/SequelMax.h"

#ifdef _MICROSOFT
std::string GetFolderPath()
{
	return "c:\\temp\\";
	//return "..\\";
}
#else
std::string GetFolderPath()
{
	return "temp/";
}
#endif

struct Employee 
{
	int EmployeeID;
	int SupervisorID;
	std::string Name;
	std::string Gender;
	double Salary;
	std::string Comment;
};

#ifdef ELMAX_USE_BOOST_FUNC
void ReadEmployee(SequelMax::Element& elem, std::vector<Employee>& vec);
void ReadName(const std::string& text, std::vector<Employee>& vec);
void ReadGender(const std::string& text, std::vector<Employee>& vec);
void ReadSalary(const std::string& text, std::vector<Employee>& vec);
void ReadComment(const std::string& text, std::vector<Employee>& vec);

void ReadEmployee(SequelMax::Element& elem, std::vector<Employee>& vec)
{
	Employee emp;
	emp.EmployeeID = elem.Attr(_TS("EmployeeID"));
	emp.SupervisorID = elem.Attr(_TS("SupervisorID"));
	vec.push_back(emp);
}
void ReadName(const std::string& text, std::vector<Employee>& vec)
{
	vec.back().Name = text;
}
void ReadGender(const std::string& text, std::vector<Employee>& vec)
{
	vec.back().Gender = text;
}
void ReadSalary(const std::string& text, std::vector<Employee>& vec)
{
	vec.back().Salary = boost::lexical_cast<int>(text);
}
void ReadComment(const std::string& text, std::vector<Employee>& vec)
{
	vec.back().Comment = text;
}
bool ReadDoc(const std::string& file, std::vector<Employee>& vec)
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
bool ReadDoc(const std::string& file, std::vector<Employee>& vec)
{
	using namespace SequelMax;
	Document doc;

	doc.RegisterStartElementFunctor("Employees|Employee", [&vec](Element& elem)->void {
		Employee emp;
		emp.EmployeeID = elem.Attr("EmployeeID");
		emp.SupervisorID = elem.Attr("SupervisorID");
		vec.push_back(emp);
	});
	doc.RegisterEndElementFunctor("Employees|Employee|Name", [&vec](const std::string& text)->void {
		vec.back().Name = text;
	});
	doc.RegisterEndElementFunctor("Employees|Employee|Gender", [&vec](const std::string& text)->void {
		vec.back().Gender = text;
	});
	doc.RegisterEndElementFunctor("Employees|Employee|Salary", [&vec](const std::string& text)->void {
		vec.back().Salary = boost::lexical_cast<int>(text);
	});
	doc.RegisterCommentFunctor("Employees|Employee", [&vec](const std::string& text)->void {
		vec.back().Comment = text;
	});

	return doc.Open(file);
}
#endif
void DisplayDoc(const std::vector<Employee>& vec)
{
	for(size_t i=0; i<vec.size(); ++i)
	{
		std::cout << "Name: " << vec[i].Name << std::endl;
		std::cout << "EmployeeID: " << vec[i].EmployeeID << std::endl;
		std::cout << "SupervisorID: " << vec[i].SupervisorID << std::endl;
		std::cout << "Gender: " << vec[i].Gender << std::endl;
		std::cout << "Salary: " << vec[i].Salary << std::endl;
		if(vec[i].Comment.empty()==false)
			std::cout << "Comment: " << vec[i].Comment << std::endl;
		
		std::cout << std::endl;
	}
}
void PopulateData(std::vector<Employee>& vec)
{
	Employee emp1;
	emp1.EmployeeID = 1286;
	emp1.SupervisorID = 666;
	emp1.Name = "Amanda Dion";
	emp1.Salary = 2200.0;
	emp1.Gender = "Female";
	emp1.Comment = "Hardworking employee!";

	Employee emp2;
	emp2.EmployeeID = 1287;
	emp2.SupervisorID = 666;
	emp2.Name = "John Smith";
	emp2.Salary = 3200.0;
	emp2.Gender = "Male";
	emp2.Comment = "Hardly working employee!";

	Employee emp3;
	emp3.EmployeeID = 1288;
	emp3.SupervisorID = 666;
	emp3.Name = "Sheldon Cohn";
	emp3.Salary = 5600.0;
	emp3.Gender = "Male";

	vec.clear();
	vec.push_back(emp1);
	vec.push_back(emp2);
	vec.push_back(emp3);
}

bool WriteDoc(const std::string& file, std::vector<Employee>& vec)
{
	using namespace SequelMax;
	XMLWriter w;
	if(w.Open(file, FT_UTF8, NEW, "    "))
	{
		w.WriteProcessingInstruction("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		w.WriteStartElem("Employees");
	
		for(size_t i=0; i<vec.size(); ++i)
		{
			w.WriteStartElem("Employee");
				w.WriteAttr("EmployeeID", vec[i].EmployeeID);
				w.WriteAttr("SupervisorID", vec[i].SupervisorID);
				
				w.WriteElement("Name", vec[i].Name);
				w.WriteElement("Salary", vec[i].Salary);
				w.WriteElement("Gender", vec[i].Gender);

				if(vec[i].Comment.empty()==false)
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
		if(WriteDoc(GetFolderPath() + "emp.xml", vec)==false)
			std::cout << "Cannot write file!" << std::endl;
			
		std::vector<Employee> vecRead;
		if(ReadDoc(GetFolderPath() + "emp.xml", vecRead))
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
