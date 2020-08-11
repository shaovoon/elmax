// TestConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../PortableElmax/Elmax.h"
#include "cpplinq.hpp"
#include <iostream>
#include <map>

using namespace std;

void WriteElement(std::string& xml)
{
	using namespace Elmax;
	RootElement root("Products");

	root.Create("Product").Create("Qty").SetInt32(1234);

	xml = root.ToPrettyString("    ");

	std::cout << xml << std::endl;
}

void ReadElement(const std::string& xml)
{
	using namespace Elmax;
	RootElement root;
	root.ParseXMLString(xml);

	int qty = root["Product"]["Qty"].GetInt32(0);

	std::cout << "Qty:" << qty << std::endl;
}

void WriteAttr(std::string& xml)
{
	using namespace Elmax;
	RootElement root("Products");

	Element elem = root.Create("Product");
	elem.SetAttrInt32("Qty", 1234);

	xml = root.ToPrettyString("    ");

	std::cout << xml << std::endl;

	
}

void ReadAttr(const std::string& xml)
{
	using namespace Elmax;
	Element root;
	root.ParseXMLString(xml);

	Element elem = root["Product"];

	int qty=elem.GetAttrInt32("Qty", 0);

	std::cout << "Qty:" << qty << std::endl;
}

void WriteComment(std::string& xml)
{
	using namespace Elmax;
	RootElement root("Products");

	Element elem = root.Create("Product");
	elem.SetAttrInt32("Qty", 1234);
	elem.AddComment("Qty must not be less than 100");

	xml = root.ToPrettyString("    ");

	std::cout << xml << std::endl;
}

void ReadComment(const std::string& xml)
{
	using namespace Elmax;
	Element root;
	root.ParseXMLString(xml);

	Element elem = root["Product"];

	int qty=elem.GetAttrInt32("Qty", 0);

	std::vector<Comment> vec = elem.GetCommentCollection();

	std::cout << "Qty:" << qty << std::endl;

	if(vec.size()>0)
		std::cout << "Comment:" << vec[0].GetContent() << std::endl;
}

void WriteCData(std::string& xml)
{
	using namespace Elmax;
	RootElement root("Products");

	Element elem = root.Create("Product");
	elem.SetAttrInt32("Qty", 1234);
	elem.AddCData("Hello world!");

	xml = root.ToPrettyString("    ");

	std::cout << xml << std::endl;
}

void ReadCData(const std::string& xml)
{
	using namespace Elmax;
	Element root;
	root.ParseXMLString(xml);

	Element elem = root["Product"];

	int qty = elem.GetAttrInt32("Qty", 0);

	std::vector<CData> vec = elem.GetCDataCollection();

	std::cout << "Qty:" << qty << std::endl;

	if(vec.size()>0)
		std::cout << "CData:" << vec[0].GetContent() << std::endl;
}

void NamespaceUri()
{
	using namespace Elmax;
	RootElement root("Products");

	Element elem = root.Create("Product").Create("Grocery:Item", "http://www.example.com");
	elem.SetInt32(1234);

	string xml = root.ToPrettyString("    ");

	std::cout << xml << std::endl;
}

void AsCollection()
{
	using namespace Elmax;
	RootElement root("Products");

	Element elem1 = root.Create(_TS("Product"));
	elem1.SetAttrInt32("Qty", 400);
	elem1.SetString("Shower Cap");
	Element elem2 = root.Create(_TS("Product"));
	elem2.SetAttrInt32("Qty", 600);
	elem2.SetString("Soap");
	Element elem3 = root.Create(_TS("Product"));
	elem3.SetAttrInt32("Qty", 700);
	elem3.SetString("Shampoo");

	string xml = root.ToPrettyString("    ");
	std::cout << xml << std::endl;

	Element::collection_t vec = root["Product"].AsCollection();

	for(size_t i=0;i<vec.size(); ++i)
	{
		cout << vec[i].GetString("") << ":" << vec[i].GetAttrInt32("Qty", 0) << std::endl;
	}
}

void AsCollectionLambda()
{
	using namespace Elmax;
	RootElement root("Products");

	Element elem1 = root.Create(_TS("Product"));
	elem1.SetAttrInt32("Qty", 400);
	elem1.SetString("Shower Cap");
	Element elem2 = root.Create(_TS("Product"));
	elem2.SetAttrInt32("Qty", 600);
	elem2.SetString("Soap");
	Element elem3 = root.Create(_TS("Product"));
	elem3.SetAttrInt32("Qty", 700);
	elem3.SetString("Shampoo");

	string xml = root.ToPrettyString("    ");
	std::cout << xml << std::endl;

	Element::collection_t vec = root["Product"].AsCollection([](Element elem){
		return (elem.GetAttrInt32("Qty", 0)>500);
	});


	for(size_t i=0;i<vec.size(); ++i)
	{
		cout << vec[i].GetString("") << ":" << vec[i].GetAttrInt32("Qty", 0) << std::endl;
	}
}

void Iterators()
{
	using namespace Elmax;
	RootElement root("Products");

	Element elem1 = root.Create(_TS("Product"));
	elem1.SetAttrInt32("Qty", 400);
	elem1.SetString("Shower Cap");
	Element elem2 = root.Create(_TS("Product"));
	elem2.SetAttrInt32("Qty", 600);
	elem2.SetString("Soap");
	Element elem3 = root.Create(_TS("Product"));
	elem3.SetAttrInt32("Qty", 700);
	elem3.SetString("Shampoo");

	string xml = root.ToPrettyString("    ");
	std::cout << xml << std::endl;

	Element::Iterator it = root.Begin("*");

	for(;it!=root.End(); ++it)
	{
		cout << (*it).GetString("") << ":" << (*it).GetAttrInt32("Qty", 0) << std::endl;
	}
}

void CppLinq()
{
	using namespace Elmax;
	RootElement root("Bookstore");

	Element Book1 = root.Create(_TS("Books")).Create(_TS("Book"));
	Book1.SetAttrInt32("AuthorID", 1255);
	Book1["Title"].SetString("The Joy Luck Club");
	Element Book2 = root.Create(_TS("Books")).Create(_TS("Book"));
	Book2.SetAttrInt32("AuthorID", 2562);
	Book2["Title"].SetString("The First Phone Call from Heaven");
	Element Book3 = root.Create(_TS("Books")).Create(_TS("Book"));
	Book3.SetAttrInt32("AuthorID", 3651);
	Book3["Title"].SetString("David and Goliath");

	Element Author1 = root.Create(_TS("Authors")).Create(_TS("Author"));
	Author1.SetAttrInt32("AuthorID", 1255);
	Author1["Name"].SetString("Amy Tan");
	Author1["Gender"].SetString("Female");
	Element Author2 = root.Create(_TS("Authors")).Create(_TS("Author"));
	Author2.SetAttrInt32("AuthorID", 2562);
	Author2["Name"].SetString("Mitch Albom");
	Author2["Gender"].SetString("Male");
	Element Author3 = root.Create(_TS("Authors")).Create(_TS("Author"));
	Author3.SetAttrInt32("AuthorID", 3651);
	Author3["Name"].SetString("Malcolm Gladwell");
	Author3["Gender"].SetString("Male");

	string xml = root.ToPrettyString("    ");
	std::cout << xml << std::endl;

	using namespace cpplinq;
	struct BookInfo
	{
		std::string title;
		std::string author;
	};
	auto result = 
		from (root["Books"].GetChildren("Book"))
		>> join (
		from (root["Authors"].GetChildren("Author")),
		// Selects the AuthorID on book element to join on
		[](const Element& b) {return b.GetAttrInt32("AuthorID", -1);},
		// Selects the AuthorID on author element to join on
		[](const Element& a) {return a.GetAttrInt32("AuthorID", -1);},
		// Gets book title and author name
		[](const Element& b, const Element& a) -> BookInfo
		{ BookInfo info = {b["Title"].GetString(""), a["Name"].GetString("")}; return info;}
		)
		>> to_vector();

	for(size_t i=0;i<result.size(); ++i)
	{
		std::cout << result[i].title << " is written by " << result[i].author << std::endl;
	}
	TSTR File = "c:\\temp\\Test.xml";
	root.PrettySave(File, FT_UTF8, "  ");
}

void TestPrettyPrint()
{
	Elmax::RootElement Root;
	TSTR File = "c:\\temp\\Test.xml";
	try
	{
		Root.Open(File);
	}
	catch (std::exception&)
	{
		// open failed, use default;
	}

	Root.GetChildElement("Data").SetString("Test");
	Root.PrettySave(File, FT_UTF8, "  ");
}

int _tmain(int argc, _TCHAR* argv[])
{
	//std::string xml;
	//WriteElement(xml);
	//ReadElement(xml);

	//WriteAttr(xml);
	//ReadAttr(xml);

	//WriteComment(xml);
	//ReadComment(xml);

	//WriteCData(xml);
	//ReadCData(xml);

	//NamespaceUri();

	//AsCollection();
	//AsCollectionLambda();
	//Iterators();

	//CppLinq();
	TestPrettyPrint();
	return 0;
}

