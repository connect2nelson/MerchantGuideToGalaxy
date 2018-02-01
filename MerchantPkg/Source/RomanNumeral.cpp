#include "RomanNumeral.h"


bool RomanNumeral::canThisRomanDigitBeSubtracted(std::string& strRoman, size_t i, bool& value1)
{
	switch (strRoman[i])
	{
	case 'L':
	case 'V':
	case 'D':
		{
			value1 = false;
			return true;
		}
	default:
		break;
	}
	return false;
}

bool RomanNumeral::IsSubtractionSequenceAllowed(std::string& strRoman, size_t i, bool& value1)
{
	if (strRoman[i] == 'I')
	{
		switch (strRoman[i + 1])
		{
		case 'V':
		case 'X':
			break;
		default:
			{
				value1 = false;
				return true;
			}
		}
	}
	else if (strRoman[i] == 'X')
	{
		switch (strRoman[i + 1])
		{
		case 'L':
		case 'C':
			break;
		default:
			{
				value1 = false;
				return true;
			}
		}
	}
	else if (strRoman[i] == 'C')
	{
		switch (strRoman[i + 1])
		{
		case 'D':
		case 'M':
			break;
		default:
			{
				value1 = false;
				return true;
			}
		}
	}
	return false;
}

bool RomanNumeral::IsSubtractionSequenceValid(std::string& strRoman)
{
	for (size_t i = 0; i < strRoman.size() - 1; i++)
	{
		if (getDecimalValueOfRomanDigit(strRoman[i]) < getDecimalValueOfRomanDigit(strRoman[i+1]))
		{
			bool isSubtractionPossible = true;
			if (canThisRomanDigitBeSubtracted(strRoman, i, isSubtractionPossible))
				return isSubtractionPossible;

			bool isSubtractionSequenceAllowed = true;
			if (IsSubtractionSequenceAllowed(strRoman, i, isSubtractionSequenceAllowed)) 
				return isSubtractionSequenceAllowed;
		}
	}
	return true;
}

int RomanNumeral::getDecimalEquivalent(const std::string& x)
{
	auto first = std::crbegin(x);
	const auto last = std::crend(x);

	auto decimalDigitFromRoman = [&](char unit, char five, char ten) {
		int num = 0;
		for (; first != last && *first == unit; ++first) ++num;
		while (first != last && (*first == ten || *first == five)) {
			num += *first == ten ? 10 : 5;
			for (++first; first != last && *first == unit; ++first) --num;
		}
		return num;
	};

	int num = 0, pow = 1;
	for (auto syms : { "IVX", "XLC", "CDM" }) {
		num += decimalDigitFromRoman(syms[0], syms[1], syms[2]) * pow;
		pow *= 10;
	}

	return num;
}

bool RomanNumeral::IsDuplicationNotAllowedForCurrentChar(const char&  romanNumeral)
{

	switch (romanNumeral)
	{
	case 'V':
	case 'L':
	case 'D':
		return true;
	default:
		return false;
	}

}

bool RomanNumeral::checkWhetherThirdAndFourthDuplicatesAreSeperatedBySmallerValue(std::string& strRoman, size_t i, bool& value1)
{
	if (i + 2 < strRoman.size() )
		if (strRoman[i] == strRoman[i + 2] && getDecimalValueOfRomanDigit(strRoman[i]) < getDecimalValueOfRomanDigit(strRoman[i+1]))
		{
			value1 = false;
			return true;
		}
	return false;
}

bool RomanNumeral::IsDuplicationOfCharValid(std::string& strRoman)
{

	for (size_t i = 0; i < strRoman.size() - 1; i++)
	{
		if (strRoman[i] == strRoman[i + 1])
		{
			if (IsDuplicationNotAllowedForCurrentChar(strRoman[i]))
				return false;
		}
	}


	if (strRoman.length() >= 3)
	{
		int duplicate_char_seq_count= 0 ;

		for (size_t i = 0; i < strRoman.size() - 1; i++)
		{
			if (strRoman[i] == strRoman[i + 1])
			{
				duplicate_char_seq_count++;

				if (duplicate_char_seq_count >= 3)
					return false;

			}
			else
			{
				if (duplicate_char_seq_count == 2)
				{
					bool bisValid = false;
					if (checkWhetherThirdAndFourthDuplicatesAreSeperatedBySmallerValue(strRoman, i, bisValid)) 
						return bisValid;
				}
				duplicate_char_seq_count = 1;
			}
		}
	}
	return true;
}




bool RomanNumeral::containsValidRomanNumeralChar(std::string& strRomanString)
{
	for (const auto& c : strRomanString)
	{
		switch (c)
		{
		case 'I':
		case 'V':
		case 'X':
		case 'L':
		case 'C':
		case 'D':
		case 'M':
			continue;
		default:
			return false;
		}
	}
	return true;
}


int RomanNumeral::getDecimalValueOfRomanDigit(char d)
{
	switch (d)
	{
	case 'M': return 1000;
	case 'D': return 500;
	case 'C': return 100;
	case 'L': return 50;
	case 'X': return 10;
	case 'V': return 5;
	case 'I': return 1;
	default: throw std::invalid_argument("Invalid digit");
	}
}

bool RomanNumeral::isRomanNumberValid(std::string& strRoman)
{

	return  containsValidRomanNumeralChar(strRoman)
			&& IsDuplicationOfCharValid(strRoman)
			&& IsSubtractionSequenceValid(strRoman);
	
}
RomanNumeral::~RomanNumeral()
{}
