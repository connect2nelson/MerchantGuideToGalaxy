#include "StringHelperFunctions.h"

#include <sstream>

StringHelperFunctions::StringHelperFunctions()
{
}


StringHelperFunctions::~StringHelperFunctions()
{
}

void StringHelperFunctions::createVectorOfStringsFromInputString(const std::string& inputStr, std::vector<std::string>& vecStrings)
{
	std::istringstream iss(inputStr);
	do
	{
		std::string sub; iss >> sub;
		if (!sub.empty())
		{
			vecStrings.push_back(sub);
		}
	} while (iss);
}
