#pragma once
#include <string>
#include <vector>

class StringHelperFunctions
{
public:
	StringHelperFunctions();
	~StringHelperFunctions();

	static void createVectorOfStringsFromInputString(const std::string & inputStr, std::vector<std::string>& vecStrings);

};

