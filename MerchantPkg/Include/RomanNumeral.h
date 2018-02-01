#pragma once

#include <string>
#include <map>

class RomanNumeral
{
public:

	static bool canThisRomanDigitBeSubtracted(std::string& strRoman, size_t i, bool& value1);
	static bool IsSubtractionSequenceAllowed(std::string& strRoman, size_t i, bool& value1);


	static int getDecimalEquivalent(const std::string& x);
	static bool IsSubtractionSequenceValid(std::string& strRoman);
	static bool IsDuplicationNotAllowedForCurrentChar(const char& romanNumeral);
	static bool checkWhetherThirdAndFourthDuplicatesAreSeperatedBySmallerValue(std::string& strRoman, size_t i, bool& value1);
	static bool IsDuplicationOfCharValid(std::string& strRoman);

	static bool containsValidRomanNumeralChar(std::string& roman);
	static int getDecimalValueOfRomanDigit(char d);

	static bool isRomanNumberValid(std::string& strRoman);
	~RomanNumeral();
};

