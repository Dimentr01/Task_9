#include <iostream>
#include <fstream>
#include "Tree.h"
#include "Helpers.h"

void TestTree(std::string test, bool needShowTree = false)
{
	auto res = CreateTreeViaInfix(test);
	if(needShowTree)
	{
		std::cout << "--------------------" << std::endl;
		ShowTreeInorder(res, 2);
		std::cout << "--------------------" << std::endl;
	}
	
	// если в формуле будут переменные, то не будем вычислять
	if (CanEvaluateValue(test))
	{
		auto result = EvalValueTree(res);
		if (result == IllegalValue)
		{
			std::cout << "An error has occured..." << std::endl;
			return;
		}
		std::cout << "Result: " << result << std::endl;
	}
	else
	{
		std::cout << "Cant evaluate the value" << std::endl;
	}
}

std::string LoadValueFromFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::string value; 
	if (!file)
	{
		std::cout << "Can`t open file " << fileName << std::endl;
		return value;
	}
	
	while (file)
	{
		std::getline(file, value);
	}

	file.close();

	if (value.empty())
	{
		std::cout << "String is empty" << std::endl;		
	}
	return value;
}

int main()
{
	std::string test1 = "!(!(1+0)*1)+(!1*!1)+1"; 
	
	std::string test2 = "0+!1*1";
	std::string test3 = "(a+b)";
	std::string test4 = "!(a+b+c)+!b+!(a+!b+c)*!(!a+b+c)+!a*!b";
	std::string test5 = "!(!(1+0)*1)+(!1*!1)+1";
	std::string test6 = "1+1*1";
	std::string test7 = "!(!(1+0)*1)+(!1*!1)+!1";

	std::string test = LoadValueFromFile("input.txt");
	std::cout << "Read: " << std::endl;
	std::cout << test << std::endl;
	
	TestTree(test, true);
		
	return 0;
}